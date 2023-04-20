#pragma once
#include "engine/ecs/Component.h"
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

    SoLoud::Soloud audio;
    SoLoud::Wav sound;

private:
    explicit AudioComponent(guid_t owner) : Component(owner){}
};