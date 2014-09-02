#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

uniform vec2 direction;
uniform float radius;

varying vec2 texcrd;

void main() {

	vec4 color = vec4(0.f);

	vec2 step = normalize(direction) / _sourceSize;

	for (float i = 0; i < radius; i++) {
		color += texture2D(_sourceTexture, texcrd + i * step);
		color += texture2D(_sourceTexture, texcrd - i * step);
	}

	color /= 2*radius;

	gl_FragColor = color;
}