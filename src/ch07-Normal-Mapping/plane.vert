#version 430 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 BiTangent;

out VS_OUT {
  vec3 FragPos;
  vec2 TexCoords;
  vec3 TangentLightPos;
  vec3 TangentViewPos;
  vec3 TangentFragPos;

}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 camPos = vec3(0.0f, 0.0f, 2.0f);
uniform vec3 lightPos = vec3(1.0f, 0.0f, 5.0f);

void main(void)
{

   mat4 mvp = proj * view * model;

    vs_out.FragPos = vec3(model * vec4(Position, 1.0));   
    vs_out.TexCoords = TexCoord;

    mat3 normalMatrix = mat3( transpose( inverse(model) ) );
    vec3 T = normalize(normalMatrix * Tangent);
    vec3 B = normalize(normalMatrix * BiTangent);
    vec3 N = normalize(normalMatrix * Normal);    
    
    mat3 TBN = transpose(mat3(T, B, N));  

    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * camPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;

   gl_Position = mvp * vec4(Position, 1.0f);

}