#pragma once

#include "ADIntegratedBC.h"

class HeatConductionOutflow : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  HeatConductionOutflow(const InputParameters & params);

protected:
  virtual ADReal computeQpResidual() override;

  const ADMaterialProperty<Real> & _thermal_conductivity;
};
