#pragma once

#include <iostream>
#include <stdexcept>

#include "../Event.h"

template<typename UniqueContentType>
class UniquePtr
{
public:
	Event<> OnDestruction;
	Event<UniquePtr<UniqueContentType>> OnNewOwner;

	UniquePtr();
	UniquePtr(UniqueContentType* ptr);
	UniquePtr(UniqueContentType value);
	UniquePtr(const UniquePtr<UniqueContentType>&) = delete;
	~UniquePtr();

	inline bool IsExpired() const;
	inline UniquePtr MoveOwner();

	//inline ContentType& operator=(const S) const;
	inline UniqueContentType& operator*() const;
	inline UniqueContentType* operator->() const;

private:
	UniqueContentType* ptr;

	inline void ExpiredExceptionChecker() const;

	template<typename ContentType>
	friend class WeakPtr;
};

template<typename UniqueContentType>
UniquePtr<UniqueContentType>::UniquePtr()
{
	ptr = new UniqueContentType();
}

template<typename UniqueContentType>
UniquePtr<UniqueContentType>::UniquePtr(UniqueContentType* ptr)
{
	this->ptr = ptr;
}

template<typename UniqueContentType>
UniquePtr<UniqueContentType>::UniquePtr(UniqueContentType value)
{
	ptr = new UniqueContentType();
	*ptr = value;
}

template<typename UniqueContentType>
UniquePtr<UniqueContentType>::~UniquePtr()
{
	OnDestruction.Invoke();
	if (!IsExpired())
		delete ptr;
	std::cout << "Deleting pointer" << std::endl;
}

template<typename UniqueContentType>
inline bool UniquePtr<UniqueContentType>::IsExpired() const
{
	return ptr == nullptr;
}

template<typename UniqueContentType>
inline UniquePtr<UniqueContentType> UniquePtr<UniqueContentType>::MoveOwner()
{
	UniquePtr<UniqueContentType> newUnique = UniquePtr<UniqueContentType>(ptr);
	ptr = nullptr;
	OnNewOwner.Invoke(newUnique);
	return newUnique;
}

template<typename UniqueContentType>
inline void UniquePtr<UniqueContentType>::ExpiredExceptionChecker() const
{
	if (IsExpired())
		throw std::runtime_error("UniquePtr Null Pointer exception\n");
}

template<typename UniqueContentType>
inline UniqueContentType& UniquePtr<UniqueContentType>::operator*() const
{
	ExpiredExceptionChecker();
	return *ptr;
}

template<typename UniqueContentType>
inline UniqueContentType* UniquePtr<UniqueContentType>::operator->() const
{
	ExpiredExceptionChecker();
	return ptr;
}
