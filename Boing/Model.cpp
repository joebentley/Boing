#include "Model.hpp"

Model::Model(std::string_view vs_filename, std::string_view fs_filename)
    : shaderProgram(vs_filename, fs_filename)
{
    set_model(glm::mat4(1.0f));
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

Model::~Model()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Model::draw(GLsizei count)
{
    shaderProgram.use();
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Model::set_model(glm::mat4 model)
{
    shaderProgram.set_model(model);
}

void Model::set_view(glm::mat4 view)
{
    shaderProgram.set_view(view);
}

void Model::set_projection(glm::mat4 projection)
{
    shaderProgram.set_projection(projection);
}
