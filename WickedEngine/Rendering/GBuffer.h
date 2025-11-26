#include <memory>

class GBuffer;
using GBufferPtr = std::shared_ptr<GBuffer>;

#pragma once

#include "FrameBuffer.h"

#include "DepthTexture.h"
#include "CustomTexture.h"
#include "shader.h"

class GBuffer : public FrameBuffer
{
public:
	~GBuffer();

	static inline GBufferPtr Make(int width, int height);

	void LoadTextures(ShaderPtr shader);
	void UnloadTextures(ShaderPtr shader);
protected:
	GBuffer(int width, int height);
};

inline GBufferPtr GBuffer::Make(int width, int height)
{
	return GBufferPtr(new GBuffer(width, height));
}
