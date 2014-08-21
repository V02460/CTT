#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;
uniform sampler2D uChannel;
uniform sampler2D vChannel;
varying vec2 texcrd;

void main() {
	ivec2 pos = ivec2(gl_FragCoord.xy);

	vec4 luminance = texelFetch(_sourceTexture, pos, 0);
	vec4 chrominanceU = texelFetch(uChannel, pos, 0);
	vec4 chrominanceV = texelFetch(vChannel, pos, 0);

//	gl_FragColor = vec4(luminance.r + 1.13983f * chrominanceV.r, 
//						luminance.r - 0.39465f * chrominanceU.r - 0.58060f * chrominanceV.r, 
//						luminance.r + 2.203211f * chrominanceU.r, 
//						1.0f);

	gl_FragColor = vec4(luminance.r + 1.13983f * (chrominanceV.r - 0.5f), 
						luminance.r - 0.39465f * (chrominanceU.r - 0.5f) - 0.58060f * (chrominanceV.r - 0.5f),
						luminance.r + 2.203211f * (chrominanceU.r - 0.5f), 
						1.0f);
}