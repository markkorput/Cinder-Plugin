#pragma once

#include <string>

namespace CinderPlugin {
  namespace types {
    class NamedPluginBase {
        virtual std::string getName() const = 0;
    };
  }
}
