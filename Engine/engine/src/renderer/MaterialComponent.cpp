#include "engine/renderer/rendererComponents/MaterialComponent.h"

textures_Dictionary MaterialComponent::texturesDictionary = {};
textureSize_Dictionary MaterialComponent::textureSizeDictionary = {};
stbi_uc* MaterialComponent::imageData = {};