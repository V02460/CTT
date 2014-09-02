#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

uniform vec2 direction;
uniform float radius;

varying vec2 texcrd;

void main() {
	vec4 color = texture2D(_sourceTexture, texcrd);

	gl_FragColor = vec4(vec3(1.f) - color.rgb, color.a);
}