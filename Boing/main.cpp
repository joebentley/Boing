#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <optional>
#include "Ball.hpp"
#include "Grid.hpp"
#include "Shadow.hpp"

#define try_emplace(optional, ...) \
try { \
    optional.emplace(__VA_ARGS__); \
} catch (std::exception &e) { \
    std::cout << e.what() << std::endl; \
    glfwTerminate(); \
    return -1; \
}

int main(void)
{
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "Boing", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    
    std::optional<Ball> ball;
    try_emplace(ball, 20, 10, 0.5f);
    
    std::optional<Grid> grid;
    try_emplace(grid);
    
    std::optional<Shadow> shadow;
    try_emplace(shadow, 20, 0.5f);
    
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.15f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    
    ball->set_view(view);
    ball->set_projection(projection);
    
    grid->set_view(view);
    grid->set_projection(projection);
    
    shadow->set_view(view);
    shadow->set_projection(projection);
    
    float clear_grey = 0.8f;
    
    float rotation_angle = 0;
    glm::vec3 position(0, 0.75, 0);
    glm::vec3 velocity(-0.5, 0, 0);
    glm::vec3 accel(0, -3, 0);
    
    const float dt = 1/60.f;
    
    while(!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
        glClearColor(clear_grey, clear_grey, clear_grey, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        rotation_angle += 0.02f;
        auto model = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f));
        model = glm::translate(model, position);
        model = glm::rotate(model, 0.5f * glm::pi<float>(), glm::vec3(1.0, 0.0, -0.2));
        model = glm::rotate(model, rotation_angle, glm::vec3(0.0, 0.0, -1.0));
        
        ball->set_model(model);
        ball->draw();
        grid->draw();
        
        model = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f));
        model = glm::translate(model, position + glm::vec3(0.2, 0.05, 0));
        
        shadow->set_model(model);
        shadow->draw();
        
        velocity += accel * dt;
        position += velocity * dt;
        
        if (position.y <= -0.25)
            velocity.y = 2.5;
    
        if (position.x <= -0.9 || position.x >= 0.9)
            velocity.x = -velocity.x;
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
