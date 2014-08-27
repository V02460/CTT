#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

vec4 encodeFloatRGBA(float v) {
	vec4 enc = vec4(1.f, 256.f, 65025.f, 16581375.f) * v;
	enc = fract(enc);
	enc -= enc.yzww * vec4(vec3(1.f / 255.f), 0.f);
	return enc;
}

void main() {
	ivec2 pos = ivec2(gl_FragCoord.xy);

	// get the 16x16 block this pixel belongs to
	ivec2 blockCorner = (pos / 16) * 16;

	// calculate the relative position to the block corner
	ivec2 posInBlock = pos - blockCorner;

	// which bucket the pixel represents depens on its position inside the block
	int bucketNr = 16 * posInBlock.y + posInBlock.x;

	int bucketCount = 0;
	int totalPixelsProcessed = 0;

	// loop over all texels in the source texture 
	ivec2 delta;
	for (delta.y = 0; delta.y < 16; delta.y++) {
		for (delta.x = 0; delta.x < 16; delta.x++) {
			ivec2 lookupPos = blockCorner + delta;

	 		vec4 color = texelFetch(_sourceTexture, lookupPos, 0);

	 		bool isInSource = (lookupPos.x < _sourceSize.x && lookupPos.y < _sourceSize.y);
			
	 		bucketCount += int(bucketNr == int(255.f * color.b)) * int(isInSource);
	 		totalPixelsProcessed += int(isInSource);
		}
	}

	float normalizedBucketValue = float(bucketCount) / totalPixelsProcessed;
	float blockWeight = totalPixelsProcessed / 256.f;

	vec4 image = texelFetch(_sourceTexture, pos, 0);

	float returnValue = normalizedBucketValue * blockWeight;

	gl_FragColor = encodeFloatRGBA(returnValue);
}