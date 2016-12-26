#include "CinderPlugin/PluginEssentials.h"
#include "../../drawableApp/include/drawable.h"

#include "cinder/gl/gl.h"

using namespace CinderPlugin;

using namespace ci;
using namespace std;

class PluginDrawable : public Drawable{
public:
    void draw() override {
        cinder::gl::drawSolidCircle(vec2(0.0f,0.0f), 100.0f);
    }
};

extern "C" {
    Interface<Drawable>* getPluginInterface(Context &context){
        auto interface = new Interface<Drawable>();
        interface->add<PluginDrawable>();
        return interface;
    }
}