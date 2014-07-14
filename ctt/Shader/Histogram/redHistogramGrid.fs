uniform vec2 sourceSize;

void main() {
	int counter = 0;

	vec2 blockCorner = floor(gl_FragCoord.xy / 16) * 16;
	vec2 positionDelta = gl_FragCoord.xy - blockCorner;
	int bucketNr = 16 * positionDelta.y + positionDelta.x;

	int bucketCount = 0;
	int totalPixelsProcessed = 0;

	vec2 delta;
	for (delta.y = 0; delta.y < 16; delta.y++) {
		for (delta.x = 0; delta.x < 16; delta.x++) {
			vec2 absolutePosition = blockReferencePoint + delta;
			vec4 color = texelFetch(sourceImage, absolutePosition, 0);

			bool isInSource = (absolutePosition < sourceSize);
			
			count += (bucketNr == color.r) * isInSource;
			totalPixelsProcessed += isInSource;
		}
	}

	float relativeAmmount = count / totalPixelsProcessed;

	gl_FragColor = vec4(relativeAmmount, relativeAmmount, relativeAmmount, 1.f);
}