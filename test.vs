#version 130

uniform mat4 pvmMatrix;
in vec2 inPosition;

void main(void) {
    gl_Position = pvmMatrix * vec4(inPosition, 0.0, 1.0);
}
