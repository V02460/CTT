#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;

varying vec2 texcrd;

void main() {
    vec4 color = texture2D(_sourceTexture, texcrd);
    float greyValue = dot(color.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
	gl_FragColor = vec4(vec3(greyValue), color.a);
}