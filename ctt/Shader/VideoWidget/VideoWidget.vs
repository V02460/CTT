#version 130

attribute vec2 aPos;
attribute vec2 aTexcrd;

varying vec2 pos;
varying vec2 texcrd;

void main() {
	pos = aPos;
    texcrd = aTexcrd;
    gl_Position = vec4(aPos, 0.0, 1.0);
}