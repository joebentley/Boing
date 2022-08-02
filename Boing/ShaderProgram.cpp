#include "ShaderProgram.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(std::string_view vs_filename, std::string_view fs_filename)
{
    std::ifstream vs_file(vs_filename);
    if (vs_file.fail())
        throw std::runtime_error("Vertex shader file not found\n");
    
    std::stringstream vs_ss;
    vs_ss << vs_file.rdbuf();
    std::string vs_source = vs_ss.str();
    const char* vs_source_cstr = vs_source.c_str();
    
    std::ifstream fs_file(fs_filename);
    if (fs_file.fail())
        throw std::runtime_error("Fragment shader file not found\n");
    
    std::stringstream fs_ss;
    fs_ss << fs_file.rdbuf();
    std::string fs_source = fs_ss.str();
    const char* fs_source_cstr = fs_source.c_str();
    
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs_source_cstr, nullptr);
    glCompileShader(vertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::string s = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        s += infoLog;
        throw std::runtime_error(s);
    }
    
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs_source_cstr, nullptr);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::string s = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        s += infoLog;
        throw std::runtime_error(s);
    }
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::string s = "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
        s += infoLog;
        throw std::runtime_error(s);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    modelLoc = glGetUniformLocation(program(), "model");
    viewLoc = glGetUniformLocation(program(), "view");
    projectionLoc = glGetUniformLocation(program(), "projection");
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgram);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(shaderProgram);
}

void ShaderProgram::set_model(glm::mat4 model)
{
    use();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void ShaderProgram::set_view(glm::mat4 view)
{
    use();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void ShaderProgram::set_projection(glm::mat4 projection)
{
    use();
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
