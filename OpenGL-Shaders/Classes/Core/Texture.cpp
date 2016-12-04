#include "Texture.h"
#include "..\Utils\ImageUtils.h"

Texture::Texture() {
}
Texture::Texture(const std::string& fileName, bool hasTransparency) : fileName(fileName) {
	BYTE* pixels = ImageUtils::Load_Image(fileName.c_str(), &width, &height);
	this->hasTransparency = hasTransparency;

	glGenTextures(1, &textureID);
	Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Unbind();
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}

bool Texture::HasTransparency() {
	return hasTransparency;
}

void Texture::Bind(int index) {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture* Texture::CreateTextureAttachment(int width, int height) {
	Texture* texture = new Texture();
	texture->width = width, texture->height = height;
	texture->hasTransparency = false;

	glGenTextures(1, &(texture->textureID));
	glBindTexture(GL_TEXTURE_2D, texture->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->textureID, 0);

	return texture;
}