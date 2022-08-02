#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>
#include "ShaderProgram.hpp"

class Model {
public:
    // You must override this to set up the VAO and VBO
    Model(std::string_view vs_filename, std::string_view fs_filename);
    ~Model();
    
    // Must override
    virtual void draw(GLsizei count);
    
    virtual void set_model(glm::mat4 model);
    virtual void set_view(glm::mat4 view);
    virtual void set_projection(glm::mat4 projection);
protected:
    unsigned int VAO;
    unsigned int VBO;
    
    ShaderProgram shaderProgram;
};
