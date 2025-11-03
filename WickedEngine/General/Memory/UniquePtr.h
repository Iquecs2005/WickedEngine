#pragma once

#include <iostream>
#include <stdexcept>

template<typename ContentType>
class UniquePtr
{
public:
	UniquePtr();
	UniquePtr(ContentType* ptr);
	UniquePtr(ContentType value);
	UniquePtr(const UniquePtr<ContentType>&) = delete;
	~UniquePtr();

	inline bool IsExpired() const;
	
	//inline ContentType& operator=(const S) const;
	inline ContentType& operator*() const;
	inline ContentType* operator->() const;
private:
	inline void ExpiredExceptionChecker() const;

	ContentType* ptr;
};

template<typename ContentType>
UniquePtr<ContentType>::UniquePtr()
{
	ptr = new ContentType();
}

template<typename ContentType>
UniquePtr<ContentType>::UniquePtr(ContentType* ptr)
{
	this->ptr = ptr;
}

template<typename ContentType>
UniquePtr<ContentType>::UniquePtr(ContentType value)
{
	ptr = new ContentType();
	*ptr = value;
}

template<typename ContentType>
UniquePtr<ContentType>::~UniquePtr()
{
	if (!IsExpired())
		delete ptr;
	std::cout << "Deleting pointer" << std::endl;
}

template<typename ContentType>
inline bool UniquePtr<ContentType>::IsExpired() const
{
	return ptr == nullptr;
}

template<typename ContentType>
inline void UniquePtr<ContentType>::ExpiredExceptionChecker() const
{
	if (IsExpired())
		throw std::runtime_error("Null Pointer exception\n");
}

template<typename ContentType>
inline ContentType& UniquePtr<ContentType>::operator*() const
{
	ExpiredExceptionChecker();
	return *ptr;
}

template<typename ContentType>
inline ContentType* UniquePtr<ContentType>::operator->() const
{
	ExpiredExceptionChecker();
	return ptr;
}
