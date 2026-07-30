#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Transform.hpp"

#include <iostream>

class Input {
    private:
    public:
        Input();
        ~Input();

        static void processInput(GLFWwindow *window, Transform& transform);
};