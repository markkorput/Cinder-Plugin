#pragma once

#include <string>

namespace CinderPlugin {
  namespace types {
    class NamedPluginBase {
    public:
        virtual std::string getName() const = 0;
    };
  }
}
