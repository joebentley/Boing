#pragma once
#include "Model.hpp"
#include <vector>

class Grid : public Model {
public:
    Grid();
    
    void draw();
    
private:
    std::vector<float> vertices;
};
