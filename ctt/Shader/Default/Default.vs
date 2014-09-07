#version 130

attribute vec2 _pos;
attribute vec2 _tex;
varying vec2 texcrd;

void main() {
    texcrd = _tex;

    gl_Position = vec4(_pos, 0.f, 1.f);
}