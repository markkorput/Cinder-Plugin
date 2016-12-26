#include "cinder/app/App.h"
#include "cinder/app/Platform.h"
#include "catch.hpp"

#include "CinderPlugin/Interface.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace CinderPlugin;

class BaseType {
public:
    virtual string getName(){ return "BaseType"; }
};

class ChildAType : public BaseType{
public:
    string getName() override { return "ChildAType"; }
};

class ChildBType : public BaseType{
public:
    string getName() override { return "ChildBType"; }
};


TEST_CASE("Interface", "")
{
	SECTION("plugins")
	{
        Interface<BaseType> interface;
        CHECK(interface.getPlugins().size() == 0);
        interface.add<ChildAType>();
        CHECK(interface.getPlugins().size() == 1);
        interface.add<ChildBType>();
        CHECK(interface.getPlugins().size() == 2);
        CHECK(interface.getPlugins()[0]->getName() == "ChildAType");
        CHECK(interface.getPlugins()[1]->getName() == "ChildBType");

    }
}