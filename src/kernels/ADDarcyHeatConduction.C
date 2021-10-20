#include "ADDarcyHeatConduction.h"

registerMooseObject("gzlApp", ADDarcyHeatConduction);

InputParameters
ADDarcyHeatConduction::validParams()
{
  auto params = ADDiffusion::validParams();
  params.addClassDescription("Computes heat conduction in the fluid in 3d ");
  return params;
}

ADDarcyHeatConduction::ADDarcyHeatConduction(const InputParameters & params)
  : ADDiffusion(params), _thermal_conductivity(getADMaterialProperty<Real>("thermal_conductivity"))
{
}

ADRealVectorValue
ADDarcyHeatConduction::precomputeQpResidual()
{
  return _thermal_conductivity[_qp] * ADDiffusion::precomputeQpResidual();
}
