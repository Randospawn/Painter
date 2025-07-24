#version 460 core


uniform sampler2D txtr;
in vec2 uv;


void main() {
	
	
	gl_FragColor = vec4((texture(txtr, uv).rgb + vec3(1.0, 0.0, 0.0)), 1.0);
}
