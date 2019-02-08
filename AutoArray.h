/*=============================================================================
File: AutoArray.h

Description:
	This class provides a way to store objects that are deallocated with 
	delete[] in an RAII object. This class is implemented using the C++ 
	auto_ptr as a model. 
===============================================================================*/
#pragma once;

template<class Elem>
class AutoArray
{
public:
	AutoArray();
	explicit AutoArray(Elem* pElem, int length);
	AutoArray(AutoArray& rAutoArray);
	//AutoArray(int size);
	~AutoArray();

	Elem* get();
	Elem& operator*();
	Elem* operator->();
	void operator=(AutoArray& rhs);
	Elem& operator[](int rhs);
	void reset(Elem* rhs = NULL);
	Elem* release();
	operator bool() { return !m_pElem==NULL; }
   int length(){return m_length;}

private:
   void operator=(Elem* rhs){};
	Elem* m_pElem;
   int m_length;
};

#include "AutoArray.inl"
