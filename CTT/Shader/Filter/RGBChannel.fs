#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

varying vec2 texcrd;

uniform vec4 colorFactor;

void main() {
    vec4 color = texture2D(_sourceTexture, texcrd);
	gl_FragColor = color * colorFactor;
}