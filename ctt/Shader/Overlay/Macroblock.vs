#version 130

attribute vec2 aPosition;
attribute vec4 aColor;
attribute vec2 aTexcrd;

varying vec2 texcrd;
varying vec4 color;

void main() {
    texcrd = aTexcrd;
    color = aColor;

    gl_Position = vec4(aPosition, 0.f, 1.f);
}