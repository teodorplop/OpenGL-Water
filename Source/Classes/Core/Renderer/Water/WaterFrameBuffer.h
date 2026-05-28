#pragma once

#include <GL/glew.h>
#include "../../Texture.h"

class WaterFrameBuffer {
private:
	static const int reflectionWidth, reflectionHeight;
	static const int refractionWidth, refractionHeight;

	GLuint reflectionFrameBuffer, reflectionDepthBuffer;
	GLuint refractionFrameBuffer, refractionDepthTexture;
	Texture *reflectionTexture, *refractionTexture;

	GLuint CreateFrameBuffer();
	GLuint CreateDepthTextureAttachment(int width, int height);
	GLuint CreateDepthBufferAttachment(int width, int height);
	void BindFrameBuffer(GLuint buffer, int width, int height);

public:
	WaterFrameBuffer();
	~WaterFrameBuffer();

	void Clear();
	void BindReflectionBuffer();
	void BindRefractionBuffer();
	void UnbindBuffer();
	Texture* GetReflectionTexture();
	Texture* GetRefractionTexture();
	GLuint GetRefractionDepthTexture();
};