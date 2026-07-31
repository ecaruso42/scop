#include "Input.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Vector3.hpp"
#include "ObjLoader.hpp"
#include "Transform.hpp"
#include <vector>
#include <iostream>

int main()
{
    Input input;

    Window window(1920, 1080, "SCOP");

	Transform transform;
	
    if (!window.isValid()){
		return 1;
    }
	
    glfwMakeContextCurrent(window.getNativeWindow());
	
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
		std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

	glEnable(GL_DEPTH_TEST);

	//inizio spazio test

	

	//fine spazio test
	
	Renderer renderer;

	ObjLoader loader("assets/models/42.obj");

	Mesh object(loader.getVertices(), loader.getIndices());

    Shader shader("shaders/basic.vert", "shaders/basic.frag");

	transform.rotation.y = 90.0f * M_PI / 180.0f;

	Matrix4 view = Matrix4::lookAt(
	    Vector3(0.0f, 0.0f, 3.0f),
	    Vector3(0.0f, 0.0f, 0.0f),
	    Vector3(0.0f, 1.0f, 0.0f)
	);

	Matrix4 projection = Matrix4::perspective(
	    45.0f * M_PI / 180.0f,
	    800.0f / 600.0f,
	    0.1f,
	    100.0f
	);

    while (!window.shouldClose())
    {
        input.processInput(window.getNativeWindow(), transform);

		renderer.clear();

		shader.use();

		shader.setBool("useLighting", true);

		shader.setMatrix4("model", transform.getMatrix());
		shader.setMatrix4("view", view);
		shader.setMatrix4("projection", projection);
		
		renderer.draw(object);

		window.update();
    }

    return 0;
}