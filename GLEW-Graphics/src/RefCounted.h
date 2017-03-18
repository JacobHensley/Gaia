#pragma once
#include "Common.h"

template<typename T>
class Ref
{
private:
	T* m_Obj;
public:

	Ref()
		: m_Obj(nullptr) {
		Set(nullptr);
		std::cout << "Created Ref(" << this << "), Using Default Constructor" << std::endl;
	}

	Ref(T* obj)
		: m_Obj(nullptr) {
		Set(obj);
		std::cout << "Created Ref(" << this << "), Using Non-Default Constructor" << std::endl;
	}

	Ref(const Ref& other)
		: m_Obj(nullptr) {
		this->operator=(other);
	}

	Ref& operator=(const Ref& other)
	{
		Set(other.Get());
		return *this;
	}

	~Ref()
	{
		Set(nullptr);
		std::cout << "Destroyed Ref(" << this << ")" << std::endl;
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
		std::cout << "Incremented m_ReferenceCount for: " << this << ", m_ReferenceCount is now: " << m_ReferenceCount << std::endl;
	}

	void Decrement() const
	{
		m_ReferenceCount--;
		std::cout << "Decremented m_ReferenceCount for: " << this << ", m_ReferenceCount is now: " << m_ReferenceCount << std::endl;
		if (m_ReferenceCount == 0) 
			delete this;
	}
};
