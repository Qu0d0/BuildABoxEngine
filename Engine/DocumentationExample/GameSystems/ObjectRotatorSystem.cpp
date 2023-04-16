//
// Created by Quirin on 16.04.2023.
//

#include "ObjectRotatorSystem.h"

void ObjectRotatorSystem::processInput(Game &game) {
    game.componentManager.forEachComponent<InputTargetComponent>([&](InputTargetComponent &inputTarget) {

        if (glfwGetKey(game.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            RoateEntityOnY(game, inputTarget, 35.0f);
        }

        if (glfwGetKey(game.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            RoateEntityOnY(game, inputTarget, -35.0f);
        }
    });
}

void ObjectRotatorSystem::RoateEntityOnY(Game &game, InputTargetComponent &inputTarget, float speed){
    Entity &entity = game.entityManager.getEntity(inputTarget.entity());
    if(entity.hasComponent<Transform>()){
        Transform &entityTransform = entity.getComponent<Transform>();
        entityTransform.localRotation.y += speed * game.getDeltaTime();
    }
}