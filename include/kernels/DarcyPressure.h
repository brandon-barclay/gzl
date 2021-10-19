#pragma once

#include "ADKernel.h"

class DarcyPressure : public ADKernel
{
public:
  static InputParameters validParams();

  DarcyPressure(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real & _permeability;
  const Real & _viscosity;
};
