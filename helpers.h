#pragma once
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


struct MeshBuffers
{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

GLFWwindow* createWindow(
    int windowWidth,
    int windowHeight,
    const char* title
);

//std::string loadShaderSource(
//    const std::string& path
//);

GLuint loadShaders(
    const std::string& vertexPath,
    const std::string& fragmentPath
);

MeshBuffers drawMesh(
    GLfloat vertices[],
    GLuint indices[],
    float vertices_size,
    float indices_size
);