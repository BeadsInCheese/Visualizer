#version 450 core

out vec4 FragColor;
in vec2 texcoord;
layout(std430, binding = 0) buffer AudioBuffer {
    float audioSamples[];
    
};
vec4 getColor(float val){
    return mix(vec4(0,1,0,1),vec4(1,0,0,1),val);

}
uniform float aspect;
void main(){
    float bufferSize=16384;
    vec2 uv=(texcoord-vec2(0.5,0.4));
    
    uv.y*=aspect;
    float tau=6.28;
    float angle=atan(uv.x,uv.y)+3.14;
    angle=angle*bufferSize/tau;
    int x=int(angle/100.0)*100;
    float s=abs((audioSamples[x])/5.0)*50.;
    float l=(length((uv))-0.01);
    l=step(l-max(0.001*s,0),0.09)-step(l+0.01,0.09);

    //l=clamp((-1000.0*l*l + 10.0*l)*200.0, 0.0 ,1.0);
    FragColor =mix(vec4(0.0f, 0.0, 0.0, 1.0f),getColor(length(((uv)-0.01))*4.),l);
    //FragColor.x=audioSamples[x];


}
