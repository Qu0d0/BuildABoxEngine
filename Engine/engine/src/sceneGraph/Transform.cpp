#include <glm/gtc/matrix_transform.hpp>
#include "engine/sceneGraph/Transform.h"

namespace gl3::engine::sceneGraph {
    Transform::Transform(guid_t owner, Transform *parentTransform, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
            : Component(owner),
              localPosition(position),
              localRotation(rotation),
              localScale(scale),
              modelMatrix(glm::identity<glm::mat4>()) {
        setParent(parentTransform);
    }

    Transform::Transform(Transform &&other) noexcept:
            localPosition(other.localPosition),
            localRotation(other.localRotation),
            localScale(other.localScale),
            modelMatrix(other.modelMatrix),
            children(std::move(other.children)) {
        owner = other.owner;
        setParent(other.parent);
    }

    Transform *Transform::getParent() {
        return parent;
    }

    void Transform::setParent(Transform *parentTransform) {
        parent = parentTransform;
        if(parent != nullptr) {
            parent->addChild(this);
        }
    }

    void Transform::addChild(Transform *transform) {
        children.insert(transform);
    }

    void Transform::removeChild(Transform *transform) {
        children.erase(transform);
    }

    std::set<Transform *> Transform::getChildTransforms() {
        return children;
    }

    void Transform::invalidate() {
        deleted = true;
        parent = nullptr;
        for(auto child: children) {
            child->invalidate();
        }
        children.clear();
    }

    Transform::~Transform() {
        if(parent != nullptr) {
            parent->removeChild(this);
        }
        invalidate();
    }

    glm::vec3 Transform::getWorldPosition(glm::mat4 parentLocalToWorld) {
        return getWorldMatrix() * glm::vec4(0, 0, 0, 1);
    }

    glm::vec3 Transform::getWorldScale(glm::mat4 parentLocalToWorld) {
        glm::mat4 worldMatrix = getWorldMatrix();
        glm::vec3 scale = {0,0,0};
        for(int i = 0; i < 3; i++){
            glm::vec3 vector = worldMatrix[i];
            scale[i] = glm::length(vector);
        }
        return scale;
    }

    glm::mat4 Transform::getWorldRotationMatrix() {

        glm::mat4 worldMatrix = getWorldMatrix();
        glm::vec3 scale = {0,0,0};
        for(int i = 0; i < 3; i++){
            glm::vec3 vector = worldMatrix[i];
            scale[i] = glm::length(vector);
        }
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                worldMatrix[i][j] /= scale[i];
            }
        }
        worldMatrix[3] = {0,0,0,1};
        return worldMatrix;
    }

    glm::vec3 Transform::getForwardVector(){
        return getWorldRotationMatrix() * glm::vec4{1.0f ,0.0f ,0.0f ,0};
    }
}