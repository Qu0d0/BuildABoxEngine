#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <soloud.h>
#include <soloud_wav.h>


#include "engine/Context.h"
#include "engine/Events.h"
#include "engine/ecs/ComponentManager.h"
#include "engine/ecs/EntityManager.h"
#include "engine/sceneGraph/Transform.h"

using gl3::engine::sceneGraph::Transform;

namespace gl3::engine {
    namespace ecs {
        class EntityManager;
        class ComponentManager;
    }

    class Game {
    public:
        using event_t = events::Event<Game, Game&>;

        void run();
        glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);
        glm::mat4 calculateMvpMatrixNew(glm::vec3 position, glm::mat4 rotationMatrix, glm::vec3 scale);
        GLFWwindow *getWindow() { return context.getWindow(); }

        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        event_t onUpdate;
        event_t onAfterUpdate;
        event_t onDraw;
        event_t onBeforeShutdown;
        event_t onShutdown;

        ecs::ComponentManager componentManager;
        ecs::EntityManager entityManager;
        Transform *origin = nullptr;

        Entity *camera;

        float getDeltaTime(){return deltaTime;}

    protected:
        Game(int width, int height, const std::string &title);
        virtual void start() {}
        virtual void update(GLFWwindow *window) {}
        virtual void draw() {}
        virtual void drawUI() {}
        virtual ~Game();

        SoLoud::Soloud audio;
        //Initial value
        float deltaTime = 1.0f / 60;

    private:
        void updateDeltaTime();

        void createCamera();

        context::Context context;
        //Initial value
        float lastFrameTime = 1.0f / 60;
    };
}
