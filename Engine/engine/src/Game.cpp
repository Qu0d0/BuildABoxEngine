#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/Game.h"
#include "engine/sceneGraph/SceneGraphUpdater.h"
#include "engine/sceneGraph/SceneGraphPruner.h"
#include "engine/renderer/rendererComponents/CameraComponent.h"
#include "engine/EngineAccessor.h"

namespace gl3::engine {
    using Context = engine::context::Context;
    using ecs::ComponentManager;
    using ecs::EntityManager;
    using sceneGraph::SceneGraphUpdater;
    using sceneGraph::SceneGraphPruner;

    Game::Game(int width, int height, const std::string &title) :
            context(width, height, title),
            componentManager(*this),
            entityManager(componentManager, *this)
            {
        EngineAccessor::getEngineAccessor()->entityManager = &entityManager;
        EngineAccessor::getEngineAccessor()->componentManager = &componentManager;
        EngineAccessor::getEngineAccessor()->game = this;
        audio.init();
        audio.setGlobalVolume(0.1f);
        origin = &entityManager.createEntity().addComponent<Transform>();
    }

    void Game::run() {
        SceneGraphUpdater sceneGraphUpdater(*this);
        SceneGraphPruner sceneGraphPruner(*this);
        onStartup.invoke(*this);
        createCamera();
        start();
        onAfterStartup.invoke(*this);
        sceneGraphUpdater.updateTransforms(*this);

        context.run([this](Context &ctx){
            onBeforeUpdate.invoke(*this);
            update(getWindow());
            onUpdate.invoke(*this);
            draw();
            onDraw.invoke(*this);
            drawUI();
            updateDeltaTime();
            onAfterUpdate.invoke(*this);
        });

        onBeforeShutdown.invoke(*this);
        onShutdown.invoke(*this);
    }


    void Game::updateDeltaTime() {
        float frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    void Game::createCamera() {
        camera = &entityManager.createEntity();
        camera->addComponent<Transform>(origin, glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
        camera->addComponent<CameraComponent>();
    }

    Game::~Game() {
        context.~Context();
    }

}