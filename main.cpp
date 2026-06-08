#include<cmath>
#include "helpers.h"
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "texture.h"


const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 1080;



GLfloat vertices[] = {                 // colors
	-0.5f, -0.5f, 0.0f,      0.8f, 0.3f, 0.02f,      0.0f, 0.0f,
	-0.5f,  0.5f, 0.0f,      0.8f, 0.3f, 0.2f,       0.0f, 1.0f,
	 0.5f,  0.5f, 0.0f,      1.0f, 0.6f, 0.32f,		 1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f,      0.9f, 0.45f, 0.17f,	 1.0f, 0.0f
};

GLuint indices[] = {
	0, 2, 1,
	0, 3, 2
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

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shader.ID, "scale");

	
	Texture popCat("popcat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shader, "tex0", 0);


	// keep the window open
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();
		glUniform1f(uniID, 0.5f);
		popCat.Bind();

		VAO1.Bind();



		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shader.Deactivate();

	glfwTerminate();
	return 0;
}

