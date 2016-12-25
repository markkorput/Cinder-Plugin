#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PluginHostAppApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void PluginHostAppApp::setup()
{
}

void PluginHostAppApp::mouseDown( MouseEvent event )
{
}

void PluginHostAppApp::update()
{
}

void PluginHostAppApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( PluginHostAppApp, RendererGl )
