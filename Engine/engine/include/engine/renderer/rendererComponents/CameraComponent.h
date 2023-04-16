//
// Created by Oddball on 10/11/2022.
//
#pragma once
#include "glm/mat4x4.hpp"
#include "engine/ecs/Component.h"
#include <glm/gtc/matrix_transform.hpp>

using gl3::engine::ecs::Component;
using gl3::engine::ecs::ComponentManager;
using gl3::engine::ecs::guid_t;
using gl3::engine::ecs::Entity;

struct CameraComponent : Component {
    friend ComponentManager;
    friend Entity;

    glm::vec3 eye = glm::vec3(0.0, 0.0, 2.0f);
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

    glm::mat4 projection = glm::perspective(glm::radians(60.0f), 1000.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 getView(){
        return glm::lookAt(eye,center,up);
    }

private:
    explicit CameraComponent(guid_t owner) : Component(owner){}
};