#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#include<iostream>
#include<fstream>
#include <sstream>
#include<string>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

std::string loadShaderSource(
    const std::string& path
);

class Shader {
public:
    GLuint ID;
    Shader(const std::string& vertexFile, const std::string& fragmentFile);

    void Activate();
    void Deactivate();


};


#endif