#pragma once
#include <iostream>
#include <cmath>
#include "engine/ecs/System.h"
#include "engine/Game.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"
#include "../GameComponents/RotatorComponet.h"

using gl3::engine::ecs::System;
using gl3::engine::Game;
using gl3::engine::ecs::Entity;
using gl3::engine::sceneGraph::Transform;

class ObjectRotatorSystem : public System {
public:

    explicit ObjectRotatorSystem(Game &game) : System(game) {
        game.onUpdate.addListener([&](Game&) {
            processInput(game);
        });
    }

private:
    void processInput(Game &game);
    void RoateEntityOnY(Game &game, Transform &transform, float speed);
};