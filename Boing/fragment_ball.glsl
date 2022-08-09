#version 330 core
out vec4 FragColor;
in float oCol;
in vec4 selCol;

void main()
{
    if (oCol < 0.5f) {
        FragColor = selCol;
    } else {
        FragColor = vec4(1.f, 1.f, 1.f, 1.0f);
    }
}
