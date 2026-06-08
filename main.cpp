#include<cmath>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helpers.h"
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "texture.h"


const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 1080;



GLfloat vertices[] = {
	// Position              // Color               // Texture

	// Base
	-0.5f, 0.0f, -0.5f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f, // 0
	-0.5f, 0.0f,  0.5f,      0.0f, 1.0f, 0.0f,      0.0f, 1.0f, // 1
	 0.5f, 0.0f,  0.5f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f, // 2
	 0.5f, 0.0f, -0.5f,      1.0f, 1.0f, 0.0f,      1.0f, 0.0f, // 3

	 // Tip
	  0.0f, 0.8f, 0.0f,       1.0f, 0.0f, 1.0f,      0.5f, 0.5f  // 4
};

GLuint indices[] = {

	// Base
	0, 1, 2,
	0, 2, 3,

	// Front
	0, 4, 3,

	// Right
	3, 4, 2,

	// Back
	2, 4, 1,

	// Left
	1, 4, 0
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

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// keep the window open
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();

		double crntTime = glfwGetTime();

		if ((crntTime - prevTime) >= 1 / 60) {
			rotation += 0.02f;
			prevTime = crntTime;
		}



		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shader.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		glUniform1f(uniID, 2.0f);
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

