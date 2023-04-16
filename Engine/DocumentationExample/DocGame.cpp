#include "DocGame.h"
#include "engine/renderer/rendererComponents/MeshComponent.h"
#include "engine/renderer/rendererComponents/ShaderComponent.h"
#include "engine/renderer/rendererComponents/MaterialComponent.h"
#include "engine/renderer/rendererComponents/CameraComponent.h"
#include "GameComponents/InputTargetComponet.h"

void DocGame::start() {
    Transform &gameObjectTransform = entityManager.createEntity().addComponent<Transform>(origin,
                                                                                               glm::vec3(0, -1.0f, 0),
                                                                                               glm::vec3(-90.0f, 0.0f, 0),
                                                                                               glm::vec3(1, 1, 1));
    Entity &gameObject = entityManager.getEntity(gameObjectTransform.entity());
    gameObject.addComponent<MeshComponent>("gltf/hog.glb");
    gameObject.addComponent<ShaderComponent>("shaders/shaded/vertexShaderTextured.vert", "shaders/shaded/fragmentShaderTextured.frag");
    gameObject.addComponent<MaterialComponent>("textures/hog.png", true);
    gameObject.addComponent<InputTargetComponent>();


    camera->getComponent<CameraComponent>().eye = {0.0f, 1.0f,6.0f};
    camera->getComponent<CameraComponent>().center = {0.0f, 0.0f,0.0f};

    initSystems();
}

void DocGame::initSystems() {
    objectRotatorSystem = std::make_unique<ObjectRotatorSystem>(*this);
    drawMeshSystem = std::make_unique<DrawMeshSystem>(*this);
}
