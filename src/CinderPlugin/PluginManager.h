//
//  PluginManager.hpp
//  exampleApp
//
//  Created by Mark van de Korput on 16-12-25.
//
//

#ifndef PluginManager_h
#define PluginManager_h

#include "cinder/Cinder.h"
#include "cinder/Log.h"

#include "Interface.h"
#include "Context.h"
#include "LibManager.h"

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <dlfcn.h>
#define GetProcAddress(DLL, NAME) dlsym(DLL, NAME)
#endif

using namespace cinder;

namespace CinderPlugin {
    
    template<typename PluginBaseType>
    class PluginManager {
        
    public: // methods
        const std::deque<std::shared_ptr<PluginBaseType>> &getPlugins(){ return mPlugins; }
        
        typedef Interface<PluginBaseType>*(*GetPluginInterfaceType)(Context &context);
        
        Interface<PluginBaseType>* loadFile(fs::path path){
            auto libItem = mLibManager.load(path);

            if(libItem == nullptr)
                return nullptr;
            
            auto getPluginInterfaceFunc = (GetPluginInterfaceType)GetProcAddress(libItem->dll, "getPluginInterface");
            if(!getPluginInterfaceFunc){
                CI_LOG_W("Library didn't have getPluginInterface function");
                return nullptr;
            }
            
            Context c;
            auto plugin_interface = getPluginInterfaceFunc(c);
            auto plugins = plugin_interface->getPlugins();
            CI_LOG_I("Found " + std::to_string(plugins.size()) + " plugins in lib file");

            for(auto it = plugins.begin(); it != plugins.end(); it++){
                mPlugins.push_back(*it);
            }
            
            return plugin_interface;
        }
        
    private: // attributes
        LibManager mLibManager;
        std::deque<std::shared_ptr<PluginBaseType>> mPlugins;
    };
}

#endif /* PluginManager_h */
