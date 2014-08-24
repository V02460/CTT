#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

varying vec2 texcrd;

void main() {
	gl_FragColor = texture2D(_sourceTexture, texcrd);
}