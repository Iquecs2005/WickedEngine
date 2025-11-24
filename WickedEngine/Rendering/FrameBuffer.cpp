#include "FrameBuffer.h"

#ifdef _WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#elif __APPLE__

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

#include "../error.h"

#include "BaseTexture.h"

FrameBuffer::FrameBuffer(BaseTexturePtr tex, AttachmentType texType)
	: type(texType)
{
	Error::Check("Start Frame Buffer Generation");

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	unsigned int attachmentType = 0;
	if (texType == AttachmentType::DepthAttach)
		attachmentType = GL_DEPTH_ATTACHMENT;

	const int mipmapLevel = 0;
	glFramebufferTexture(GL_FRAMEBUFFER, attachmentType,
						 tex->GetId(), mipmapLevel);

	Error::Check("Check Frame Buffer Generation");

	width = tex->GetWidth();
	height = tex->GetHeight();

	//TO DO: Wont work with color frame buffers with how it is implemented
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//Unbinds frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Error::Check("End Frame Buffer Generation");
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &id);
}

void FrameBuffer::Activate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, width, height);
	
}

void FrameBuffer::Deactivate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
}