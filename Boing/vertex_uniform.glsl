#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 colour;

out vec4 aColour;

void main()
{
    aColour = colour;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
