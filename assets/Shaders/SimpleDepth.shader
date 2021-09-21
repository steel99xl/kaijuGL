#Shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normalizedpos;
layout(location = 2) in vec2 texCord;
layout(location = 3) in float texIndex;

uniform mat4 LightSpaceMatrix;

// This just just to make testing easier 
uniform mat4 Modle;

void main(){
    gl_Position = LightSpaceMatrix * Modle * vec4(position, 1.0);
}


#Shader fragment
#version 330 core

void main(){

}