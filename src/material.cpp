#include "material.hpp"
#include <Errorhandling.hpp>


Material::Material()
{
}

Material::~Material()
{
    for(auto &i:buffers){
        glad_glDeleteBuffers(1,&i.second);
    }
}

void Material::Bind()
{

}

void Material::setShader(unsigned int program)
{
    shaderProgram=program;
}
void Material::setBuffer(std::string name,std::vector<float> data){
    if(buffers.find(name)==buffers.end()){
        GL_CHECK(glad_glGenBuffers(1,&buffers[name]));
        GL_CHECK(glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffers[name]));
        GL_CHECK(glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(float), data.data(), GL_DYNAMIC_DRAW));
    }else{
        GL_CHECK(glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffers[name]));
        GL_CHECK(glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float)*data.size(), data.data()));

    }
    GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffers[name]));
}

