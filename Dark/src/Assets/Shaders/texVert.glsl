#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out vec2 v_TexCoords;

void main() {

	v_TexCoords = aTexCoords;

	gl_Position = u_ProjectionView * u_Transform * vec4(aPos, 1.0f);

}