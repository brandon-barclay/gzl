#include "PackedColumn.h"
#include "Function.h"
#include "DelimitedFileReader.h"

registerMooseObject("gzlApp", PackedColumn);

InputParameters
PackedColumn::validParams()
{
  auto params = Material::validParams();
  params.addRequiredCoupledVar("temperature", "the temperature of the fluid");
  params.addParam<FunctionName>("radius", "1.0", "radius of steel spheres in the column");
  params.addParam<FunctionName>("porosity", 0.25925, "Porosity of the media");
  // Fluid Properties //
  params.addParam<Real>("fluid_viscosity", 1.002e-3, "viscosity of water at 20c");
  params.addParam<FileName>(
      "fluid_viscosity_file",
      "name of the file containing fluid viscosity as a fucntion of temperature");
  // default will be used if no file specified //
  params.addParam<Real>("fluid_thermal_conductivity", 0.59803, "conductivity of water");
  params.addParam<FileName>("fluid_thermal_conductivity_file", "name of conductivity data file");
  //
  params.addParam<Real>("fluid_density", 998.21, "density of water");
  params.addParam<FileName>("fluid_density_file", "name of density data file");
  //
  params.addParam<Real>("fluid_specific_heat", 4157.0, "cp of fluid");
  params.addParam<FileName>("fluid_specific_heat_file", "name of cp data file");
  // Solid Properties //
  params.addParam<Real>("solid_thermal_conductivity", 15.0, "solid thermal conductivity SS at 20c");
  params.addParam<FileName>("solid_thermal_conductivity_filename", "solid k data file");
  //
  params.addParam<Real>("solid_density", 7900.0, "density of SS at 20");
  params.addParam<FileName>("solid_density_file", "solid density data file");
  //
  params.addParam<Real>("solid_specific_heat", 500.0, "cp of SS at 20");
  params.addParam<FileName>("solid_specific_heat_file", "solid cp data file");

  return params;
}

PackedColumn::PackedColumn(const InputParameters & params)
  : ADMaterial(params),
    _input_radius(getFunction("radius")),
    _input_porosity(getFunction("porosity")),
    _temperature(adCoupledValue("temperature")),
    // fluid init//
    _fluid_mu(getParam<Real>("fluid_viscosity")),
    _fluid_k(getParam<Real>("fluid_thermal_conductivity")),
    _fluid_rho(getParam<Real>("fluid_density")),
    _fluid_cp(getParam<Real>("fluid_specific_heat")),
    // solid init//
    _solid_k(getParam<Real>("solid_thermal_conductivity")),
    _solid_rho(getParam<Real>("solid_density")),
    _solid_cp(getParam<Real>("solid_specific_heat")),
    // properties being solved for //
    _permeability(declareADProperty<Real>("permeability")),
    _porosity(declareADProperty<Real>("porosity")),
    _viscosity(declareADProperty<Real>("viscosity")),
    _thermal_conductivity(declareADProperty<Real>("thermal_conductivity")),
    _specific_heat(declareADProperty<Real>("specific_heat")),
    _density(declareADProperty<Real>("density"))
{
  // Set data for the permeability interpolation //
  std::vector<Real> sphere_sizes = {1, 3};
  std::vector<Real> permeability = {0.8451e-9, 8.968e-9};
  _permeability_interpolation.setData(sphere_sizes, permeability);

  _use_fluid_mu_interp = initInputData("fluid_viscosity_file", _fluid_mu_interpolation);
  _use_fluid_k_interp = initInputData("fluid_thermal_conductivity_file", _fluid_k_interpolation);
  _use_fluid_rho_interp = initInputData("fluid_density_file", _fluid_rho_interpolation);
  _use_fluid_cp_interp = initInputData("fluid_specific_heat_file", _fluid_cp_interpolation);

  _use_solid_k_interp = initInputData("solid_thermal_conductivity_file", _solid_k_interpolation);
  _use_solid_rho_interp = initInputData("solid_density_file", _solid_rho_interpolation);
  _use_solid_cp_interp = initInputData("solid_specific_heat_file", _solid_cp_interpolation);
}

void
PackedColumn::computeQpProperties()
{
  ADReal temp = _temperature[_qp] - 273.15;
  // Permeability //
  Real radius_value = _input_radius.value(_t, _q_point[_qp]);
  mooseAssert(radius_value >= 1 && radius_value <= 3,
              "radius must be between 1,3 but " << radius_value << " was provided.");
  _permeability[_qp] = _permeability_interpolation.sample(radius_value);
  // Porosity //
  Real porosity_value = _input_porosity.value(_t, _q_point[_qp]);
  mooseAssert(input_porosity >= 0 && input_porosity <= 1,
              "porosity must be between 0,1 but " << porosity_value << " provided.");
  _porosity[_qp] = porosity_value;
  // Fluid Properties //
  _viscosity[_qp] = _use_fluid_mu_interp ? _fluid_mu_interpolation.sample(temp) : _fluid_mu;
  ADReal fluid_k = _use_fluid_k_interp ? _fluid_k_interpolation.sample(temp) : _fluid_k;
  ADReal fluid_rho = _use_fluid_rho_interp ? _fluid_rho_interpolation.sample(temp) : _fluid_rho;
  ADReal fluid_cp = _use_fluid_cp_interp ? _fluid_cp_interpolation.sample(temp) : _fluid_cp;
  // Solid Properties //
  ADReal solid_k = _use_solid_k_interp ? _solid_k_interpolation.sample(temp) : _solid_k;
  ADReal solid_rho = _use_solid_rho_interp ? _solid_rho_interpolation.sample(temp) : _solid_rho;
  ADReal solid_cp = _use_solid_cp_interp ? _solid_cp_interpolation.sample(temp) : _solid_cp;
  // Determine the combined mixture properties based on porosity //
  _thermal_conductivity[_qp] = _porosity[_qp] * fluid_k + (1 - _porosity[_qp]) * solid_k;
  _density[_qp] = _porosity[_qp] * fluid_rho + (1 - _porosity[_qp]) * solid_rho;
  _specific_heat[_qp] = _porosity[_qp] * fluid_cp + (1 - _porosity[_qp]) * solid_cp;
}

bool
PackedColumn::initInputData(const std::string & param_name, ADLinearInterpolation & interp)
{
  if (isParamValid(param_name))
  {
    const std::string & filename = getParam<FileName>(param_name);
    MooseUtils::DelimitedFileReader reader(filename, &_communicator);
    reader.setComment("#");
    reader.read();
    interp.setData(reader.getData(0), reader.getData(1));
    return true;
  }
  return false;
}
