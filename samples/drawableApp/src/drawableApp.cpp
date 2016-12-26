#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "CinderPlugin.h"

#include "drawable.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class drawableApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void fileDrop( FileDropEvent event ) override;
    
private:
    CinderPlugin::PluginManager<Drawable> mPluginManager;
    
};

void drawableApp::setup()
{
}

void drawableApp::mouseDown( MouseEvent event )
{
}

void drawableApp::update()
{
}

void drawableApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    cinder::gl::pushMatrices();
    translate(vec3(100.0f, 100.0f, 0.0f));
    for(auto plugin : mPluginManager.getPlugins()){
        plugin->draw();
        translate(vec3(100.0f, 100.0f, 0.0f));
    }
    cinder::gl::popMatrices();
}

void drawableApp::fileDrop( FileDropEvent event )
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
}


CINDER_APP( drawableApp, RendererGl )
