#include "Input.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Vector3.hpp"

#include <vector>
#include <iostream>

int main()
{
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

	//inizio spazio test

	

	//fine spazio test
	
	Renderer renderer;

    std::vector<Vertex> vertices =
    {
        {
            {-0.5f, -0.5f, 0.0f}, // position
            {0.0f, 0.0f, 1.0f},  // normal
            {1.0f, 0.0f, 0.0f},  // color
            {0.0f, 0.0f}         // texture
        },

        {
            {0.5f, -0.5f, 0.0f},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 1.0f, 0.0f},
            {1.0f, 0.0f}
        },

        {
            {0.0f, 0.5f, 0.0f},
            {0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 1.0f},
            {0.5f, 1.0f}
        }
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2
    };

	Mesh triangle(vertices, indices);

    Shader shader{
        "shaders/basic.vert",
        "shaders/basic.frag"
    };

    while (!window.shouldClose())
    {
        input.processInput(window.getNativeWindow());

		renderer.clear();

		shader.use();

		renderer.draw(triangle);

		window.update();
    }

    return 0;
}