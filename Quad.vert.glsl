#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 UV;
out vec2 texcoord;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texcoord=UV;
    
    
}
