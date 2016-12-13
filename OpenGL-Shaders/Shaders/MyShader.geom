// Geometry shader

#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices =	3) out;

out vec3 fColor;

void main() {
	fColor = vec3(1, 0, 0);
  for(int i=0; i<3; i++) {
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
}