/*=============================================================================
File: CASharedPtr.h

Description:
	This class provides an RAII object for managing pointers allocated with new.
	A shared pointer keeps a reference count of how many references are made to 
	the interal pointer and only deallocates the pointer when the number of 
	references reaches zero.
===============================================================================*/
#pragma once;

#include <map>

template<class Elem>
class CASharedPtr
{
public:
	CASharedPtr();
	explicit CASharedPtr(Elem* pElem);
	CASharedPtr(const CASharedPtr& rhs);
	~CASharedPtr();

	Elem* get() const;
	Elem& operator*() const;
	Elem* operator->() const;
	void operator=(const CASharedPtr& rhs);
	void operator=(Elem* rhs);
	void reset(Elem* rhs = NULL);
	Elem* release();
	operator bool() const {return m_pElem!=NULL;}

private:
	Elem* m_pElem;
	static std::map<Elem*,unsigned int> m_referenceCountMap;
};

#include "CASharedPtr.inl"
