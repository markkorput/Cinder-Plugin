//
//  LibManager.cpp
//  exampleApp
//
//  Created by Mark van de Korput on 16-12-25.
//
//

#include "LibManager.h"
#include "cinder/Log.h"

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <dlfcn.h>
#define FreeLibrary(DLL) dlclose(DLL)
#endif

using namespace CinderPlugin;
using namespace cinder;

void LibManager::destroy(){
    unloadAll();
}

//----------
// from http://www.codeproject.com/Tips/479880/GetLastError-as-std-string
std::string LibManager::GetLastErrorStdStr()
{
#ifdef _MSC_VER
    DWORD error = GetLastError();
    if (error)
    {
        LPVOID lpMsgBuf;
        DWORD bufLen = FormatMessageA(
                                      FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                      FORMAT_MESSAGE_FROM_SYSTEM |
                                      FORMAT_MESSAGE_IGNORE_INSERTS,
                                      NULL,
                                      error,
                                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                      (LPSTR)&lpMsgBuf,
                                      0, NULL);
        if (bufLen)
        {
            LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
            std::string result(lpMsgStr, lpMsgStr + bufLen);
            
            LocalFree(lpMsgBuf);
            
            return result;
        }
    }
#else
    char *error = dlerror();
    if (error)
    {
        return error;
    }
#endif
    return std::string();
}

//----------
///Load any factories from the plugin which match this FactoryRegister
LibItemPtr LibManager::load(fs::path path, bool verbose) {
//    //transform path to data path
//    if (path.is_relative()) {
//        path = std::string(ofToDataPath("")) / path;
//    }
    
    //attempt to load DLL
#ifdef _MSC_VER
    auto dll = LoadLibraryW(path.c_str());
#else
    auto dll = dlopen(path.c_str(), RTLD_LAZY);
#endif
    if (!dll) {
        auto errorMessage = GetLastErrorStdStr();
        CI_LOG_W("Failed to open dynamic library file [ " + path.string() + "]. " + errorMessage);
        return nullptr;
    }
    
    LibItemPtr libItem = std::make_shared<LibItem>();
    libItem->dll = dll;
    libItem->path = path;
    libItems.push_back(libItem);
//    ofNotifyEvent(loadEvent, libItem);
    return libItem;
}

void LibManager::unload(fs::path path){
    for(auto it = libItems.begin(); it != libItems.end(); it++){
        if((*it)->path == path){
            unload(it);
            return;
        }
    }
}

void LibManager::unload(void * dll){
    for(auto it = libItems.begin(); it != libItems.end(); it++){
        if((*it)->dll == dll){
            unload(it);
            return;
        }
    }
}

void LibManager::unload(LibItemPtr libItem){
    unload(find(libItems.begin(), libItems.end(), libItem));
}

void LibManager::unloadAll(){
    while(!libItems.empty())
        unload(libItems.begin());
}

void LibManager::unload(std::deque<LibItemPtr>::iterator it){
    if(it == libItems.end()) return;
    CI_LOG_V("unloading lib: " + (*it)->path.string());
    
    libItems.erase(it);
//    ofNotifyEvent(unloadEvent, (*it));
    
    FreeLibrary((*it)->dll);
}