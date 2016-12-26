#include "CinderPlugin/PluginEssentials.h"
#include "CinderPlugin/types/NamedPluginBase.h"

using namespace CinderPlugin;

class CustomPlugin : public types::NamedPluginBase {
    std::string getName() const override { return "CustomPlugin"; }
};

class AdditionalPlugin : public types::NamedPluginBase {
    std::string getName() const override { return "AdditionalPlugin"; }
};

extern "C" {
    Interface<types::NamedPluginBase>* getPluginInterface(Context &context){
        auto interface = new Interface<types::NamedPluginBase>();
        interface->add<CustomPlugin>();
        interface->add<AdditionalPlugin>();
        return interface;
    }
}