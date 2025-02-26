#version 330 core
out vec4 FragColor;
in vec2 texcoord;
void main(){
    
    FragColor = vec4(1.0f, texcoord.x, texcoord.y, 1.0f);
    
}
