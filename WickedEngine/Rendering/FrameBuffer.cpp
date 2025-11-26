#include "FrameBuffer.h"

#ifdef _WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#elif __APPLE__

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

#include <iostream>

#include "../error.h"

FrameBuffer::FrameBuffer(int width, int height)
	: width(width), height(height)
{
}

FrameBuffer::FrameBuffer(int width, int height, DepthTexturePtr depthTex, std::initializer_list<BaseTexturePtr> colorTextures)
	: width(width), height(height), depthTex(depthTex), colorTextures(colorTextures)
{
	GenFrameBuffer(width, height, depthTex, colorTextures);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &id);
}

void FrameBuffer::GenFrameBuffer()
{
	Error::Check("Start Frame Buffer Generation");

	if (id != 0)
	{
		std::cerr << "Frame Buffer already generated" << std::endl;
		return;
	}

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	const int mipmapLevel = 0;
	if (depthTex != nullptr)
	{
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTex->GetId(), mipmapLevel);

		if (width != depthTex->GetWidth() || height != depthTex->GetHeight())
		{
			std::cerr << "Wrong Depth Texture dimension in Frame Buffer creation" << std::endl;
			return;
		}
	}

	int i = 0;
	for (BaseTexturePtr colorTex : colorTextures)
	{
		unsigned int texId = colorTex->GetId();
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, texId, 0);
		i++;

		if (width != colorTex->GetWidth() || height != colorTex->GetHeight())
		{
			std::cerr << "Wrong Color Texture " << i << " dimension in Frame Buffer creation" << std::endl;
			return;
		}
	}

	Error::Check("Check Frame Buffer Generation");

	//Unbinds frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Error::Check("End Frame Buffer Generation");
}

void FrameBuffer::GenFrameBuffer(int width, int height, DepthTexturePtr depthTex, std::initializer_list<BaseTexturePtr> colorTextures)
{
	this->width = width;
	this->height = height;
	this->depthTex = depthTex;
	this->colorTextures = colorTextures;

	GenFrameBuffer();
}

void FrameBuffer::Activate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, width, height);
	
	if (colorTextures.empty())
	{
		glDrawBuffer(GL_NONE);
	}
	else
	{
		std::vector<GLenum> buffers;
		for (int i = 0; i < colorTextures.size(); i++) 
		{
			buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
		}
		glDrawBuffers(colorTextures.size(), buffers.data());
	}
}

void FrameBuffer::Deactivate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
}