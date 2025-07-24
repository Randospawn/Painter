#version 460 core


layout(location = 0) in vec2 vert;
layout(location = 1) in vec2 texCoord;
out vec2 uv;


void main() {
	uv = texCoord;
	gl_Position = vec4(vert, 0.1, 1.0);
}

