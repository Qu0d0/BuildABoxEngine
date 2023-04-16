#version 460 core

in vec3 normal;
in vec2 texCoord;

uniform sampler2D tex0;
uniform vec4 color = vec4(0.945f, 0.768f, 0.058f, 1.0f);
uniform vec4 lightDirection = vec4(-1.0f, -1.0f, -1.0f, 1.0f);
//Outputs colors in RGBA
out vec4 fragColor;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(vec3(lightDirection));
    float attenuation = max(dot(norm, -lightDir), 0.0f);
    //fragColor = texture(tex0, texCoord);
    //fragColor = texture(tex0, texCoord) * attenuation;

    fragColor = attenuation * texture(tex0, texCoord) + 0.5f * texture(tex0, texCoord);
    //fragColor = color * attenuation;
}
