#pragma once

#include <vector>
#include <memory>

namespace CinderPlugin {
    
    template<typename PluginBaseType>
    class Interface {

    public:
        const std::vector<std::shared_ptr<PluginBaseType>> &getPlugins(){
            return mPlugins;
        }
        
        void add(std::shared_ptr<PluginBaseType> plugin){
            mPlugins.push_back(plugin);
        }

        template<typename PluginType>
        void add() {
            auto plugin = std::make_shared<PluginType>();
            this->add(std::static_pointer_cast<PluginBaseType>(plugin));
        }
        
    private:
        std::vector<std::shared_ptr<PluginBaseType>> mPlugins;
    };
}