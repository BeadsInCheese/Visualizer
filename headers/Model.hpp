#pragma once
#include <vector>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "Errorhandling.hpp"
class Model{
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int shaderProgram;
public:
    int indexCount=0;
    Model(unsigned int shadedr,std::vector<float>& vertices,std::vector<int> &indices);
    ~Model();
    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;
    void Bind();
    void setShader(unsigned int);
    void setUniform(std::string name,float value);
};