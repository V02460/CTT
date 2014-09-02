#version 130

varying vec2 texcrd;
varying vec4 color;

uniform sampler2D partitionMap;

void main() {
	vec4 partitionColor = texture2D(partitionMap, texcrd);
	
	gl_FragColor.rgb = mix(color.rgb, partitionColor.rgb, partitionColor.a);
	gl_FragColor.a = partitionColor.a + (1 - partitionColor.a) * color.a;
}