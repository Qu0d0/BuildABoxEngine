#pragma once
#include <filesystem>
#include "engine/ecs/Component.h"
#include <tiny_gltf/tiny_gltf.h>

using gl3::engine::ecs::Component;
using gl3::engine::ecs::ComponentManager;
using gl3::engine::ecs::guid_t;
using gl3::engine::ecs::Entity;

typedef std::map<std::filesystem::path, tinygltf::Model> models_Dictionary;

struct Primitive {
    int mode;
    size_t count;
    int type;
};


struct MeshComponent: Component {
    friend ComponentManager;
    friend Entity;

    public:
        void draw() const;

    private:
    static models_Dictionary modelsDictionary;

        tinygltf::Model loadGltf(const std::filesystem::path &gltfAssetPath);

        unsigned int VAO = 0;
        GLuint EBO;
        std::map<int, unsigned int> buffers;
        std::map<std::string, unsigned int> vaa = {
                {"POSITION", 0},
                {"NORMAL", 1},
                {"TEXCOORD_0", 2}
        };

        std::vector<Primitive> primitives;

private:
    explicit MeshComponent(guid_t owner, const std::filesystem::path &gltfAssetPath, int meshIndex = 0); //: Component(owner){}

};