#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in ivec4 aBoneIDs;
layout (location = 6) in vec4 aWeights;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const int MAX_BONES = 100;
const int MAX_BONES_PER_VERTEX = 4;
uniform mat4 bones[MAX_BONES];

void main()
{
    vec4 pos = vec4(0.0);

    for (int i = 0; i < MAX_BONES_PER_VERTEX; i++) {
        if (aBoneIDs[i] == -1)
            continue;
        if (aBoneIDs[i] >= MAX_BONES) {
            pos = vec4(aPos, 1.0);
            break;
        }
        vec4 localPosition = bones[aBoneIDs[i]] * vec4(aPos, 1.0);
        pos += localPosition * aWeights[i];
        vec3 localNormal = mat3(bones[aBoneIDs[i]]) * aNormal;
    }

    mat4 viewModel = view * model;
    gl_Position = projection * viewModel * pos;
    TexCoords = aTexCoords;
}