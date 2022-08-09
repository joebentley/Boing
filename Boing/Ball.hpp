#pragma once
#include "Model.hpp"
#include <glm/glm.hpp>
#include <vector>

class Ball: public Model {
public:
    Ball(int columns, int rows, float radius);
    
    void set_colour(glm::vec4 colour);
    void draw();
    
private:
    std::vector<float> vertices;
    
    float colourLocation;
};
