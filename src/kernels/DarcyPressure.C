#include "DarcyPressure.h"

registerMooseObject("gzlApp", DarcyPressure);

InputParameters
DarcyPressure::validParams()
{
  auto params = ADKernel::validParams();
  params.addClassDescription("Diffusion kernel which describes the darcy pressure equation");
  return params;
}

DarcyPressure::DarcyPressure(const InputParameters & params)
  : ADKernel(params),
    _permeability(getADMaterialProperty<Real>("permeability")),
    _viscosity(getADMaterialProperty<Real>("viscosity"))
{
}

ADReal
DarcyPressure::computeQpResidual()
{
  return (_permeability[_qp] / _viscosity[_qp]) * _grad_test[_i][_qp] * _grad_u[_qp];
}
