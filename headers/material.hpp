#pragma once
#include <unordered_map>
#include <string>
#include <glad/glad.h>
class Material{
    public:
        unsigned int shaderProgram;
        std::unordered_map<std::string,unsigned int> buffers;
        Material();
        ~Material();
        void Bind();
        void setShader(unsigned int);
        void setBuffer(std::string name,std::vector<float> data);
};
