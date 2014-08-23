#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;
varying vec2 texcrd;

void main() {
	ivec2 pos = ivec2(gl_FragCoord.x, gl_FragCoord.y);

	int absolutePixelNumber = (((_targetSize.x * pos.y) + pos.x) * 4);
	int effectivePixelNumber = absolutePixelNumber % (_sourceSize.x * _sourceSize.y);
	
	vec4 result = vec4(1.0f,1.0f,1.0f,1.0f);

	for (int i = 0; i < 4; i++)
	{
		if (!((absolutePixelNumber) >= (3 * _sourceSize.x * _sourceSize.y)))
		{
			ivec2 sourcePos = ivec2(effectivePixelNumber % _sourceSize.x, _sourceSize.y - (effectivePixelNumber / _sourceSize.x));
			vec4 describedPixel = texelFetch(_sourceTexture, sourcePos, 0);

			if ((absolutePixelNumber) >= (2 * _sourceSize.x * _sourceSize.y))
			{
				//is in v channel
				result[i] = 0.615f * describedPixel.r - 0.51499f * describedPixel.g - 0.10001f *describedPixel.b + 0.5f;
			} else if ((absolutePixelNumber) >= ( _sourceSize.x * _sourceSize.y))
			{
				//is in u channel
				result[i] = -0.14713f * describedPixel.r - 0.28886f * describedPixel.g + 0.436f *describedPixel.b + 0.5f;
			} else
			{
				//is in y channel
				result[i] = 0.299f * describedPixel.r + 0.587f * describedPixel.g + 0.114f *describedPixel.b;
			}
		}
		absolutePixelNumber++;
		effectivePixelNumber = absolutePixelNumber % (_sourceSize.x * _sourceSize.y);
	}

	gl_FragColor = result;
}