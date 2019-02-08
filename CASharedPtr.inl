/*=============================================================================
Copyright © Cummins-Allison Corp. 2012, All rights reserved.

File: CASharedPtr.cpp

Description:
	This class provides an RAII object for managing pointers allocated with new.
	CASharedPtr is modeled after the C++11 shared_ptr.
===============================================================================*/
#include <stdexcept>
#include <iostream>

template<class Elem>
std::map<Elem*, unsigned int> CASharedPtr<Elem>::m_referenceCountMap;

template<class Elem>
CASharedPtr<Elem>::CASharedPtr()
:m_pElem(NULL)
{
}

/*------------------------------------------------------------------------------
Constructor

Description:
	This sets the internal pointer value to the given parameter value and sets 
	the reference count associated with the given pointer appropriately.
-------------------------------------------------------------------------------*/
template<class Elem>
CASharedPtr<Elem>::CASharedPtr(Elem* pElem)
:m_pElem(pElem)
{
	if(!pElem)
	{
		return;
	}
	std::map<Elem*, unsigned int>::iterator it = m_referenceCountMap.find(m_pElem);
	if(it!=m_referenceCountMap.end())
	{
		if(it->second>=1)
		{
			it->second++;
			//std::cout << it->second << " references to " << it->first 
				//<< " map ptr: " << &m_referenceCountMap << std::endl;
		}
		else
		{
			std::cerr << "CASharedPtr::ctor ERR: reference count is less than 1.";
		}
	}
	else
	{
		m_referenceCountMap.insert(std::pair<Elem*,unsigned int>(m_pElem,1));
	}
}

/*------------------------------------------------------------------------------
Copy Constructor

Description:
	Since shared_ptr objects share ownership of the pointer they point to, when a 
	new shared_ptr is constructed from another shared_ptr, the reference count 
	for that object is incremented when a copy constructor is called.
-------------------------------------------------------------------------------*/
template<class Elem>
CASharedPtr<Elem>::CASharedPtr(const CASharedPtr& rhs)
:m_pElem(rhs.get())
{
	if(!m_pElem)
	{
		return;
	}
	std::map<Elem*, unsigned int>::iterator it = m_referenceCountMap.find(m_pElem);
	if(it!=m_referenceCountMap.end())
	{
		if(it->second>=1)
		{
			it->second++;
			//std::cout << it->second << " references to " << it->first 
				//<< " map ptr: " << &m_referenceCountMap << std::endl;
		}
		else
		{
			std::cerr << "CASharedPtr::cpyctor ERR: reference count is less than 1.";
		}
	}
	else
	{
		std::cerr << "CASharedPtr::cpyctor ERR: Elem* not found in map when expected.";
	}
}

/*------------------------------------------------------------------------------
Destructor

Description:
	destructs the currently pointed to object if no other shared pointers are 
	referencing the pointed to object. 
-------------------------------------------------------------------------------*/
template<class Elem>
CASharedPtr<Elem>::~CASharedPtr()
{
	reset();
}

/*------------------------------------------------------------------------------
Method: get

Description:
	Simple getter method to expose the internally held resource pointer if it is
	so needed.

Returns:
	a copy of the internally stored variable
-------------------------------------------------------------------------------*/
template<class Elem>
Elem* CASharedPtr<Elem>::get() const
{
	return m_pElem;
}

/*------------------------------------------------------------------------------
Method: operator*

Description:
	This is a simple dereference operator overload to make using this RAII 
	object more simple and intuitive.

Returns:
	a reference to the object we are currently pointing to.
-------------------------------------------------------------------------------*/
template<class Elem>
Elem& CASharedPtr<Elem>::operator*() const
{
	return *m_pElem;
}

/*------------------------------------------------------------------------------
Method: operator->

Description:
	A simple operator overload to make using this RAII object more simple and
	intuitive.

Returns:
	A copy of our internally held pointer.
-------------------------------------------------------------------------------*/
template<class Elem>
Elem* CASharedPtr<Elem>::operator->() const
{
	return m_pElem;
}

