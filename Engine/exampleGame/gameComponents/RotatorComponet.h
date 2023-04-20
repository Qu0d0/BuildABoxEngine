#pragma once

#include "engine/ecs/Component.h"

using gl3::engine::ecs::Component;
using gl3::engine::ecs::ComponentManager;
using gl3::engine::ecs::guid_t;
using gl3::engine::ecs::Entity;

struct RotatorComponent: Component {
    friend ComponentManager;
    friend Entity;

    float baseRotationSpeed;

private:
    explicit RotatorComponent(guid_t owner, float baseRotationSpeed) : Component(owner), baseRotationSpeed(baseRotationSpeed){}
};