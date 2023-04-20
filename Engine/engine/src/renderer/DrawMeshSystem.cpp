#pragma once
#include "engine/renderer/rendererSystems/DrawMeshSystem.h"

void DrawMeshSystem::drawMesh(Game &game) {

    game.componentManager.forEachComponent<MeshComponent>([&](MeshComponent &meshComponent) {

        Entity &entity = game.entityManager.getEntity(meshComponent.entity());
        Transform &transform = entity.getComponent<Transform>();
        glm::vec3 position = transform.getWorldPosition();

        auto mvpMatrix = calculateMvpMatrix(game.camera,
                                            position,
                                            transform.getWorldRotationMatrix(),
                                            transform.getWorldScale());


        ShaderComponent &shaderComponent = entity.getComponent<ShaderComponent>();
        shaderComponent.use();
        shaderComponent.setMatrix("mvp", mvpMatrix);
        shaderComponent.setMatrix("modelToWorldNormal", calculateModelToWorldNormal(transform));
        shaderComponent.setVector("color", {1, 1, 1, 1});

        //texture
        if (entity.hasComponent<MaterialComponent>()) {
            shaderComponent.setTextrue("tex0");
            MaterialComponent &materialComponent = entity.getComponent<MaterialComponent>();
            materialComponent.bindTexture();
        }
        meshComponent.draw();
    });
}

glm::mat4 DrawMeshSystem::calculateModelToWorldNormal(Transform &transform) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 position = transform.getWorldPosition();
    model = glm::translate(model, position);
    model = glm::scale(model, transform.getWorldScale());
    model *= transform.getWorldRotationMatrix();
    return glm::transpose(glm::inverse(model));
}

glm::mat4 DrawMeshSystem::calculateMvpMatrix(Entity *camera, glm::vec3 position, glm::mat4 rotationMatrix, glm::vec3 scale) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model *= rotationMatrix;
    glm::mat4 view = camera->getComponent<CameraComponent>().getView();
    glm::mat4 projection = camera->getComponent<CameraComponent>().projection;
    return projection * view * model;
}
