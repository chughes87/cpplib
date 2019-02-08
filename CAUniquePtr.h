/*=============================================================================
File: CAUniquePtr.h

Description:
	This class provides a way to store objects that are deallocated with 
	delete in an RAII object. This class is implemented using the C++ 
	auto_ptr as a model. 
===============================================================================*/
#pragma once;

template<class Elem>
class CAUniquePtr
{
public:
	CAUniquePtr();
	explicit CAUniquePtr(Elem* pElem);
	CAUniquePtr(CAUniquePtr& rCAUniquePtr);
	~CAUniquePtr();

	Elem* get();
	Elem& operator*();
	Elem* operator->();
	void operator=(CAUniquePtr& rhs);
	void operator=(Elem* rhs);
	void reset(Elem* rhs = NULL);
	Elem* release();
	operator bool() { return !m_pElem==NULL; }

private:
	Elem* m_pElem;
};

#include "CAUniquePtr.inl"
