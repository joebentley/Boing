#include "Grid.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

void add_grid_point(std::vector<float> &vertices, float x, float y, bool horiz)
{
    if (horiz) {
        vertices.insert(vertices.end(), {x, 0, y});
    } else {
        vertices.insert(vertices.end(), {x, y, 0});
    }
}

std::vector<float> generate_grid(bool horiz, float spacing, int columns, int rows, float thickness)
{
    std::vector<float> vertices;
    
    const float width = spacing * (columns - 1) + thickness;
    const float height = spacing * (rows - 1) + thickness;
    
    for (int x = 0; x < columns; x++) {
        float x_offs = x * spacing;
        
        add_grid_point(vertices, x_offs, height, horiz);
        add_grid_point(vertices, x_offs, 0, horiz);
        add_grid_point(vertices, x_offs + thickness, height, horiz);
        add_grid_point(vertices, x_offs + thickness, height, horiz);
        add_grid_point(vertices, x_offs, 0, horiz);
        add_grid_point(vertices, x_offs + thickness, 0, horiz);
    }
    
    for (int y = 0; y < rows; y++) {
        float y_offs = y * spacing;
        
        if (horiz && y == rows - 1)
            continue;
        
        add_grid_point(vertices, 0, y_offs, horiz);
        add_grid_point(vertices, 0, y_offs + thickness, horiz);
        add_grid_point(vertices, width, y_offs + thickness, horiz);
        add_grid_point(vertices, 0, y_offs, horiz);
        add_grid_point(vertices, width, y_offs + thickness, horiz);
        add_grid_point(vertices, width, y_offs, horiz);
    }
    
    return vertices;
}

Grid::Grid() : Model("vertex_uniform.glsl", "fragment_uniform.glsl")
{
    auto colLoc = glGetUniformLocation(shaderProgram.program(), "colour");;
    glUniform4f(colLoc, 0.7, 0.3, 0.7, 1.0);
    
    const float spacing = 0.1f;
    const int columns = 16;
    const int rows = 13;
    const float thickness = 0.01f;
    
    vertices = generate_grid(false, spacing, columns, rows, thickness);
    auto horiz_vertices = generate_grid(true, spacing, columns, 4, thickness);
    vertices.insert(vertices.end(), horiz_vertices.cbegin(), horiz_vertices.cend());
    
    auto model = glm::scale(glm::mat4(1.0f), glm::vec3(1.4));
    set_model(glm::translate(model, glm::vec3(-(columns / 2.0 - 0.5) * spacing, -0.4, 0)));
    
    float *pvertices = &vertices[0];
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), pvertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Grid::draw()
{
    Model::draw((GLsizei)vertices.size() / 3);
}
