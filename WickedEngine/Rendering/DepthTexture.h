#include <memory>

class DepthTexture;
using DepthTexturePtr = std::shared_ptr<DepthTexture>;

#pragma once

#include <string>

#include "BaseTexture.h"

class DepthTexture : public BaseTexture
{
public:
	static inline DepthTexturePtr Make(const std::string& name, unsigned int width, unsigned int height);
	void SetCompareMode();
protected:
	DepthTexture(const std::string& name, unsigned int width, unsigned int height);
};

inline DepthTexturePtr DepthTexture::Make(const std::string& name, unsigned int width, unsigned int height)
{
	return DepthTexturePtr(new DepthTexture(name, width, height));
}

