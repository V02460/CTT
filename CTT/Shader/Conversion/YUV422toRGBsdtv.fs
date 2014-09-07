#version 130

uniform ivec2 _sourceSize;
uniform ivec2 _targetSize;
uniform sampler2D _sourceTexture;
varying vec2 texcrd;

uniform sampler2D uChannel;
uniform sampler2D vChannel;

void main() {
	vec4 yuv1 = vec4(texture2D(_sourceTexture, texcrd).r,
                     texture2D(uChannel, texcrd).r - 0.5f,
                     texture2D(vChannel, texcrd).r - 0.5f,
                     1.f);

    mat4 A;
    A[0] = vec4(     1.f,       1.f,       1.f, 0.f);
    A[1] = vec4(     0.f, -0.39465f, 2.203211f, 0.f);
    A[2] = vec4(1.13983f, -0.58060f,       0.f, 0.f);
    A[3] = vec4(     0.f,       0.f,       0.f, 1.f);

    gl_FragColor = A * yuv1;
}