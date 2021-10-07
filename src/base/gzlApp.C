#include "gzlApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
gzlApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  // Do not use legacy material output, i.e., output properties on INITIAL as well as TIMESTEP_END
  params.set<bool>("use_legacy_material_output") = false;

  return params;
}

gzlApp::gzlApp(InputParameters parameters) : MooseApp(parameters)
{
  gzlApp::registerAll(_factory, _action_factory, _syntax);
}

gzlApp::~gzlApp() {}

void
gzlApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"gzlApp"});
  Registry::registerActionsTo(af, {"gzlApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
gzlApp::registerApps()
{
  registerApp(gzlApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
gzlApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  gzlApp::registerAll(f, af, s);
}
extern "C" void
gzlApp__registerApps()
{
  gzlApp::registerApps();
}
