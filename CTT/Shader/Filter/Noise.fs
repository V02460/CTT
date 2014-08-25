#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

uniform float intensity;
uniform float time;

varying vec2 texcrd;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233)) + time) * 43758.5453);
}

void main() {
    vec4 color = texture2D(_sourceTexture, texcrd);
    vec4 noiseColor = vec4(vec3(rand(texcrd), 1.f);
	gl_FragColor = vec4(mix(color.rgb, noiseColor.rgb, intensity), color.a);
}