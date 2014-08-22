#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

uniform vec2 direction;
uniform float radius;

varying vec2 texcrd;

void main() {

	vec4 color = vec4(0.f);
	float step = 1 / radius;

	for (float i = 0; i < 1; i += step) {
		color += texture2D(_sourceTexture, texcrd + i*direction);
		color += texture2D(_sourceTexture, texcrd - i*direction);

	}

	color /= 2*radius;

	gl_FragColor = color;
}