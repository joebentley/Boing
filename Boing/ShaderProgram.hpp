#pragma once
#include <string_view>
#include <glm/glm.hpp>

class ShaderProgram {
public:
    ShaderProgram(std::string_view vs_filename, std::string_view fs_filename);
    ~ShaderProgram();
    void use();
    unsigned int program() { return shaderProgram; }
    void set_model(glm::mat4 model);
    void set_view(glm::mat4 view);
    void set_projection(glm::mat4 projection);
    
private:
    unsigned int shaderProgram;
    unsigned int modelLoc;
    unsigned int viewLoc;
    unsigned int projectionLoc;
};
