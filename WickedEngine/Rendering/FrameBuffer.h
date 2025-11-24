#include <memory>

class FrameBuffer;
using FrameBufferPtr = std::shared_ptr<FrameBuffer>;

#pragma once

#include "BaseTexture.h"

enum AttachmentType
{
	ColorAttach, DepthAttach
};

class FrameBuffer
{
public:
	static inline FrameBufferPtr Make(BaseTexturePtr tex, AttachmentType texType);
	~FrameBuffer();

	void Activate();
	void Deactivate();
private:
	unsigned int id;
	unsigned int width;
	unsigned int height;
	AttachmentType type;

	FrameBuffer(BaseTexturePtr tex, AttachmentType texType);
};

inline FrameBufferPtr FrameBuffer::Make(BaseTexturePtr tex, AttachmentType texType)
{
	return FrameBufferPtr(new FrameBuffer(tex, texType));
}