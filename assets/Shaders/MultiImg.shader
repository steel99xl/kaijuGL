#Shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normalizedpos;
layout(location = 2) in vec2 texCord;
layout(location = 3) in float texIndex;

out vec3 v_Normalized;
out vec3 v_FragPos;
out vec2 v_TexCord;
out float v_TexIndex;

uniform mat4 Modle;
uniform mat4 View;
uniform mat4 Projection;

void main(){
gl_Position = Projection * View * Modle * vec4(position, 1.0);
v_FragPos = vec3(Modle * vec4(position, 1.0));
v_Normalized = normalizedpos;
v_TexCord  = texCord;
v_TexIndex = texIndex;
}



#Shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normalized;
in vec3 v_FragPos;
in vec2 v_TexCord;
in float v_TexIndex;

uniform vec4 u_Color;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;

uniform vec3 u_camPos;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main(){
    vec4 texColor;
    vec4 ObjectColor;
    int index  = int(v_TexIndex);

    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 ambient = ambientStrength * u_lightColor;

    vec3 norm = normalize(v_Normalized);
    vec3 lightDir = normalize(u_lightPos - v_FragPos);

    vec3 viewDir = normalize(u_camPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    if(index == 1){
        texColor = texture(u_Texture0, v_TexCord); 
    } else if(index == 2){
        texColor = texture(u_Texture1, v_TexCord); 
    } else if(index == 3){
        texColor = texture(u_Texture2, v_TexCord); 
    } else {
        texColor = u_Color;
    }
    if(texColor == u_Color){
        ObjectColor = texColor;
    } else{
        ObjectColor = texColor + u_Color;
    }


    color = vec4((ambient+ diffuse+ specular), 1.0) * ObjectColor;
}