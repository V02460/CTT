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

    // Not actually a mix filter - more a overlay filter
    float alpha = mixRatio * color2.a;
	gl_FragColor.rgb = mix(color1.rgb, color2.rgb, alpha);
	gl_FragColor.a = alpha + (1 - alpha) * color1.a;
}