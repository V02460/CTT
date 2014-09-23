#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;
uniform sampler2D heatmapLookup;

varying vec2 texcrd;

float decodeFloatRGBA(vec4 rgba) {
	return dot(rgba, vec4(1.f, 1.f / 255.f, 1.f / 65025.f, 1.f / 16581375.f));
}

void main() {
	vec4 diffColor = texture2D(_sourceTexture, texcrd);
	float diff = decodeFloatRGBA(diffColor);

	gl_FragColor = texture2D(heatmapLookup, vec2(diff, 0.5));
}