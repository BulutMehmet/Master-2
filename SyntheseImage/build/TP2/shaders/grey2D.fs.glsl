#version 300 es
precision mediump float;

in vec3 vFragColor;

out vec3 fFragColor;

void main() {
  float greyValue = (vFragColor.r + vFragColor.g + vFragColor.b) / 3.0;
  fFragColor = vec3(greyValue, greyValue, greyValue);
};