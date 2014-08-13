#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

float decodeFloatRGBA(vec4 rgba) {
	return dot(rgba, vec4(1.f, 1.f / 255.f, 1.f / 65025.f, 1.f / 160581375.f));
}

void main() {
	ivec2 pos = ivec2(gl_FragCoord.xy);

	//int foo = pos.x / 16
	ivec2 lookupPos = ivec2(mod(pos.x, 16), pos.x / 16);

	// get max height
	float maxHeight = 0.f;
	ivec2 delta;
	for (delta.y = 0; delta.y < 16; delta.y++) {
		for (delta.x = 0; delta.x < 16; delta.x++) {
			vec4 color = texelFetch(_sourceTexture, delta, 0);
			float value = decodeFloatRGBA(color);

			maxHeight = max(maxHeight, value);
		}
	}

	vec4 color = texelFetch(_sourceTexture, lookupPos, 0);
	float value = decodeFloatRGBA(color);

	if (float(pos.y) < value * _targetSize.y / maxHeight) {
		gl_FragColor = vec4(1.f, 0.f, 0.f, 1.f);
	} else {
		gl_FragColor = vec4(0.f, 1.f, 0.f, 0.f);
	}
}

//x < (perc * height) * height / height*maxHeight