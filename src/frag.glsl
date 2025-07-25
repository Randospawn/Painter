#version 460 core


layout(rgba32f, binding = 0) uniform image2D txtr;
// in vec2 uv;
// uniform int m1d;


void main() {
	ivec2 tc = ivec2(gl_FragCoord.xy);
	imageStore(txtr, tc, vec4((imageLoad(txtr, tc).rgb + vec3(1.0, 0.0, 0.0)), 1.0));
	gl_FragColor = imageLoad(txtr, tc).rgba;
}
