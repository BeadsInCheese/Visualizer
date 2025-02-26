#version 450 core

out vec4 FragColor;
in vec2 texcoord;
uniform float aspect;
void main(){
    vec2 uv=texcoord;
    uv.y*=aspect;

    float l=(length((uv-vec2(0.5,0.5*aspect)))-0.1);
    l=clamp((-1000.0*l*l + 10.0*l)*200.0, 0.0 ,1.0);
    FragColor =mix(vec4(0.0f, 0.0, 0.0, 1.0f),vec4(1.0, 1.0, 1.0, 1.0f),l);



}
