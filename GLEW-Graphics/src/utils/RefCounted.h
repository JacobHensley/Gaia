#pragma once
#include "utils/Common.h"

template<typename T>
class Ref
{
private:
	T* m_Obj;
public:

	Ref()
		: m_Obj(nullptr) 
	{
		Set(nullptr);
	}

	Ref(T* obj)
		: m_Obj(nullptr) 
	{
		Set(obj);
	}

	Ref(const Ref& other)
		: m_Obj(nullptr) 
	{
		this->operator=(other);
	}

	Ref& operator=(const Ref& other)
	{
		Set(other.Get());
		return *this;
	}

	operator T*() { return m_Obj; }
	operator const T*() const { return m_Obj; }

	~Ref()
	{
		Set(nullptr);
	}

	T* Get() const
	{
		return m_Obj;
	}

	void Set(T* obj)
	{
		if (obj)
			obj->Increment();
		if (m_Obj)
			m_Obj->Decrement();
		m_Obj = obj;
	}

	T* operator->()
	{
		return m_Obj;
	}

	const T* operator->() const
	{
		return m_Obj;
	}

	T& operator *()
	{
		return *m_Obj;
	}

	const T& operator *() const
	{
		return *m_Obj;
	}

	bool operator==(const Ref<T>& other) const
	{
		return m_Obj == other.m_Obj;
	}
};

class RefCounted {
private:
	mutable uint m_ReferenceCount;
public:
	RefCounted() : m_ReferenceCount(0) {}

	virtual ~RefCounted()
	{
	}

	void Increment() const
	{
		m_ReferenceCount++;
	}

	void Decrement() const
	{
		m_ReferenceCount--;
		if (m_ReferenceCount == 0) 
			delete this;
	}
};
