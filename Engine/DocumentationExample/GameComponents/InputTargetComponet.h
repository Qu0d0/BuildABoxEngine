#pragma once

#include "engine/ecs/Component.h"

using gl3::engine::ecs::Component;
using gl3::engine::ecs::ComponentManager;
using gl3::engine::ecs::guid_t;
using gl3::engine::ecs::Entity;

struct InputTargetComponent: Component {
    friend ComponentManager;
    friend Entity;

private:
    explicit InputTargetComponent(guid_t owner) : Component(owner){}
};