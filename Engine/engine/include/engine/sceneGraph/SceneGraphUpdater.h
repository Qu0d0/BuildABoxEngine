#pragma once
#include <glm/gtx/euler_angles.hpp>

#include "engine/Game.h"
#include "engine/ecs/System.h"
#include "Transform.h"

using gl3::engine::ecs::System;
using gl3::engine::Game;
using gl3::engine::sceneGraph::Transform;

namespace gl3::engine::sceneGraph {
    class SceneGraphUpdater : public System {
    public:
        explicit SceneGraphUpdater(Game &game) : System(game) {
            game.onUpdate.addListener([&](Game &) {
                updateTransforms(game);
            });
        }

        static void updateTransforms(Game &game) {
            game.componentManager.forEachComponent<Transform>([&](Transform &transform) {
                transform.modelMatrix = calculateModelMatrix(transform);
            });
        }

    private:
        static glm::mat4 calculateModelMatrix(Transform &transform) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform.localPosition);
            model = glm::scale(model, transform.localScale);
            model *= glm::eulerAngleYXZ(glm::radians(transform.localRotation.y),
                                        glm::radians(transform.localRotation.x),
                                        glm::radians(transform.localRotation.z));
            return model;
        }
    };
}