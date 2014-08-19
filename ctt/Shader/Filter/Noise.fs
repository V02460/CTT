#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;
uniform float intensity;

varying vec2 texcrd;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec4 color = texture2D(_sourceTexture, texcrd);
    float noise = rand(texcrd);
    
	gl_FragColor = vec4(mix(color.rgb, vec3(noise), intensity), 1.f);
}