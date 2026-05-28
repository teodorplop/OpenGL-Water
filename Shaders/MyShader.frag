// Fragment Shader 

#version 400

in DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
} In;

uniform sampler2D textureSampler;

out vec4 outColor;

void main() {
	outColor = texture(textureSampler, In.textureCoord);
}