/*------------------------------------------------------------------------------
Method: copy assignment operator

Description:
	Copies the value of the pointer held by the given parameter.

	The object on the left-hand side shares ownership of the pointer with the 
	rhs shared pointer.

	If the lhs shared pointer previously pointed to any resource, it is 
	relieved of that responsibility and the previously pointed to item is 
	destroyed if no other shared pointers refer to it.

Returns:
	N/A
-------------------------------------------------------------------------------*/
template<class Elem>
void CASharedPtr<Elem>::operator=(const CASharedPtr& rhs)
{
	if(&rhs == this)
	{
		return;
	}
	//take care of any currently pointed to resources
	if(m_pElem)
	{
		reset();
	}
	//share resource with parameter
	std::map<Elem*, unsigned int>::iterator it = m_referenceCountMap.find(rhs.get());
	if(it!=m_referenceCountMap.end())
	{
		if(it->second>=1)
		{
			m_pElem = it->first;
			it->second++;
			//std::cout << it->second << " references to " << it->first 
				//<< " map ptr: " << &m_referenceCountMap << std::endl;
		}
		else
		{
			std::cerr << "CASharedPtr::copy assignment operator ERR: reference count is less than 1.";
		}
	}
	else
	{
		std::cerr << "CASharedPtr::copy assignment operator ERR: Elem* not found in map when expected.";
	}
}

template<class Elem>
void CASharedPtr<Elem>::operator=(Elem* pElem)
{
	reset(pElem);
}

/*------------------------------------------------------------------------------
Method: reset

Description:
	Destructs the object pointed by the shared pointer object if this shared 
	pointer is the last reference. Otherwise, the reference count variable is 
	simply decremented for that poitner value. If a value for rhs is specified, 
	the internal pointer is initialized to that value (otherwise it is set to 
	the null pointer).

	To only release the ownership of a pointer without destructing the object 
	pointed by it, use member function release instead.

Returns:
	N/A
-------------------------------------------------------------------------------*/
template<class Elem>
void CASharedPtr<Elem>::reset(Elem* pElem)
{
	//if lhs is NULL and we want to set to NULL, there is nothing to do.
	if(!m_pElem && !pElem)
	{
		return;
	}
	//delete or decrement lhs reference count if exists
	if(m_pElem)
	{
		std::map<Elem*, unsigned int>::iterator it = m_referenceCountMap.find(m_pElem);
		if(it!=m_referenceCountMap.end())
		{
			if(it->second>1)
			{
				it->second--;
				//std::cout << it->second << " references to " << it->first  
				//<< " map ptr: " << &m_referenceCountMap << std::endl;
			}
			else if(it->second==1)
			{
				//std::cout << "deleting element " << it->first  
				//<< " map ptr: " << &m_referenceCountMap << std::endl;
				m_referenceCountMap.erase(it);
				delete m_pElem;
			}
			else
			{
				std::cerr << "CASharedPtr::reset ERR: reference count is less than 1.";
			}
		}
		else
		{
			std::cerr << "CASharedPtr::reset ERR: Elem* not found in map when expected.";
		}
	}
	m_pElem = pElem;
	//insert new value into map if exists
	if(pElem)
	{
		std::pair<std::map<Elem*,unsigned int>::iterator ,bool> in;
		in = m_referenceCountMap.insert(std::pair<Elem*,unsigned int>(pElem,1));
		//if an entry for this object already exists, simply increment the reference count
		if(!in.second)
		{
			in.first->second++;
			//std::cout << "1 reference to " << in.first->first
				//<< " map ptr: " << &m_referenceCountMap << std::endl;
		}
	}
}

/*------------------------------------------------------------------------------
Method: release

Description:
	Sets the shared pointer internal pointer to null pointer (which indicates it 
	points to no object) without destructing the object currently pointed by 
	the auto_ptr. Also updates the internal pointer map appropriately.

	To force a destruction of the object pointed, use member function reset() 
	instead.

Returns:
	The function returns a pointer to the object it pointed before the call, 
	which is no longer its responsibility to destruct.
-------------------------------------------------------------------------------*/
template<class Elem>
Elem* CASharedPtr<Elem>::release()
{
	if(!m_pElem)
	{
		return NULL;
	}
	std::map<Elem*, unsigned int>::iterator it = m_referenceCountMap.find(m_pElem);
	if(it!=m_referenceCountMap.end())
	{
		if(it->second>1)
		{
			it->second--;
			//std::cout << it->second << " references to " << it->first  
				//<< " map ptr: " << &m_referenceCountMap << std::endl;
		}
		else if(it->second==1)
		{
			m_referenceCountMap.erase(it);
		}
		else
		{
			std::cerr << "CASharedPtr::release ERR: reference count is less than 1.";
		}
	}
	else
	{
		std::cerr << "CASharedPtr::release ERR: Elem* not found in map when expected.";
	}
	Elem* temp = m_pElem;
	m_pElem = NULL;
	return temp;
}
