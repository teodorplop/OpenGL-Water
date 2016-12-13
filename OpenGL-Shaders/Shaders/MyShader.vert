// Vertex Shader

#version 400

uniform mat4 gWorld;
uniform mat4 gProj;
uniform mat4 gCamera;

layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec2 inTextureCoord;
layout (location = 2) in vec3 inNormal;

out DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
} Out;

uniform float textureTiling;

void main() {
  vec4 worldPosition = gWorld * inPosition;
	vec4 positionRelativeToCamera = gCamera * worldPosition;
	
	gl_Position = gProj * positionRelativeToCamera;
	
	Out.worldPosition = worldPosition.xyz;
	Out.textureCoord = inTextureCoord * textureTiling;
	Out.normal = (gWorld * vec4(inNormal, 0.0f)).xyz;
}