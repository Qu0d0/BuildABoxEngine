//
// Created by Oddball on 27/10/2022.
//
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

    static void drawMesh(Game &game) {
        game.componentManager.forEachComponent<MeshComponent>([&](MeshComponent &meshComponent) {
            Entity &entity = game.entityManager.getEntity(meshComponent.entity());
            Transform &meshComponentTransform = entity.getComponent<Transform>();
            glm::vec3 position = meshComponentTransform.getWorldPosition();

            auto mvpMatrix = calculateMvpMatrix(game.camera,
                                                position,
                                                meshComponentTransform.getWorldRotationMatrix(),
                                                meshComponentTransform.getWorldScale());

            ShaderComponent &shaderComponent = entity.getComponent<ShaderComponent>();
            shaderComponent.use();
            shaderComponent.setMatrix("mvp", mvpMatrix);
            shaderComponent.setMatrix("modelToWorldNormal", calculateModelToWorldNormal2( meshComponentTransform));
            shaderComponent.setVector("color", {1, 1, 1, 1});
            //texture
            if(entity.hasComponent<MaterialComponent>()){
                shaderComponent.setTextrue("tex0");
                MaterialComponent &materialComponent = entity.getComponent<MaterialComponent>();
                materialComponent.bindTexture();
            }
            meshComponent.draw();
        });
    }


    static glm::mat4 calculateModelToWorldNormal2(Transform &transform) {
        glm::mat4 model = glm::mat4(1.0f);
        glm::vec3 position = transform.getWorldPosition();
        model = glm::translate(model, position);
        model = glm::scale(model, transform.getWorldScale());
        model *= transform.getWorldRotationMatrix();
        return glm::transpose(glm::inverse(model));
    }

    static glm::mat4 calculateMvpMatrix(Entity *camera, glm::vec3 position, glm::mat4 rotationMatrix, glm::vec3 scale) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model *= rotationMatrix;
        glm::mat4 view = camera->getComponent<CameraComponent>().getView();
        glm::mat4 projection = camera->getComponent<CameraComponent>().projection;
        return projection * view * model;
    }
};