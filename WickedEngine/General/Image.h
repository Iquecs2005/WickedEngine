#include <memory>

class Image;
using ImagePtr = std::shared_ptr<Image>;

#pragma once

#include <string>

class Image
{
public:
	static ImagePtr Make(const std::string& fileName);

	inline int GetWidth() const;
	inline int GetHeight() const;
	inline int GetNChannels() const;
	inline const unsigned char* GetData() const;
protected:
	Image(const std::string& fileName);
private:
	int width;
	int height;
	int nChannels;
	unsigned char* imageData;
};

inline int Image::GetWidth() const
{
	return width;
}

inline int Image::GetHeight() const
{
	return height;
}

inline int Image::GetNChannels() const
{
	return nChannels;
}

inline const unsigned char* Image::GetData() const
{
	return imageData;
}