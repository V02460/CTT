#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

vec4 encodeFloatRGBA(float v) {
	vec4 enc = vec4(1.f, 255.f, 65025.f, 16581375.f) * v;
	enc = fract(enc);
	enc -= enc.yzww * vec4(vec3(1.f / 255.f), 0.f);
	return enc;
}

float decodeFloatRGBA(vec4 rgba) {
	return dot(rgba, vec4(1.f, 1.f / 255.f, 1.f / 65025.f, 1.f / 16581375.f));
}

void main() {
	ivec2 pos = ivec2(gl_FragCoord.xy);

	float returnValue = 0.f;
	int inSourceCnt = 0;

	// compact 4 texels to one
	ivec2 delta;
	for (delta.y = 0; delta.y < 2; delta.y++) {
		for (delta.x = 0; delta.x < 2; delta.x++) {
			ivec2 lookupPos = pos + delta;

			bool isInSource = (lookupPos.x < _sourceSize.x && lookupPos.y < _sourceSize.y);

	 		vec4 color = texelFetch(_sourceTexture, lookupPos, 0) * int(isInSource);

	 		returnValue += decodeFloatRGBA(color);
	 		inSourceCnt += int(isInSource);
		}
	}

	returnValue /= inSourceCnt;

	gl_FragColor = encodeFloatRGBA(returnValue);
}