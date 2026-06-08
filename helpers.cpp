#include "helpers.h"



GLFWwindow* createWindow(int windowWidth, int windowHeight, const char* title) {
	// Tell glfw which version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Renderer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return NULL;
	}
	// make the current window the context
	glfwMakeContextCurrent(window);
	//load GLAD
	gladLoadGL();
	// intialise the viewport
	glViewport(0, 0, windowWidth, windowHeight);
	return window;
}

//std::string loadShaderSource(const std::string& path) {
//	std::ifstream file(path);
//	if (!file.is_open()) {
//		throw std::runtime_error("Failed to open file: " + path);
//	}
//	std::stringstream buffer;
//	buffer << file.rdbuf();
//	return buffer.str();
//}
//
//GLuint loadShaders(const std::string& vertexPath, const std::string& fragmentPath) {
//	std::string vertexCode = loadShaderSource(vertexPath);
//	std::string fragmentCode = loadShaderSource(fragmentPath);
//
//	const char* vertexShaderSource = vertexCode.c_str();
//	const char* fragmentShaderSource = fragmentCode.c_str();
//
//	std::cout << vertexCode << std::endl;
//	std::cout << fragmentCode << std::endl;
//
//
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	GLint success;
//	char infoLog[512];
//
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "Vertex shader error:\n"
//			<< infoLog
//			<< std::endl;
//	}
//
//
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "Fragment shader error:\n"
//			<< infoLog
//			<< std::endl;
//	}
//
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//
//	glLinkProgram(shaderProgram);
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	return shaderProgram;
//}
//
//MeshBuffers drawMesh(GLfloat vertices[], GLuint indices[], float vertices_size, float indices_size) {
//
//	MeshBuffers mesh;
//
//
//	glGenVertexArrays(1, &mesh.VAO);
//	glGenBuffers(1, &mesh.VBO);
//	glGenBuffers(1, &mesh.EBO);
//
//	glBindVertexArray(mesh.VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
//
//	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
//
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	return mesh;
//}