#include "CinderPlugin.h"

using namespace CinderPlugin;

class CustomPlugin : public types::NamedPluginBase {
    std::string getName() const override { return "CustomPlugin"; }
};

extern "C" {
    Interface<types::NamedPluginBase>* getPluginInterface(Context &context){
        auto interface = new Interface<types::NamedPluginBase>();
        interface->add<CustomPlugin>();
        return interface;
    }
}