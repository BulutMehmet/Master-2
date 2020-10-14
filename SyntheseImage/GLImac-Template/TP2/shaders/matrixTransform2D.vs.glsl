#version 300 es
precision mediump float;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;

mat3 translate(float tx, float ty){
    return mat3(vec3(1.0, 0.0, 0.0), vec3(0.0,1.0,0.0), vec3(tx, ty, 1.0));
}

mat3 scale(float sx, float sy){
    return mat3(vec3(sx, 0.0, 0.0), vec3(0.0, sy, 0.0), vec3(0.0, 0.0, 1.0));
}

mat3 rotation(float alpha){
    return mat3(vec3(cos(alpha), sin(alpha), 0), vec3(-sin(alpha), cos(alpha), 0), vec3(0, 0, 1));
}

void main() {
  vFragColor = aVertexColor;

  vec3 rotationPoint = rotation(radians(45.0)) * vec3(0.5, 0.0, 1.0);
  vec3 translated = translate(rotationPoint.x, rotationPoint.y) * vec3(aVertexPosition, 1.0);
  vec3 scaled = scale(0.5, 0.5) * vec3(translated.xy, 1.0);
  //vec3 translated = translate(0.5, 0.0) * vec3(aVertexPosition, 1.0);
  //vec3 rotated = rotation(radians(45.0)) * translated;
  //vec3 scaled = scale(0.5,0.5) * rotated;
  gl_Position = vec4(scaled.xy, 0, 1);
};