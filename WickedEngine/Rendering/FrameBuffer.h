#include <memory>

class FrameBuffer;
using FrameBufferPtr = std::shared_ptr<FrameBuffer>;

#pragma once

//#include "Texture.h"
class Texture;
using TexturePtr = std::shared_ptr<Texture>;

enum AttachmentType
{
	ColorAttach, DepthAttach
};

class FrameBuffer
{
public:
	static inline FrameBufferPtr Make(TexturePtr tex, AttachmentType texType);
	~FrameBuffer();

	void Activate();
	void Deactivate();
private:
	unsigned int id;
	unsigned int width;
	unsigned int height;
	AttachmentType type;

	FrameBuffer(TexturePtr tex, AttachmentType texType);
};

inline FrameBufferPtr FrameBuffer::Make(TexturePtr tex, AttachmentType texType)
{
	return FrameBufferPtr(new FrameBuffer(tex, texType));
}