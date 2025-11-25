#include <memory>

class FrameBuffer;
using FrameBufferPtr = std::shared_ptr<FrameBuffer>;

#pragma once

#include <initializer_list>

#include "DepthTexture.h"
#include "Texture.h"

enum AttachmentType
{
	ColorAttach, DepthAttach
};

class FrameBuffer
{
public:
	static inline FrameBufferPtr Make(int width, int height,
									  DepthTexturePtr depthTex,
									  std::initializer_list<TexturePtr> colorTextures = {});
	~FrameBuffer();

	void Activate();
	void Deactivate();
private:
	unsigned int id;
	unsigned int width;
	unsigned int height;
	DepthTexturePtr depthTex;
	std::vector<TexturePtr> colorTextures;

	FrameBuffer(int width, int height, DepthTexturePtr depthTex, std::initializer_list<TexturePtr> colorTextures);
};

inline FrameBufferPtr FrameBuffer::Make(int width, int height,
										DepthTexturePtr depthTex,
										std::initializer_list<TexturePtr> colorTextures)
{
	return FrameBufferPtr(new FrameBuffer(width, height, depthTex, colorTextures));
}