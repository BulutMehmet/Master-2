#version 300 es
precision mediump float;

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;

void main() {
  vec2 origin = vec2(0.0, 0.0);
  float alpha = 2.0;
  float beta = 55.0;
  fFragColor = vec3(vFragColor.r * alpha * exp(-beta * distance(vFragPosition, origin) * distance(vFragPosition, origin)), vFragColor.g * alpha *exp(-beta * distance(vFragPosition, origin) * distance(vFragPosition, origin)), vFragColor.b * alpha * exp(-beta * distance(vFragPosition, origin) * distance(vFragPosition, origin)));
};