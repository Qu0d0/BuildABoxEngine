#include "ObjectRotatorSystem.h"

void ObjectRotatorSystem::processInput(Game &game) {
    game.componentManager.forEachComponent<RotatorComponent>([&](RotatorComponent &rotatorComponent) {

        Entity &entity = game.entityManager.getEntity(rotatorComponent.entity());
        if (entity.hasComponent<Transform>()) {
            Transform &entityTransform = entity.getComponent<Transform>();


            if (glfwGetKey(game.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
                RoateEntityOnY(game, entityTransform, rotatorComponent.baseRotationSpeed);
            }

            if (glfwGetKey(game.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
                RoateEntityOnY(game, entityTransform, -rotatorComponent.baseRotationSpeed);
            }


        }
    });
}


void ObjectRotatorSystem::RoateEntityOnY(Game &game, Transform &entityTransform, float speed) {
    entityTransform.localRotation.y += speed * game.getDeltaTime();
}