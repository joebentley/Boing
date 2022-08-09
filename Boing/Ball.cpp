#include "Ball.hpp"
#include <glad/glad.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#define PI 3.14159265359

void insert_spherical_polar(std::vector<float> &vertices, float r, float theta, float phi)
{
    vertices.insert(vertices.end(), { r * cos(phi) * sin(theta), r * sin(phi) * sin(theta), r * cos(theta)});
}

float vertex_color(int i, int j) {
    bool even_row = i % 2 == 0;
    bool even_col = j % 2 == 0;

    return (even_row && even_col) || (!even_row && !even_col) ? 1 : 0;
}

std::vector<float> generateBall(int columns, int rows, float radius) {
    std::vector<float> vertices;
    
    const float theta_step = glm::pi<float>() / (float)rows;
    const float phi_step = 2 * glm::pi<float>() / (float)columns;
    
    for (int i = 2; i < rows; i++) {
        float theta = i * theta_step;
        for (int j = 0; j < columns; j++) {
            float phi = j * phi_step;

            float color = vertex_color(i, j);

            insert_spherical_polar(vertices, radius, theta, phi);
            vertices.push_back(color);
            insert_spherical_polar(vertices, radius, theta - theta_step, phi);
            vertices.push_back(color);
            insert_spherical_polar(vertices, radius, theta, phi + phi_step);
            vertices.push_back(color);

            insert_spherical_polar(vertices, radius, theta, phi + phi_step);
            vertices.push_back(color);
            insert_spherical_polar(vertices, radius, theta - theta_step, phi);
            vertices.push_back(color);
            insert_spherical_polar(vertices, radius, theta - theta_step, phi + phi_step);
            vertices.push_back(color);
        }
    }
    
    // top cap
    for (int j = 0; j < columns; j++) {
        float phi = j * phi_step;
        float color = vertex_color(0, j);
        insert_spherical_polar(vertices, radius, 0, phi);
        vertices.push_back(color);
        insert_spherical_polar(vertices, radius, theta_step, phi);
        vertices.push_back(color);
        insert_spherical_polar(vertices, radius, theta_step, phi - phi_step);
        vertices.push_back(color);
    }
    
    // bottom cap
    for (int j = 0; j < columns; j++) {
        float phi = j * phi_step;
        float color = vertex_color(rows + 1, j);
        insert_spherical_polar(vertices, radius, PI, phi);
        vertices.push_back(color);
        insert_spherical_polar(vertices, radius, PI-theta_step, phi);
        vertices.push_back(color);
        insert_spherical_polar(vertices, radius, PI-theta_step, phi - phi_step);
        vertices.push_back(color);
    }
    
    return vertices;
}

Ball::Ball(int columns, int rows, float radius) : Model("vertex_ball.glsl", "fragment_ball.glsl")
{
    vertices = generateBall(columns, rows, radius);
    float *pvertices = &vertices[0];
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), pvertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    colourLocation = glGetUniformLocation(shaderProgram.program(), "selectedCol");
    set_colour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void Ball::draw()
{
    Model::draw((GLsizei)vertices.size() / 4);
}

void Ball::set_colour(glm::vec4 colour)
{
    shaderProgram.use();
    glUniform4f(colourLocation, colour.r, colour.g, colour.b, colour.a);
}
