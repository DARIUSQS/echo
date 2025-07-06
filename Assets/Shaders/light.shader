#shader vertex

#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_Color;

void main()
{
    color = vec4(u_Color, 1.0f);
}
