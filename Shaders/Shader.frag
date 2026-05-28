// Fragment Shader 

#version 400

in DATA {
	vec3 worldPosition;
	vec2 textureCoord;
	vec3 normal;
} In;

struct DirectionalLight {
	vec3 color;
	float intensity;
	vec3 direction;
};

uniform DirectionalLight directionalLight;
uniform sampler2D textureSampler;

out vec4 outColor;

vec4 CalculateAmbientColor() {
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.intensity;

	return ambientColor;
}
vec4 CalculateDiffuseColor() {
	float diffuseFactor = dot(normalize(In.normal), -directionalLight.direction);
	diffuseFactor = max(0.0f, diffuseFactor);
	vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.intensity * diffuseFactor;

	return diffuseColor;
}

void main() {
  vec4 ambientColor = CalculateAmbientColor();
	vec4 diffuseColor = CalculateDiffuseColor();
	vec4 textureColor = texture(textureSampler, In.textureCoord);

	outColor = textureColor * (ambientColor + diffuseColor);
}