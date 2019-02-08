/*=============================================================================
File: DFSIteratorConst.inl

Description:
	This file provides the class definitions for Node.h without cluttering the
	file.
===============================================================================*/

#include <assert.h>

/*------------------------------------------------------------------------------
Constructor: DFSIteratorConst

Description:
	Instantiates the member variables of this object.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>::DFSIteratorConst::DFSIteratorConst()
: m_pDFSIterator(NULL)
{
}
template<class Elem>
Node<Elem>::DFSIteratorConst::DFSIteratorConst(Node<Elem>& rRootNode)
:m_pDFSIterator(new Node<Elem>::DFSIterator(rRootNode))
{
}

template<class Elem>
Node<Elem>::DFSIteratorConst::DFSIteratorConst(const DFSIteratorConst& rDFSIteratorConst)
:m_pDFSIterator(new Node<Elem>::DFSIterator(rDFSIteratorConst))
{
}

template<class Elem>
Node<Elem>::DFSIteratorConst::DFSIteratorConst(const DFSIterator& rDFSIterator)
:m_pDFSIterator(new Node<Elem>::DFSIterator(rDFSIterator))
{
}

/*------------------------------------------------------------------------------
Destructor: ~DFSIteratorConst

Description:
	Deletes the map items created during the traversal.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>::DFSIteratorConst::~DFSIteratorConst()
{
	if(m_pDFSIterator != NULL)
	{
		delete m_pDFSIterator;
		m_pDFSIterator = NULL;
	}
}


/*------------------------------------------------------------------------------
Method: Next

Description:
	Returns the next item in the list that this iterator is pointing to.
-------------------------------------------------------------------------------*/
template<class Elem>
typename Node<Elem>::DFSIteratorConst* Node<Elem>::DFSIteratorConst::operator++()
{
	++(*m_pDFSIterator);
	return this;
}

/*------------------------------------------------------------------------------
Method: currentItem

Description:
	Returns the item currently pointed to by the iterator.
-------------------------------------------------------------------------------*/
template<class Elem>
const Node<Elem>& Node<Elem>::DFSIteratorConst::operator*() const
{
	//return const_cast<const Item&>(**m_pDFSIterator);
	return **m_pDFSIterator;
}

/*------------------------------------------------------------------------------
Method: operator->

Description:
	Returns the item currently pointed to by the iterator.
-------------------------------------------------------------------------------*/
template<class Elem>
const Node<Elem>* Node<Elem>::DFSIteratorConst::operator->() const
{
	//return const_cast<const Item*>(&**m_pDFSIterator);
	return &**m_pDFSIterator;
}
template<class Elem>
bool Node<Elem>::DFSIteratorConst::operator==(const DFSIteratorConst& rhs) const
{
	if( (*m_pDFSIterator) == (*rhs.m_pDFSIterator) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
template<class Elem>
bool Node<Elem>::DFSIteratorConst::operator==(const DFSIterator& rhs) const
{
	if( (*m_pDFSIterator) == (rhs) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class Elem>
bool Node<Elem>::DFSIteratorConst::operator!=(const DFSIteratorConst& rhs) const
{
	return !(operator==(rhs));
}

template<class Elem>
bool Node<Elem>::DFSIteratorConst::operator!=(const DFSIterator& rhs) const
{
	return !(operator==(rhs));
}

template<class Elem>
typename Node<Elem>::DFSIteratorConst& Node<Elem>::DFSIteratorConst::operator=(const DFSIteratorConst& rhs)
{
	if(this == &rhs)
	{
		return *this;
	}
	if(m_pDFSIterator != NULL)
	{
		delete m_pDFSIterator;
		m_pDFSIterator = NULL;
	}
	m_pDFSIterator = new Node<Elem>::DFSIterator(rhs);

	return *this;
}

template<class Elem>
typename Node<Elem>::DFSIteratorConst& Node<Elem>::DFSIteratorConst::operator=(const DFSIterator& rhs)
{
	if(m_pDFSIterator == &rhs)
	{
		return *this;
	}
	if(m_pDFSIterator != NULL)
	{
		delete m_pDFSIterator;
		m_pDFSIterator = NULL;
	}
	m_pDFSIterator = new Node<Elem>::DFSIterator(*rhs);

	return *this;
}

