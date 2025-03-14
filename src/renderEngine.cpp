#include "renderEngine.hpp"
renderEngine::~renderEngine(){
        // Clean up and exit
        models.clear();
        glfwDestroyWindow(window);
        glfwTerminate();
}
renderEngine::renderEngine(){

        
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    // Set the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Visualizer", nullptr, nullptr);
    aspectRatio=(float)600/(float)800;
    initWindow();
}
void renderEngine::updateAspectRatio(){}
void framebuffer_size_callback( GLFWwindow* window,int width, int height)
{
    glViewport(0, 0, width, height);
    aspectRatio=(float)height/(float)width;
}

float renderEngine::getAspectRatio(){

        return aspectRatio;
}

void renderEngine::compileAndLinkShaderProgram(unsigned int &shaderProgram,const char* fragmentCode, const char* vertexCode) {


        // Create and compile the vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GL_CHECK(glShaderSource(vertexShader, 1, &vertexCode, NULL));
        GL_CHECK(glCompileShader(vertexShader));
    
        int success;
        char infoLog[512];
        GL_CHECK(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    
        // Create and compile the fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        GL_CHECK(glShaderSource(fragmentShader, 1, &fragmentCode, NULL));
        GL_CHECK(glCompileShader(fragmentShader));
    
        GL_CHECK(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        shaderProgram = glCreateProgram();
        GL_CHECK(glAttachShader(shaderProgram, vertexShader));
        GL_CHECK(glAttachShader(shaderProgram, fragmentShader));
        GL_CHECK(glLinkProgram(shaderProgram));
    
        GL_CHECK(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    
        GL_CHECK(glDeleteShader(vertexShader));
        GL_CHECK(glDeleteShader(fragmentShader));
    
    
    }

const char* renderEngine::ReadFileAsCString(std::string filename,std::string& result) {
        std::ifstream file(filename.c_str()); // Open the file
        if (!file.is_open()) {
            std::cerr << "Unable to open file\n";
            return 0;
        }
        result="";
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n'; // Output the line
            result+=line+"\n";
        }
    
        file.close(); // Close the file
    
        return result.c_str();
    }
void renderEngine::initWindow(){
        if (!window) {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                exit( -1);
            }
        
            // Make the OpenGL context current
            glfwMakeContextCurrent(window);
        
            // Initialize GLAD
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cerr << "Failed to initialize GLAD" << std::endl;
                exit(-1);
            }
            // Define the viewport dimensions
            GL_CHECK(glViewport(0, 0, 800, 600));
            GL_CHECK(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback));


}
void renderEngine::addModel(std::shared_ptr<Model> &m){
        std::cout<<"Model added"<<std::endl;
        models.push_back(std::move(m));

}
void renderEngine::initFullScreenQuad(){



}
void renderEngine::setUniform(std::string &name,float value){
        uniforms[name]=value;
}
void renderEngine::render(){
        GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
for(std::shared_ptr<Model> &m : models){
        m->Bind();

        for(auto i : uniforms){
                m->setUniform(i.first,i.second);
        }
        for(auto &i : m->material.buffers){
            GL_CHECK(glBindBuffer(GL_SHADER_STORAGE_BUFFER, i.second));
        }
        glDrawElements(GL_TRIANGLES, m->indexCount, GL_UNSIGNED_INT, 0);

}
        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
        

}
void BindModels(){}
void renderEngine::renderFullScreenQuad(){
        float vertices[] = {
                // positions          // texture coords
                 1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
                 1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
                -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
                -1.0f,  1.0f, 0.0f,   0.0f, 1.0f    // top left
            };
            unsigned int indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
            };
        
            // Link shaders to create a shader program
            unsigned int shaderProgram = 0;
            std::string result;
            std::string result2;
            ReadFileAsCString("Shaders/Quad.vert.glsl",result2);
            ReadFileAsCString("Shaders/Quad.frag.glsl",result);
            compileAndLinkShaderProgram(shaderProgram, result.c_str(), result2.c_str());
            // Generate and bind a Vertex Array Object (VAO)
            unsigned int VAO, VBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
        
            glBindVertexArray(VAO);
        
            unsigned int EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
            // Bind and set vertex buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
            // Set vertex attribute pointers
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        
            // Set vertex attribute pointers
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        
            // Unbind the VAO
            glBindVertexArray(0);




            

}
    
    