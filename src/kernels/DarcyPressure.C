#include "DarcyPressure.h"

registerMooseObject("gzlApp", DarcyPressure);

InputParameters
DarcyPressure::validParams()
{
  auto params = ADKernelGrad::validParams();
  params.addClassDescription("Diffusion kernel which describes the darcy pressure equation");
  params.addRequiredParam<Real>("permeability", "obvious");
  params.addRequiredParam<Real>("viscosity", "obvious");
  return params;
}

DarcyPressure::DarcyPressure(const InputParameters & params)
  : ADKernel(params),
    _permeability(getParam<Real>("permeability")),
    _viscosity(getParam<Real>("viscosity"))
{
}

ADReal
DarcyPressure::computeQpResidual()
{
  return (_permeability / _viscosity) * _grad_test[_i][_qp] * _grad_u[_qp];
}
