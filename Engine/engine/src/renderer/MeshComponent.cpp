//
// Created by Oddball on 30/10/2022.
//
#pragma once
#include <iostream>
#include "glad/glad.h"
#include "engine/assetLoader/Assets.h"
#include "engine/renderer/rendererComponents/MeshComponent.h"

models_Dictionary MeshComponent::modelsDictionary = {};

MeshComponent::MeshComponent(guid_t owner, const std::filesystem::path &gltfAssetPath, int meshIndex) : Component(owner){

    std::filesystem::path assetPath = resolveAssetPath(gltfAssetPath);
    tinygltf::Model model;
    model = loadGltf(assetPath);

    if(model.meshes.size() <= meshIndex) {
        throw std::runtime_error("[mesh] model does not contain requested mesh: " + gltfAssetPath.string());
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    for(size_t i = 0; i < model.bufferViews.size(); ++i) {
        const auto &bufferView = model.bufferViews[i];
        const auto &buffer = model.buffers[bufferView.buffer];
        if(bufferView.target == 0) {
            continue;
        }

        GLuint vbo;
        glGenBuffers(1, &vbo);
        buffers[i] = vbo;
        glBindBuffer(bufferView.target, vbo);
        glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset,
                     GL_STATIC_DRAW);

    }


    const auto &mesh = model.meshes[meshIndex];
    for(const auto &primitive: mesh.primitives) {
        const auto &indexAccessor = model.accessors[primitive.indices];

        for(const auto &attrib: primitive.attributes) {
            tinygltf::Accessor accessor = model.accessors[attrib.second];
            int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);
            glBindBuffer(GL_ARRAY_BUFFER, buffers[accessor.bufferView]);

            int size = 1;
            if(accessor.type != TINYGLTF_TYPE_SCALAR) {
                size = accessor.type;
            }

            const auto &result = vaa.find(attrib.first);



            if(result != vaa.end()) {
                glEnableVertexAttribArray(result->second);
                glVertexAttribPointer(result->second, size, accessor.componentType,
                                      accessor.normalized ? GL_TRUE : GL_FALSE,
                                      byteStride, nullptr);
            }
            else {
                std::cerr << "[mesh] unsupported VAA: " << attrib.first << std::endl;
            }

        }

        primitives.push_back({primitive.mode, indexAccessor.count,
                              indexAccessor.componentType});
    }
    glBindVertexArray(0);
}

tinygltf::Model MeshComponent::loadGltf(const std::filesystem::path &gltfAssetPath) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    bool res;
    if(gltfAssetPath.extension().string() == ".glb") {
        res = loader.LoadBinaryFromFile(&model, &err, &warn, gltfAssetPath.string());
    } else {
        res = loader.LoadASCIIFromFile(&model, &err, &warn, gltfAssetPath.string());
    }

    if(!warn.empty()) {
        std::cerr << "[tinygltf] warning: " << warn << std::endl;
    }

    if(!err.empty()) {
        std::cerr << "[tinygltf] error: " << err << std::endl;
    }

    if(!res) {
        throw std::runtime_error("[tinyglt] failed to load glTF: " + gltfAssetPath.string());
    }

    return std::move(model);
}


void MeshComponent::draw() const {
    glBindVertexArray(VAO);
    for(auto &primitive: primitives) {
        glDrawElements(primitive.mode, primitive.count, primitive.type, nullptr);
    }
    glBindVertexArray(0);
}
