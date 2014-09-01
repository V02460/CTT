#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

varying vec2 texcrd;

uniform sampler2D sourceTexture2;

vec4 encodeFloatRGBA(float v) {
	vec4 enc = vec4(1.f, 255.f, 65025.f, 16581375.f) * v;
	enc = fract(enc);
	enc -= enc.yzww * vec4(vec3(1.f / 255.f), 0.f);
	return enc;
}

void main() {
    vec3 color1 = texture2D(_sourceTexture, texcrd).rgb;
    vec3 color2 = texture2D(sourceTexture2, texcrd).rgb;

    gl_FragColor = encodeFloatRGBA(distance(color1, color2));
}