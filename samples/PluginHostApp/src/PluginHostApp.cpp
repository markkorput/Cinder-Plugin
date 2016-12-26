#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "CinderPlugin.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace CinderPlugin;

class PluginHostApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void fileDrop( FileDropEvent event ) override;

private:
    PluginManager<types::NamedPluginBase> mPluginManager;
};

void PluginHostApp::setup()
{
}

void PluginHostApp::mouseDown( MouseEvent event )
{
}

void PluginHostApp::update()
{
}

void PluginHostApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

void PluginHostApp::fileDrop( FileDropEvent event )
{
#ifdef _WIN32
    string extension = ".dll";
#else
    string extension = ".dylib";
#endif

    for(auto file : event.getFiles()){
        if(file.extension() == extension){
            mPluginManager.loadFile(file);
        }
    }

    CI_LOG_I("Plugins:");
    auto plugins = mPluginManager.getPlugins();
    for(auto plugin : plugins){
        CI_LOG_I(plugin->getName());
    }
}

CINDER_APP( PluginHostApp, RendererGl )
