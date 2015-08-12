#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT {
  vec2 tc;
  vec3 n
}fs_in;

 uniform sampler2D colorTex;
 uniform sampler2D normalTex;

void main(void)
{
   vec4 texColor = texture2D(colorTex, vs_out.tc);
   vec4

   fragColor = ;

}