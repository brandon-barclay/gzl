#pragma once

#include "ADMaterial.h"

#include "LinearInterpolation.h"

class PackedColumn : public ADMaterial
{
public:
  static InputParameters validParams();

  PackedColumn(const InputParameters & params);

protected:
  virtual void computeQpProperties() override;

  bool initInputData(const std::string & param_name, ADLinearInterpolation & interp);

  const Function & _input_radius;

  const Function & _input_porosity;

  const ADVariableValue & _temperature;
  /// Permeability based on the radius ///
  LinearInterpolation _permeability_interpolation;

  /// Fluid Properties ///
  bool _use_fluid_mu_interp;
  const Real & _fluid_mu;
  ADLinearInterpolation _fluid_mu_interpolation;

  bool _use_fluid_k_interp = false;
  const Real & _fluid_k;
  ADLinearInterpolation _fluid_k_interpolation;

  bool _use_fluid_rho_interp = false;
  const Real & _fluid_rho;
  ADLinearInterpolation _fluid_rho_interpolation;

  bool _use_fluid_cp_interp;
  const Real & _fluid_cp;
  ADLinearInterpolation _fluid_cp_interpolation;

  /// Solid Properties
  bool _use_solid_k_interp = false;
  const Real & _solid_k;
  ADLinearInterpolation _solid_k_interpolation;

  bool _use_solid_cp_interp;
  const Real & _solid_cp;
  ADLinearInterpolation _solid_cp_interpolation;

  bool _use_solid_rho_interp;
  const Real & _solid_rho;
  ADLinearInterpolation _solid_rho_interpolation;

  ADMaterialProperty<Real> & _permeability;
  ADMaterialProperty<Real> & _porosity;
  ADMaterialProperty<Real> & _viscosity;
  ADMaterialProperty<Real> & _thermal_conductivity;
  ADMaterialProperty<Real> & _specific_heat;
  ADMaterialProperty<Real> & _density;
};
