#version 330 core
out vec4 FragColor;
in float oCol;

void main()
{
    if (oCol < 0.5f) {
        FragColor = vec4(1.0f, 0.f, 0.f, 1.0f);
    } else {
        FragColor = vec4(1.f, 1.f, 1.f, 1.0f);
    }
}
