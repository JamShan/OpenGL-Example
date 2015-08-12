#version 430 core

layout (triangles) in;

layout (triangle_strip, max_vertices = 6) out;


in VS_OUT 
{
  vec3 normal;
}vs_out[];

out GS_OUT
{
  vec3 normal;
  vec3 lightDir;
  vec3 viewDir;
  vec4 color;
}gs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 lightPos = vec3(0.0f, 0.0f, 2.0f);
uniform vec3 camPos = vec3(0.0f, 0.0f, 4.0f);

void main(void)
{
 
 //Make the second sphere translation
  mat4 trans = model;
  trans[3][0] = -1.5f;

  for (int i = 0; i != gl_in.length(); ++i)
  {
    mat4 mv  = view * trans;
    mat4 mvp = proj * mv;
    gl_Position = mvp *  gl_in[i].gl_Position;
	vec4 worldPos = mv * gl_in[i].gl_Position;

    gs_out.normal   = mat3(mv) * vs_out[i].normal;
    gs_out.viewDir  = camPos -   worldPos.xyz;
    gs_out.color    = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    gs_out.lightDir = lightPos - worldPos.xyz;
	EmitVertex(); 
   }
   EndPrimitive();


   ///////////////////////////////////////////////////////////////////////
    trans[3][0] = +1.5f;
  
   for (int i = 0; i != gl_in.length(); ++i)
   {
       mat4 mv  = view * trans;
       mat4 mvp = proj * mv;
       gl_Position = mvp *  gl_in[i].gl_Position;
	   vec4 worldPos = mv * gl_in[i].gl_Position;
	   
       gs_out.normal   = mat3(mv) * vs_out[i].normal;
       gs_out.viewDir  = camPos -   worldPos.xyz;
       gs_out.color    = vec4(1.0f, 1.0f, 0.0f, 1.0f);
       gs_out.lightDir = lightPos - worldPos.xyz;

       EmitVertex();
   }

   EndPrimitive();
   
}
