#pragma once
#include <set>
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "engine/ecs/ecs.h"
#include "engine/ecs/Component.h"

using gl3::engine::ecs::Component;
using gl3::engine::ecs::ComponentManager;
using gl3::engine::ecs::Entity;
using gl3::engine::ecs::guid_t;

namespace gl3::engine::sceneGraph {
    class Transform final : public Component {
        friend ComponentManager;
        friend Entity;

    public:
        std::set<Transform *> getChildTransforms();
        Transform *getParent();
        void setParent(Transform *parentTransform);
        void invalidate();

        ~Transform() override;
        Transform(const Transform&) = delete;
        Transform& operator = (const Transform&) = delete;
        Transform& operator = (Transform&&) = delete;
        Transform(Transform &&other) noexcept;

        glm::vec3 localPosition;
        glm::vec3 localRotation;
        glm::vec3 localScale;
        glm::mat4 modelMatrix;

        glm::vec3 getWorldPosition(glm::mat4 parentLocalToWorld = glm::identity<glm::mat4>());
        glm::vec3 getWorldScale(glm::mat4 parentLocalToWorld = glm::identity<glm::mat4>());
        glm::mat4 getWorldRotationMatrix();
        glm::vec3 getForwardVector();

    protected:
        void addChild(Transform *transform);
        void removeChild(Transform *transform);

    private:

        glm::mat4 getWorldMatrix(glm::mat4 parentLocalToWorld = glm::identity<glm::mat4>()) {

            glm::mat localToWorld = modelMatrix * parentLocalToWorld;
            if(parent != nullptr){
                localToWorld = parent->getWorldMatrix(localToWorld);
            }
            return localToWorld;
        }

        explicit Transform(guid_t owner,
                           Transform *parentTransform = nullptr,
                           glm::vec3 position = {0, 0, 0},
                           glm::vec3 rotation = {0, 0, 0},
                           glm::vec3 scale = {1, 1, 1});

        Transform *parent = nullptr;
        std::set<Transform *> children;
    };
}