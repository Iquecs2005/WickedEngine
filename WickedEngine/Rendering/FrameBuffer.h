#include <memory>

class FrameBuffer;
using FrameBufferPtr = std::shared_ptr<FrameBuffer>;

#pragma once

#include <initializer_list>

#include "DepthTexture.h"
#include "Texture.h"

class FrameBuffer
{
public:
	static inline FrameBufferPtr Make(int width, int height,
									  DepthTexturePtr depthTex,
									  std::initializer_list<BaseTexturePtr> colorTextures = {});
	~FrameBuffer();

	void Activate();
	void Deactivate();
protected:
	unsigned int id = 0;
	unsigned int width;
	unsigned int height;
	DepthTexturePtr depthTex;
	std::vector<BaseTexturePtr> colorTextures;
	
	FrameBuffer(int width, int height);
	FrameBuffer(int width, int height, DepthTexturePtr depthTex, std::initializer_list<BaseTexturePtr> colorTextures);
	void GenFrameBuffer();
	void GenFrameBuffer(int width, int height, DepthTexturePtr depthTex, std::initializer_list<BaseTexturePtr> colorTextures);
};

inline FrameBufferPtr FrameBuffer::Make(int width, int height,
										DepthTexturePtr depthTex,
										std::initializer_list<BaseTexturePtr> colorTextures)
{
	return FrameBufferPtr(new FrameBuffer(width, height, depthTex, colorTextures));
}