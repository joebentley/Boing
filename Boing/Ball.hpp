#pragma once
#include "Model.hpp"
#include <glm/glm.hpp>
#include <vector>

class Ball: public Model {
public:
    Ball(int columns, int rows, float radius);
    
    void draw();
    
private:
    std::vector<float> vertices;
};
