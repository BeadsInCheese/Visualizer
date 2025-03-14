#include "Model.hpp"
#include <GLFW/glfw3.h>

Model::Model(unsigned int shader,std::vector<float>& vertices,std::vector<int>& indices){
    // Generate and bind a Vertex Array Object (VAO)
    std::cout<<indices.size()<<std::endl;
    std::cout<<vertices.size()<<std::endl;
    indexCount=indices.size();
    GLFWwindow* currentContext = glfwGetCurrentContext();
    if (!currentContext) {
        std::cerr << "No current OpenGL context" << std::endl;
        exit(0);
    }
    VAO = 0;
    VBO = 0;
    EBO = 0;
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        // print(error), etc...
    }
    GL_CHECK(glGenBuffers(1, &VBO));

    GL_CHECK(glGenVertexArrays(1, &VAO));
    GL_CHECK(glBindVertexArray(VAO));

    GL_CHECK(glGenBuffers(1, &EBO));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER,  indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW));

    // Bind and set vertex buffer
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER,  vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));

    // Set vertex attribute pointers
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
    GL_CHECK(glEnableVertexAttribArray(0));

    // Set vertex attribute pointers
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    GL_CHECK(glEnableVertexAttribArray(1));
    glUseProgram(shader);
    material.shaderProgram=shader;
    // Unbind the VAO
    GL_CHECK(glBindVertexArray(0));

}
Model::~Model(){
    std::cout<<"model deleted"<<"\n";
    GL_CHECK(glDeleteVertexArrays(1, &VAO));
    GL_CHECK(glDeleteBuffers(1, &VBO));
    GL_CHECK(glDeleteBuffers(1, &EBO));
}

void Model::setShader(unsigned int program){
    material.shaderProgram=program;
}
void Model::Bind(){
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glUseProgram(material.shaderProgram));
    GL_CHECK(glBindVertexArray(VAO));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

}

void Model::setUniform(std::string name,float value){

    int loc = glGetUniformLocation(material.shaderProgram, name.c_str());
    GL_CHECK(glUniform1f(loc,value));
}