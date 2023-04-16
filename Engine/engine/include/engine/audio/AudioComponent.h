//
// Created by Oddball on 26/01/2023.
//
#pragma once
#include "glm/mat4x4.hpp"
#include "engine/ecs/Component.h"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/assetLoader/Assets.h"

#include <soloud.h>
#include <soloud_wav.h>

using gl3::engine::ecs::Component;
using gl3::engine::ecs::ComponentManager;
using gl3::engine::ecs::guid_t;
using gl3::engine::ecs::Entity;

struct AudioComponent : Component {
    friend ComponentManager;
    friend Entity;

private:
    SoLoud::Soloud audio;
    SoLoud::Wav sound;

public:
    void playSound(){audio.play(sound);}

    void loadSound(){
        //sound = std::make_unique<SoLoud::Wav>();
        sound.load(resolveAssetPath("audio/electronic-wave.mp3").string().c_str());
        sound.setSingleInstance(true);
        //audio.playBackground(*backgroundMusic);
    }

    void loadSoundLooping(){
        //sound = std::make_unique<SoLoud::Wav>();
        sound.load(resolveAssetPath("audio/electronic-wave.mp3").string().c_str());
        sound.setLooping(true);
        //audio.playBackground(*backgroundMusic);
    }

private:
    explicit AudioComponent(guid_t owner) : Component(owner){
        audio.init();
        audio.setGlobalVolume(1.0f);
        sound.load(resolveAssetPath("audio/electronic-wave.mp3").string().c_str());
        sound.setLooping(true);
        playSound();
    }
};