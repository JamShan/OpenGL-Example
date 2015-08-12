#version 430 core

layout (location = 0) out vec4 fragColor;

in GS_OUT
{
 vec3 normal;
 vec3 lightDir;
 vec3 viewDir;
  vec4 color;
}gs_out;


uniform vec3 diffuse_material = vec3(0.5, 0.2, 0.7);
uniform float power = 64.0f;
uniform vec3 specular_material = vec3(0.7);

void main(void)
{
    vec3 N = normalize(gs_out.normal);
	vec3 L = normalize(gs_out.lightDir);
	vec3 V = normalize(gs_out.viewDir);

	vec3 R = reflect(-L, N);
	vec3 diffuse = max(dot(N, L), 0.0) * diffuse_material;
	vec3 specular = pow(max(dot(R, V), 0.0), power) * specular_material;

    vec3 result = (specular + diffuse);
	fragColor = gs_out.color * vec4(result, 1.0f);
}