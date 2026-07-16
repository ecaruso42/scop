#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Input.hpp"
#include "Shader.hpp"
#include "Window.hpp"

#include <iostream>

int main()
{
    float vertices[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f
    };

    Input input;

    Window window(800, 600, "SCOP");

    if (!window.isValid()){
        return 1;
    }

    glfwMakeContextCurrent(window.getNativeWindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// attributo posizione (location = 0)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    Shader shader{
        "shaders/basic.vert",
        "shaders/basic.frag"
    };

    while (!window.shouldClose())
    {
        input.processInput(window.getNativeWindow());

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.update();
    }

    return 0;
}