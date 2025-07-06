#shader vertex

#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normals;
layout(location = 2) in vec2 a_TexCoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
uniform float u_Time;

out vec3 v_Normal;
out vec2 v_TexCoords;
out vec3 v_FragPos;

void main()
{
    v_TexCoords = a_TexCoords;
    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normals;
    v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec2 v_TexCoords;
in vec3 v_FragPos;

uniform vec3 u_CameraPos;
uniform sampler2D u_Texture;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform float u_AmbientStrenght;

void main()
{
    vec3 norm = normalize(v_Normal); 
    vec3 LightDir = normalize(u_LightPos - v_FragPos);

    // ambient
    vec3 ambient = u_AmbientStrenght * u_LightColor;
    
    ///difuse
    float diff = max(dot(norm, LightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;
    
    // specular 
    
    vec3 reflectLight = reflect(-LightDir, v_Normal);
    vec3 ViewDir = normalize(u_CameraPos - v_FragPos);

    vec3 specular = 0.5 * pow(max(dot(ViewDir, reflectLight), 0.0f), 256) * u_LightColor;

    vec3 result = ambient + diffuse + specular;

    color = vec4(result, 1.0f) * texture(u_Texture, v_TexCoords);
}
