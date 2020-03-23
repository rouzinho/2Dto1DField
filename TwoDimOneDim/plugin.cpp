#include "plugin.h"
#include "TwoDimOneDim.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <TwoDimOneDim>("Utilities")
    );
    plugin->add(summation_decl);
}
