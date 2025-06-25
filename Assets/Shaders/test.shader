#shader vertex

#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec2 v_TexCoords;

void main()
{
    v_TexCoords = a_TexCoords;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main()
{
///   vec4 intermi = vec4(v_Position * 0.5 + 0.5, 1.0);
 //   color = v_Color + intermi;
    color = texture(u_Texture, v_TexCoords);
}
