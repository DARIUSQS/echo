#shader vertex

#version 330 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 v_Position;

void main()
{
    v_Position = a_Position;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}

#shader fragment

#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;

void main()
{
///   vec4 intermi = vec4(v_Position * 0.5 + 0.5, 1.0);
 //   color = v_Color + intermi;
    
    color = vec4(v_Position * 0.5 + 0.5, 1.0);
}
