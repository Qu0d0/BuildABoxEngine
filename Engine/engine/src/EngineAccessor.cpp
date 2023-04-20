#include "engine/EngineAccessor.h"
namespace gl3::engine {

    EngineAccessor* EngineAccessor::instance = nullptr;
    EngineAccessor *EngineAccessor::getEngineAccessor() {

            if( instance == nullptr )
                instance = new EngineAccessor();
            return instance;
    }
}