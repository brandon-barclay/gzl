#include "HeatConductionOutflow.h"

registerMooseObject("gzlApp", HeatConductionOutflow);

InputParameters
HeatConductionOutflow::validParams()
{
  auto params = ADIntegratedBC::validParams();
  params.addClassDescription("No BC BC");
  return params;
}

HeatConductionOutflow::HeatConductionOutflow(const InputParameters & params)
  : ADIntegratedBC(params),
    _thermal_conductivity(getADMaterialProperty<Real>("thermal_conductivity"))
{
}

ADReal
HeatConductionOutflow::computeQpResidual()
{
  return -_test[_i][_qp] * _thermal_conductivity[_qp] * _grad_u[_qp] * _normals[_qp];
}
