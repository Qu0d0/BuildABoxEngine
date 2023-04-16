#version 460 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 mvp;
uniform mat4 modelToWorldNormal;

//Outputs colors for the Fragment Shader
//TODO Learn instanceing
out vec3 normal;
out vec2 texCoord;


void main() {
    gl_Position = mvp * vec4(aPosition, 1.0f);
    normal = vec3(modelToWorldNormal * vec4(aNormal, 0.0f));
    texCoord = aTex;
}