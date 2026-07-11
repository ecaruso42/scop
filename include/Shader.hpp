#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Shader {
    private:
        unsigned int _ID;

        std::string readFile(const std::string& path);
        void compileShader(const std::string& source, unsigned int shaderType, unsigned int& shaderID);
        unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
        void checkErrors(unsigned int shader, const std::string& type);

    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void use() const;
};