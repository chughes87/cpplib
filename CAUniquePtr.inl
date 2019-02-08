/*=============================================================================
File: CAUniquePtr.inl

Description:
	This class provides a way to store objects that are deallocated with 
	release() in an RAII object. This class is implemented using the C++11 
	unique_ptr as a model. 
===============================================================================*/

/*------------------------------------------------------------------------------
Constructor

Description:
	This sets the internal pointer value to the given parameter value.
-------------------------------------------------------------------------------*/
template<class Elem>
CAUniquePtr<Elem>::CAUniquePtr()
:m_pElem(NULL)
{
}

/*------------------------------------------------------------------------------
Constructor

Description:
	This sets the internal pointer value to the given parameter value.
-------------------------------------------------------------------------------*/
template<class Elem>
CAUniquePtr<Elem>::CAUniquePtr(Elem* pElem)
:m_pElem(pElem)
{
}

/*------------------------------------------------------------------------------
Copy Constructor

Description:
	Since unique pointer objects take ownership of the pointer they point to, 
	when a new unique ptr is constructed from another unique ptr, the former 
	owner releases it.
-------------------------------------------------------------------------------*/
template<class Elem>
CAUniquePtr<Elem>::CAUniquePtr(CAUniquePtr& rCAUniquePtr)
{
	m_pElem = rCAUniquePtr.release();
}

/*------------------------------------------------------------------------------
Destructor

Description:
	Calls release() on the currently pointed to object. This will not work for 
	objects that have their deallocator defined as Release(). (I so wish that
	Microsoft would stick to naming standards...)
-------------------------------------------------------------------------------*/
template<class Elem>
CAUniquePtr<Elem>::~CAUniquePtr()
{
	if(m_pElem)
	{
		delete m_pElem;
	}
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
Elem* CAUniquePtr<Elem>::get()
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
Elem& CAUniquePtr<Elem>::operator*()
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
Elem* CAUniquePtr<Elem>::operator->()
{
	return m_pElem;
}

/*------------------------------------------------------------------------------
Method: copy assignment operator

Description:
	Copies the value of the pointer held by the given parameter.

	The object on the left-hand side takes ownership of the pointer (i.e., it 
	is now in charge of freeing the memory block when destroyed). Therefore, 
	the unique pointer object on the right-hand side is automatically released 
	(i.e., it is set to point to null) after the copy.

	If the (left-hand side) object was being used to point to an object before the 
	operation, the pointed object is destroyed (by calling operator delete).

Returns:
	N/A
-------------------------------------------------------------------------------*/
template<class Elem>
void CAUniquePtr<Elem>::operator=(CAUniquePtr& rhs)
{
	if(&rhs == this)
	{
		return;
	}
	this->reset(rhs.get());
	rhs.release();
}

template<class Elem>
void CAUniquePtr<Elem>::operator=(Elem* rhs)
{
	this->reset(rhs);
}

/*------------------------------------------------------------------------------
Method: reset

Description:
	Destructs the object pointed by the unique pointer object, if any, and 
	deallocates its memory. If a value for rhs is specified, the internal 
   pointer is initialized to that value (otherwise it is set to null).

	To only release the ownership of a pointer without destructing the object 
	pointed by it, use member function release instead.

Returns:
	N/A
-------------------------------------------------------------------------------*/
template<class Elem>
void CAUniquePtr<Elem>::reset(Elem* rhs)
{
	if(m_pElem)
	{
      delete m_pElem;
	}
	m_pElem = rhs;
}

/*------------------------------------------------------------------------------
Method: release

Description:
	Sets the unique pointer internal pointer to null (which indicates that
	it points to no object) without destructing the object currently pointed by 
	the unique pointer.

	To force a destruction of the object pointed, use member function reset() 
	instead.

Returns:
	The function returns a pointer to the object it pointed before the call, 
	which is no longer its responsibility to destruct.
-------------------------------------------------------------------------------*/
template<class Elem>
Elem* CAUniquePtr<Elem>::release()
{
	Elem* temp = m_pElem;
	m_pElem = NULL;
	return temp;
}
