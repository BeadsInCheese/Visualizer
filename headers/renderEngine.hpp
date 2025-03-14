#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Model.hpp"
#include "Globals.hpp"
#include "Errorhandling.hpp"
#include <memory.h>
#include <unordered_map>
// float aspectRatio=600/800;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
class renderEngine{
private:
    int width=600;
    int height=800;

    std::unordered_map<std::string,float> uniforms;
public:
    GLFWwindow* window;
    renderEngine();
    ~renderEngine();
    float getAspectRatio();
    private:
        void initWindow();
        
    public:
        std::vector<std::shared_ptr<Model>> models;
        void addModel(std::shared_ptr<Model> &m);
        const char* ReadFileAsCString(std::string filename,std::string& result);
        void compileAndLinkShaderProgram(unsigned int &shaderProgram,const char* fragmentCode, const char* vertexCode);
        void updateAspectRatio();
        void initFullScreenQuad();
        void render();
        void setUniform(std::string &name,float value);
        void renderFullScreenQuad();
        

};