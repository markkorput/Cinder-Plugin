//
//  LibManager.hpp
//  exampleApp
//
//  Created by Mark van de Korput on 16-12-25.
//
//

#ifndef LibManager_h
#define LibManager_h

#include "cinder/Cinder.h"

namespace CinderPlugin {

    struct LibItem{
        void * dll;
        cinder::fs::path path;
    };
    
    typedef std::shared_ptr<LibItem> LibItemPtr;
    
    class LibManager {
        
    public: // methods
        ~LibManager(){ destroy(); }
        void destroy();
        
        LibItemPtr load(cinder::fs::path path, bool verbose = false);
        void unload(cinder::fs::path path);
        void unload(void * dll);
        void unload(LibItemPtr libItem);
        void unloadAll();
        
    private: // methods
        void unload(std::deque<LibItemPtr>::iterator it);
        static std::string GetLastErrorStdStr();
        
//    public: // events
//        ofEvent<LibItemPtr> loadEvent;
//        ofEvent<LibItemPtr> unloadEvent;
        
    private: // attrs
        std::deque<LibItemPtr> libItems;
    };
}

#endif /* LibManager_h */
