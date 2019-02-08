/*=============================================================================
File: ChildListIterator.inl

Description:
	This file provides the class definitions for Node.h without cluttering the
	file.
===============================================================================*/

#include <assert.h>

template<class Elem>
Node<Elem>::ChildListIterator::ChildListIterator(Node& rParentNode, const std::wstring& findKey)
		:m_findKey(findKey),
		 m_pList(&rParentNode.m_childList)
{
	m_Iter = m_pList->begin();
	//if(m_pList->size() > 0)
	//{
	//	m_Iter = m_pList->begin();
	//}
	//else
	//{
	//	throw std::exception(std::length_error("Can not create a ChildListIterator for a node with no children."));
	//}
	initialize(findKey);
}

template<class Elem>
Node<Elem>::ChildListIterator::ChildListIterator(Node& rParentNode, typename const std::vector<Node*>::iterator& it)
		:m_findKey(L""),
		 m_pList(&rParentNode.m_childList)
{
	m_Iter = it;
	initialize(m_findKey);
}

template<class Elem>
void Node<Elem>::ChildListIterator::initialize(const std::wstring& findKey)
{
	if(findKey!=L"")
	{
		while(m_Iter!=m_pList->end() && (*m_Iter)->getKey()!=findKey)
		{
			m_Iter++;
		}
		//m_FindIter = m_Iter;
	}
	//else
	//{
	//	m_FindIter = m_pList->end();
	//}
}

/*------------------------------------------------------------------------------
Method: First

Description:
	Getter function that returns the first item in the list this iterator 
	points to.
-------------------------------------------------------------------------------*/
//template<class Elem> 
//typename Node<Elem>::ChildListIterator* Node<Elem>::ChildListIterator::begin() const
//{
//	assert(m_pList);
//	if(m_findKey==L"")
//	{
//		m_Iter = m_pList->begin();
//	}
//	//else
//	//{
//	//	m_Iter = m_FindIter;
//	//}
//	return this;
//}
/*------------------------------------------------------------------------------
Method: increment overload

Description:
	Getter function that returns the item following the currently pointed to 
	object in the list for this iterator.
-------------------------------------------------------------------------------*/
template<class Elem>
typename Node<Elem>::ChildListIterator* Node<Elem>::ChildListIterator::operator++()
{
	assert(m_pList);
	//if(&m_Iter == NULL)
	//{
	//	m_Iter = m_pList->begin();
	//}
	while(m_Iter != m_pList->end())
	{
		++m_Iter;
		if(m_Iter==m_pList->end())
		{
			return NULL;
		}
		else if(m_findKey==L"" || (*m_Iter)->getKey()==m_findKey)
		{
			return this;
		}
	}
	return NULL;
}

/*------------------------------------------------------------------------------
Method: decrement overload

Description:
	Getter function that returns the item preceeding the currently pointed to 
	object in the list for this iterator.
-------------------------------------------------------------------------------*/
template<class Elem>
typename Node<Elem>::ChildListIterator* Node<Elem>::ChildListIterator::operator--()
{
	assert(m_pList);
	while(m_Iter != m_pList->begin())
	{
		--m_Iter;
		if(m_findKey==L"" || (*m_Iter)->getKey()==m_findKey)
		{
			return this;
		}
	}
	return NULL;
}

/*------------------------------------------------------------------------------
Method: dereference operator

Description:
	Returns the item in the list that this iterator is currently pointing to.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>& Node<Elem>::ChildListIterator::operator*() const
{
	return **m_Iter;
}

/*------------------------------------------------------------------------------
Method: operator->

Description:
	Returns the item in the list that this iterator is currently pointing to.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>* Node<Elem>::ChildListIterator::operator->() const
{
	assert(m_pList);
	if(m_Iter == m_pList->end())
	{
		return NULL;
	}
	else  
	{
		return *m_Iter;
	}
}

template<class Elem>
bool Node<Elem>::ChildListIterator::operator!=(const ChildListIterator& rhs) const
{
	return !(operator==(rhs));
}

template<class Elem>
bool Node<Elem>::ChildListIterator::operator==(const ChildListIterator& rhs) const
{
	if (m_pList == rhs.m_pList && 
		m_Iter == rhs.m_Iter)// && 
		//m_FindIter == rhs.m_FindIter)
	{
		return true;
	}
	else
	{
		return false;
	}
}
