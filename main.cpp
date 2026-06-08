#include<cmath>
#include "helpers.h"
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;



GLfloat vertices[] = {
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	-0.5f / 2, 0.5f * float(sqrt(3))/ 6, 0.0f,
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	0.0f / 2, -0.5f * float(sqrt(3)) / 3, 0.0f,

};

GLuint indices[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};

int main() {
	//Initialise GLFW
	glfwInit();

	GLFWwindow* window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Renderer");
	
	// Change the background color and swap the buffers to display it
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// load the shaders
	Shader shader = Shader("vertex.glsl", "fragment.glsl");

	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	// keep the window open
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader.Deactivate();

	glfwTerminate();
	return 0;
}

