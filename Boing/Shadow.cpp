#include "Shadow.hpp"
#include <glm/gtc/constants.hpp>

std::vector<float> generate_circle(int sections, float radius)
{
    std::vector<float> vertices;
    
    float angle_step = 2 * glm::pi<float>() / sections;
    
    for (int i = 0; i < sections; i++) {
        float angle = i * angle_step;
        vertices.insert(vertices.end(),
            { 0, 0, 0,
              radius * cos(angle + angle_step), radius * sin(angle + angle_step), 0,
              radius * cos(angle), radius * sin(angle), 0 });
    }
    
    return vertices;
}

Shadow::Shadow(int sections, float radius) : Model("vertex_uniform.glsl", "fragment_uniform.glsl")
{
    auto colLoc = glGetUniformLocation(shaderProgram.program(), "colour");;
    glUniform4f(colLoc, 0, 0, 0, 0.3);
    
    vertices = generate_circle(sections, radius);
    float *pvertices = &vertices[0];
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), pvertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Shadow::draw()
{
    Model::draw((GLsizei)vertices.size() / 3);
}
