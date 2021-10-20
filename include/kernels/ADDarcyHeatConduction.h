#pragma once

#include "ADDiffusion.h"

class ADDarcyHeatConduction : public ADDiffusion
{
public:
  static InputParameters validParams();

  ADDarcyHeatConduction(const InputParameters & params);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  const ADMaterialProperty<Real> & _thermal_conductivity;
};
