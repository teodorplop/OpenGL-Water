// Vertex Shader

#version 400

uniform mat4 gWorld;
uniform mat4 gProj;
uniform mat4 gCamera;

layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec2 inTextureCoord;
layout (location = 2) in vec3 inNormal;

out DATA {
	vec4 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	vec3 toCamera;
	vec3 fromLight;
} Out;

uniform float textureTiling;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;

void main() {
  vec4 worldPosition = gWorld * inPosition;
	vec4 positionRelativeToCamera = gCamera * worldPosition;

	Out.worldPosition = gProj * positionRelativeToCamera;
	Out.textureCoord = inTextureCoord * textureTiling;
	Out.normal = inNormal;
	Out.toCamera = cameraPosition - worldPosition.xyz;
	Out.fromLight = worldPosition.xyz - lightPosition;

	gl_Position = Out.worldPosition;
}