#include "Input.hpp"

void Input::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        std::cout << "W premuto\n";
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        std::cout << "A premuto\n";
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        std::cout << "S premuto\n";
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        std::cout << "D premuto\n";
}

Input::Input(){
}
Input::~Input(){
}