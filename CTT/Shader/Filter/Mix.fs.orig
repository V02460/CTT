#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

uniform sampler2D sourceTexture2;
uniform float mixRatio;

varying vec2 texcrd;

void main() {
    vec4 color1 = texture2D(_sourceTexture, texcrd);
    vec4 color2 = texture2D(sourceTexture2, texcrd);
	gl_FragColor = mix(color1, color2, mixRatio);
}