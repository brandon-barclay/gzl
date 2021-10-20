#include "DarcyVelocity.h"

registerMooseObject("gzlApp", DarcyVelocity);

InputParameters
DarcyVelocity::validParams()
{
  auto params = VectorAuxKernel::validParams();
  params.addRequiredCoupledVar("pressure", "the pressure field creating the velocity field");
  return params;
}

DarcyVelocity::DarcyVelocity(const InputParameters & params)
  : VectorAuxKernel(params),
    _pressure_gradient(coupledGradient("pressure")),
    _permeability(getADMaterialProperty<Real>("permeability")),
    _viscosity(getADMaterialProperty<Real>("viscosity"))
{
}

RealVectorValue
DarcyVelocity::computeValue()
{
  return -MetaPhysicL::raw_value(_permeability[_qp] / _viscosity[_qp]) * _pressure_gradient[_qp];
}
