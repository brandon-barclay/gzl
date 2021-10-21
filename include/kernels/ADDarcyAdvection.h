#pragma once

#include "ADKernelValue.h"

class ADDarcyAdvection : public ADKernelValue
{
public:
  static InputParameters validParams();

  ADDarcyAdvection(const InputParameters & params);

protected:
  ADReal precomputeQpResidual() override;

  const ADVariableGradient & _pressure_gradient;

  const ADMaterialProperty<Real> & _permeability;
  const ADMaterialProperty<Real> & _porosity;
  const ADMaterialProperty<Real> & _viscosity;
  const ADMaterialProperty<Real> & _density;
  const ADMaterialProperty<Real> & _specific_heat;
};
