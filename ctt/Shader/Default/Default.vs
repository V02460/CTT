#version 130

attribute vec2 _pos;
varying vec2 texcrd;

void main() {
    texcrd = (_pos + 1.f) * 0.5f;

    gl_Position = vec4(_pos, 0.f, 1.f);
}