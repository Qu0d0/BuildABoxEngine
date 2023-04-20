#pragma once
#include "engine/ecs/EntityManager.h"

namespace gl3::engine{
    class EngineAccessor
    {
    public:
        static EngineAccessor* getEngineAccessor();

        ecs::EntityManager* entityManager = nullptr;
        ecs::ComponentManager* componentManager = nullptr;
        Game* game = nullptr;


    protected:
        EngineAccessor() {}

    private:
        static EngineAccessor *instance;
    };
}


