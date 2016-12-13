// Fragment Shader 

#version 400

in DATA {
	vec4 worldPosition;
	vec2 textureCoord;
	vec3 normal;
	vec3 toCamera;
} In;

uniform sampler2D reflectionSampler;
uniform sampler2D refractionSampler;
uniform sampler2D dudvSampler;

uniform float moveFactor;
uniform float distorsionStrength;

out vec4 outColor;

void main() {
	vec2 normalizedDeviceCoord = (In.worldPosition.xy / In.worldPosition.w) / 2.0 + 0.5;
	vec2 reflectionTextureCoord = vec2(normalizedDeviceCoord.x, -normalizedDeviceCoord.y);
	vec2 refractionTextureCoord = vec2(normalizedDeviceCoord.x, normalizedDeviceCoord.y);

	vec2 distortedTexCoords = texture(dudvSampler, vec2(In.textureCoord.x + moveFactor, In.textureCoord.y)).rg * 0.1;
	distortedTexCoords = In.textureCoord + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);
	vec2 totalDistortion = (texture(dudvSampler, distortedTexCoords).rg * 2.0 - 1.0) * distorsionStrength;

	refractionTextureCoord += totalDistortion;
	refractionTextureCoord = clamp(refractionTextureCoord, 0.001, 0.999);

	reflectionTextureCoord += totalDistortion;
	reflectionTextureCoord.x = clamp(reflectionTextureCoord.x, 0.001, 0.999);
	reflectionTextureCoord.y = clamp(reflectionTextureCoord.y, -0.999, -0.001);

	vec4 reflectColor = texture(reflectionSampler, reflectionTextureCoord);
	vec4 refractColor = texture(refractionSampler, refractionTextureCoord);

	vec3 viewVector = normalize(In.toCamera);
	float refractiveFactor = dot(viewVector, vec3(0, 1, 0));
	refractiveFactor = pow(refractiveFactor, 0.5);
	refractiveFactor = clamp(refractiveFactor, 0.001, 0.999);

	outColor = mix(reflectColor, refractColor, refractiveFactor);
	outColor = mix(outColor, vec4(0.0, 0.3, 0.5, 1.0), 0.2);
}