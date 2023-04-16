#pragma once
#include <iostream>
#include "engine/ecs/System.h"
#include "engine/renderer/rendererComponents/MeshComponent.h"
#include "engine/renderer/rendererComponents/ShaderComponent.h"
#include "engine/renderer/rendererComponents/CameraComponent.h"
#include "engine/renderer/rendererComponents/MaterialComponent.h"

using gl3::engine::ecs::System;
using gl3::engine::Game;
using gl3::engine::sceneGraph::Transform;

class DrawMeshSystem : public System {
public:

    explicit DrawMeshSystem(Game &game) : System(game) {
        game.onDraw.addListener([&](Game&) {
            drawMesh(game);
        });
    }

    static void drawMesh(Game &game);

    static glm::mat4 calculateModelToWorldNormal(Transform &transform);

    static glm::mat4 calculateMvpMatrix(Entity *camera, glm::vec3 position, glm::mat4 rotationMatrix, glm::vec3 scale);
};