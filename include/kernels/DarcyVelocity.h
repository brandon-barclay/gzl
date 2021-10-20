#pragma once

#include "AuxKernel.h"

class DarcyVelocity : public VectorAuxKernel
{
public:
  static InputParameters validParams();

  DarcyVelocity(const InputParameters & params);

protected:
  virtual RealVectorValue computeValue() override;

  const VariableGradient & _pressure_gradient;

  const ADMaterialProperty<Real> & _permeability;
  const ADMaterialProperty<Real> & _viscosity;
};
