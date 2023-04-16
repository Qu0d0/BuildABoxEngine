#include <glm/gtc/matrix_transform.hpp>
#include "engine/sceneGraph/Transform.h"

namespace gl3::engine::sceneGraph {
    Transform::Transform(guid_t owner, Transform *parentTransform, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
            : Component(owner),
              localPosition(position),
              localRotation(rotation),
              localScale(scale),
              modelMatrix(glm::identity<glm::mat4>()) {
        //localRotation = rotation;
        setParent(parentTransform);
    }
    //make copy constructer
    Transform::Transform(Transform &&other) noexcept:
            localPosition(other.localPosition),
            localZRotation(other.localZRotation),
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
}