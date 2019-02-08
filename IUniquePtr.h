/*=============================================================================
File: IUniquePtr.h

Description:
	This class provides a way to store objects that are deallocated with 
	Release() in an RAII object. This class is implemented using the C++ 
	auto_ptr as a model. 
===============================================================================*/
#pragma once;

template<class Elem>
class IUniquePtr
{
public:
	IUniquePtr();
	explicit IUniquePtr(Elem* pElem);
	IUniquePtr(IUniquePtr& rIUniquePtr);
	~IUniquePtr();

	Elem* get();
	Elem& operator*();
	Elem* operator->();
	void operator=(IUniquePtr& rhs);
	void operator=(Elem* rhs);
	void reset(Elem* rhs = NULL);
	Elem* release();
	operator bool() { return !m_pElem==NULL; }

private:
	Elem* m_pElem;
};

#include "IUniquePtr.inl"
