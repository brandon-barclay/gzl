//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "gzlTestApp.h"
#include "gzlApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
gzlTestApp::validParams()
{
  InputParameters params = gzlApp::validParams();
  return params;
}

gzlTestApp::gzlTestApp(InputParameters parameters) : MooseApp(parameters)
{
  gzlTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

gzlTestApp::~gzlTestApp() {}

void
gzlTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  gzlApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"gzlTestApp"});
    Registry::registerActionsTo(af, {"gzlTestApp"});
  }
}

void
gzlTestApp::registerApps()
{
  registerApp(gzlApp);
  registerApp(gzlTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
gzlTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  gzlTestApp::registerAll(f, af, s);
}
extern "C" void
gzlTestApp__registerApps()
{
  gzlTestApp::registerApps();
}
