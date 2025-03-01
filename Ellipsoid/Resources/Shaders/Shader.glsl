#shader vertex
#version 410 core

layout(location = 0) in vec3 a_Position;

out vec4 v_Color;

void main() {
    gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 410 core

out vec4 FragColor;

void main() {
    FragColor = vec4(0.5, 0.5, 0.5, 1.0);
}
