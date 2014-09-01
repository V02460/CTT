#version 130

uniform sampler2D tex;

varying vec2 texcrd;
varying vec2 pos;

void main() {
	vec4 outColor = texture2D(tex, texcrd);
	gl_FragColor = outColor;
}