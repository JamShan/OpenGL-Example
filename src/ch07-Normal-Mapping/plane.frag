#version 430 core

layout (location = 0) out vec4 fragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
}vs_out;

 uniform sampler2D colorTex;
 uniform sampler2D normalTex;

void main(void)
{
   vec4 textureColor = texture2D(colorTex, vs_out.TexCoords);

    // Obtain normal from normal map in range [0,1]
    vec3 normal = texture(normalTex, vs_out.TexCoords).rgb;
    // Transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space


    // Ambient
    vec3 ambient =  0.1f * textureColor.xyz;

    // Diffuse
    vec3  lightDir = normalize(vs_out.TangentLightPos - vs_out.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3  diffuse = diff * textureColor.xyz * 0.5f;

    // Specular
    vec3 viewDir = normalize(vs_out.TangentViewPos - vs_out.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2f) * spec;
    
	vec4 result  = vec4( (ambient + diffuse + specular), 1.0f);
    fragColor = result; // texture(normalTex, vs_out.TexCoords);

}