#pragma once
#include <vector>
#include "Model.hpp"

class Shadow : public Model {
public:
    Shadow(int sections, float radius);
    void draw();
    
private:
    std::vector<float> vertices;
};

