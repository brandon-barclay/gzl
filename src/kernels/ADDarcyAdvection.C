#include "ADDarcyAdvection.h"

registerMooseObject("gzlApp", ADDarcyAdvection);

InputParameters
ADDarcyAdvection::validParams()
{
  auto params = ADKernelValue::validParams();
  params.addRequiredCoupledVar("pressure", "the pressure variable");
  return params;
}

ADDarcyAdvection::ADDarcyAdvection(const InputParameters & params)
  : ADKernelValue(params),
    _pressure_gradient(adCoupledGradient("pressure")),
    _permeability(getADMaterialProperty<Real>("permeability")),
    _porosity(getADMaterialProperty<Real>("porosity")),
    _viscosity(getADMaterialProperty<Real>("viscosity")),
    _density(getADMaterialProperty<Real>("density")),
    _specific_heat(getADMaterialProperty<Real>("specific_heat"))
{
}

ADReal
ADDarcyAdvection::precomputeQpResidual()
{
  ADRealVectorValue superficial_velocity =
      _porosity[_qp] * -(_permeability[_qp] / _viscosity[_qp]) * _pressure_gradient[_qp];

  return _density[_qp] * _specific_heat[_qp] * superficial_velocity * _grad_u[_qp];
  // I guess those other things are of type ADRealVectorValue and theres some
  // kind of operator overloading?
}
