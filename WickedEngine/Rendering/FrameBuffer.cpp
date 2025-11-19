#include "FrameBuffer.h"

#ifdef _WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#elif __APPLE__

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

#include "Texture.h"

FrameBuffer::FrameBuffer(TexturePtr tex, AttachmentType texType)
{
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	unsigned int attachmentType = 0;
	if (texType == AttachmentType::DepthAttach)
		attachmentType = GL_DEPTH_ATTACHMENT;

	const int mipmapLevel = 0;
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType,
						   GL_TEXTURE_2D, id, mipmapLevel);

	width = tex->GetWidth();
	height = tex->GetHeight();

	//TO DO: Wont work with color frame buffers with how it is implemented
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//Unbinds frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &id);
}

void FrameBuffer::Activate()
{
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	if (type == AttachmentType::DepthAttach)
		glClear(GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::Deactivate()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
}