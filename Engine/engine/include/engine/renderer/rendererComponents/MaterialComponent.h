//
// Created by Oddball on 17/11/2022.
//
#pragma once
#include <filesystem>
#include <utility>
#include <iostream>
#include "engine/ecs/Component.h"
#include "tiny_gltf/tiny_gltf.h"
#include "tiny_gltf/stb_image.h"
#include "engine/assetLoader/Assets.h"
#include "glad/glad.h"

using gl3::engine::ecs::Component;
using gl3::engine::ecs::ComponentManager;
using gl3::engine::ecs::guid_t;
using gl3::engine::ecs::Entity;
typedef std::map<std::filesystem::path, stbi_uc*> textures_Dictionary;
typedef std::map<std::filesystem::path, int> textureSize_Dictionary;


struct MaterialComponent : Component {
    friend ComponentManager;
    friend Entity;

public:

    void bindTexture() {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    static textures_Dictionary texturesDictionary;
    static textureSize_Dictionary textureSizeDictionary;
    static stbi_uc* imageData;


private:

    bool hasAlphaTexture = false;
    int textureInt = 0;
    int imgWidth, imgHight, imgColChannels;

    unsigned char *bytes;

    std::filesystem::path texturePath;
    GLuint texture;

    void loadTexture() {
        //stbi_set_flip_vertically_on_load(true);
        //1 if value is in map 0 if not
        if(texturesDictionary.count(texturePath)){

            auto value = texturesDictionary.find(texturePath);
            auto texmapo = textureSizeDictionary.find(texturePath);
            if (value == texturesDictionary.end() || texmapo == textureSizeDictionary.end()) {
                std::cout << "Map error in material loader" << std::endl;
            }else{
                imageData = value->second;
                imgWidth = texmapo->second;
                imgHight = texmapo->second;
            }
        }
        else{
            std::string assetPath2 = resolveAssetPath(texturePath).string();
            imageData = stbi_load(assetPath2.c_str(), &imgWidth, &imgHight, &imgColChannels, 0);
            texturesDictionary.emplace(texturePath, imageData);
            textureSizeDictionary.emplace(texturePath, imgWidth);
        }

        if (imageData == NULL) {
            std::cout << "Failed to load image" << std::endl;
        }

        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        if(hasAlphaTexture){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        }else{
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0); //Make this a variable for different textures on models

    }

private:
    explicit MaterialComponent(guid_t owner, std::filesystem::path texturePath) : Component(owner) {
        this->texturePath = std::move(texturePath);
        loadTexture();
    }

    explicit MaterialComponent(guid_t owner, std::filesystem::path texturePath , bool hasAnAlphaTexture) : Component(owner) {
        this->texturePath = std::move(texturePath);
        hasAlphaTexture = hasAnAlphaTexture;
        loadTexture();
    }
};