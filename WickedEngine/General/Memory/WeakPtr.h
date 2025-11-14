#pragma once

#include "UniquePtr.h"

template<typename WeakContentType>
class WeakPtr
{
public:
	inline WeakPtr();
	inline WeakPtr(const UniquePtr<WeakContentType>& base);
	inline ~WeakPtr();

	inline bool IsExpired();

	//inline WeakPtr<WeakContentType>& operator=(const WeakPtr<WeakContentType>& weakPtr);
	//inline WeakPtr<WeakContentType>& operator=(const UniquePtr<WeakContentType>& uniquePtr);
	inline WeakContentType& operator*() const;
	inline WeakContentType* operator->() const;
private:
	UniquePtr<WeakContentType>* const ref;
	WeakContentType* ptr;

	void OnPtrDelete();
	void OnPtrMove(UniquePtr<WeakContentType> newOwner);
	inline void ExpiredExceptionChecker() const;
};

template<typename WeakContentType>
inline WeakPtr<WeakContentType>::WeakPtr()
{
	ptr = nullptr;
	ref = nullptr;
}

template<typename WeakContentType> 
inline WeakPtr<WeakContentType>::WeakPtr(const UniquePtr<WeakContentType>& base)
{
	ptr = base.ptr;
	ref = &base;
	base.OnDestruction.AddListener(OnPtrDelete);
	base.OnNewOwner.AddListener();
}

template<typename WeakContentType>
inline WeakPtr<WeakContentType>::~WeakPtr()
{
	if (ref != nullptr)
	{
		ref->OnDestruction.RemoveListener(OnPtrDelete);
		ref->OnNewOwner.RemoveListener(OnPtrMove);
	}
}

template<typename WeakContentType>
inline bool WeakPtr<WeakContentType>::IsExpired()
{
	return ptr == nullptr;
}

template<typename WeakContentType>
inline WeakContentType& WeakPtr<WeakContentType>::operator*() const
{
	ExpiredExceptionChecker();
	return *ptr;
}

template<typename WeakContentType>
inline WeakContentType* WeakPtr<WeakContentType>::operator->() const
{
	ExpiredExceptionChecker();
	return ptr;
}

template<typename WeakContentType>
void WeakPtr<WeakContentType>::OnPtrDelete()
{
	ptr = nullptr;
}

template<typename WeakContentType>
void WeakPtr<WeakContentType>::OnPtrMove(UniquePtr<WeakContentType> newOwner)
{
	if (ref != nullptr)
		ref->OnDestruction.RemoveListener(OnPtrDelete);
	ref = newOwner;
}

template<typename WeakContentType>
inline void WeakPtr<WeakContentType>::ExpiredExceptionChecker() const
{
	if (IsExpired())
		throw std::runtime_error("WeakPtr Null Pointer exception\n");
}