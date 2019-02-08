/*=============================================================================
File: DFSIterator.inl

Description:
	This file provides the class definitions for Node.h without cluttering the
	file.
===============================================================================*/

#include <stdexcept>

/*------------------------------------------------------------------------------
Constructor: DFSIterator

Description:
	Instantiates the member variables of this object.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>::DFSIterator::DFSIterator()
		:m_pCurrentListIter(NULL),
		 m_pRootNode(NULL),
		 m_pCurrentNode(NULL)
{
}

template<class Elem>
Node<Elem>::DFSIterator::DFSIterator(Node& rRootNode)
		:m_pCurrentListIter(NULL),
		 m_pRootNode(&rRootNode),
		 m_pCurrentNode(&rRootNode)
{
}

template<class Elem>
Node<Elem>::DFSIterator::DFSIterator(const DFSIterator& rDFSIterator)
		:m_pCurrentListIter(NULL),
		 m_pRootNode(rDFSIterator.m_pRootNode),
		 m_pCurrentNode(rDFSIterator.m_pCurrentNode),
		 m_listMap(rDFSIterator.m_listMap)
{
}
//template<class Elem>
//Node<Elem>::DFSIterator::DFSIterator(Node& rRootNode)
//		:m_pCurrentListIter(ChildListIterator(rRootNode)), 
//		 m_pRootNode(&rRootNode),
//		 m_pCurrentNode(&rRootNode)
//{
//	m_listMap.insert( std::pair<Node<Elem>*, ChildListIterator*>
//						  (m_pCurrentNode, m_pCurrentListIter) );
//}
//
//template<class Elem>
//Node<Elem>::DFSIterator::DFSIterator(const DFSIterator& rDFSIterator)
//		:m_pCurrentListIter(ChildListIterator(*rDFSIterator)), 
//		 m_pRootNode(rDFSIterator.m_pRootNode),
//		 m_pCurrentNode(rDFSIterator.m_pRootNode)
//{
//	m_listMap.insert( std::pair<Node<Elem>*, ChildListIterator*>
//						  (m_pCurrentNode, m_pCurrentListIter) );
//}

/*------------------------------------------------------------------------------
Destructor: ~DFSIterator

Description:
	Deletes the map items created during the traversal.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>::DFSIterator::~DFSIterator()
{
}

//template<class Elem>
//void Node<Elem>::DFSIterator::clearListMap()
//{
//	if(m_listMap.size()>0)
//	{
//		std::map<Node*, ChildListIterator>::iterator it = m_listMap.begin();
//		for(; it != m_listMap.end(); it++)
//		{
//			ChildListIterator* pListIterator = it->second;
//			std::cout << "destroying:\t" << pListIterator << std::endl;
//			if(pListIterator != NULL)
//			{
//				delete pListIterator;
//				it->second = NULL;
//			}
//		}
//		m_listMap.clear();
//	}
//}

template<class Elem>
void Node<Elem>::DFSIterator::endTraversal()
{
	m_pCurrentNode = &endNode;
	//clearListMap();
	m_listMap.clear();
	m_pCurrentListIter = NULL;
}

/*------------------------------------------------------------------------------
Method: Next

Description:
	Returns the next item in the list that this iterator is pointing to.
-------------------------------------------------------------------------------*/
template<class Elem>
typename Node<Elem>::DFSIterator* Node<Elem>::DFSIterator::operator++()
{
	if(m_pCurrentNode == NULL || m_pRootNode == NULL)
	{
		return NULL;
	}

	bool success = false;

	success = traverseDown();
	if(success == true)
	{
		return this;
	}

	success = traverseUp();
	if(success == true)
	{
		operator++();
	}
	else
	{
		endTraversal();
		return &endNodeIter;
	}
}

template<class Elem>
bool Node<Elem>::DFSIterator::traverseDown()
{
	if(m_pCurrentNode->hasChild() == false)
	{
		return false;
	}
	if(m_pCurrentListIter == NULL)
	{
		initChildListIterator();
	}
	if((*m_pCurrentListIter) != m_pCurrentNode->lastChild())
	{
		m_pCurrentNode = &**m_pCurrentListIter;
		++(*m_pCurrentListIter);
		m_pCurrentListIter = NULL;
		return true;
	}
	else
	{
		return false;
	}
}

template<class Elem>
bool Node<Elem>::DFSIterator::traverseUp()
{
	if(m_pCurrentNode->m_pParentNode != NULL)
	{
		if(m_pCurrentListIter != NULL)
		{
			m_listMap.erase(m_listMap.find(m_pCurrentNode));
		}
		m_pCurrentNode = m_pCurrentNode->m_pParentNode;
		initChildListIterator();
		m_pCurrentListIter = &m_listMap.find(m_pCurrentNode)->second;
		return true;
	}
	else
	{
		return false;
	}
}

/*------------------------------------------------------------------------------
Method: initListIterator

Description:
	Helper method that creates a ChildListIterator for the given node
-------------------------------------------------------------------------------*/
template<class Elem>
void Node<Elem>::DFSIterator::initChildListIterator()
{
	if(m_pCurrentNode->hasChild() == false)
	{
		m_pCurrentListIter = NULL;
		throw std::logic_error("Can not create a ChildListIterator for a node with no children.");
	}
	std::map<Node<Elem>*, ChildListIterator>::iterator it = m_listMap.find(m_pCurrentNode);
	if(it == m_listMap.end())
	{
		std::pair<std::map<Node*, ChildListIterator>::iterator, bool> resultPair;
		resultPair = m_listMap.insert( std::pair<Node<Elem>*, ChildListIterator>
						  (m_pCurrentNode, ChildListIterator(*m_pCurrentNode)) );
		m_pCurrentListIter = &(resultPair.first->second);
	}
	else
	{
		m_pCurrentListIter = &it->second;
	}
}
/*------------------------------------------------------------------------------
Method: currentItem

Description:
	Returns the item currently pointed to by the iterator.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>& Node<Elem>::DFSIterator::operator*() const
{
	assert(m_pCurrentNode != NULL);
	return *m_pCurrentNode;
}

/*------------------------------------------------------------------------------
Method: operator->

Description:
	Returns the item currently pointed to by the iterator.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>* Node<Elem>::DFSIterator::operator->() const
{
	assert(m_pCurrentNode != NULL);
	return m_pCurrentNode;
}

template<class Elem>
typename Node<Elem>::DFSIterator& Node<Elem>::DFSIterator::operator=(const DFSIterator& rhs)
{
	if(this == &rhs)
	{
		return *this;
	}
	m_pRootNode = rhs.m_pRootNode;
	m_pCurrentNode = rhs.m_pCurrentNode;
	m_listMap = rhs.m_listMap;
	return *this;
}

template<class Elem>
bool Node<Elem>::DFSIterator::operator!=(const DFSIterator& rhs) const
{
	return !(operator==(rhs));
}

template<class Elem>
bool Node<Elem>::DFSIterator::operator==(const DFSIterator& rhs) const
{
	if ((m_pRootNode == rhs.m_pRootNode && m_pCurrentNode == rhs.m_pCurrentNode) || 
		(&rhs == &endNodeIter && m_pCurrentNode == &endNode))
	{
		return true;
	}
	else
	{
		return false;
	}
}



// removee is the node to be deleted
template<class Elem>
bool Node<Elem>::DFSIterator::removeNode()
{
	if(m_pCurrentNode->m_pParentNode != NULL)
	{

		//find the parent node
		Node* pParentNode  = m_pCurrentNode->m_pParentNode;

		//load parent node's child list
		ChildListIterator* pCurrentListIter;
		std::map<Node*,ChildListIterator>::iterator it = m_listMap.find(pParentNode);
		if(it != m_listMap.end())
		{
			pCurrentListIter = &it->second;
		}
		else
		{
			throw std::exception(std::runtime_error("A child list doesn't exist when one should."));
		}
		(*pCurrentListIter)--;//point iterator to the removee

		pParentNode->removeChild(*pCurrentListIter);

		//remove the removee's child ChildListIterator from the list map
		if(m_listMap.find(m_pCurrentNode) != m_listMap.end())
		{
			m_listMap.erase(m_listMap.find(m_pCurrentNode));
		}

		sNodeSet.erase(&**this);

		//put the system into the previous state with the node now removed
		//and increment the DFSIterator to find the previous node
		m_pCurrentNode = pParentNode;
		m_pCurrentListIter = pCurrentListIter;
		(*pCurrentListIter)--;
		operator++();
	}
	else
	{
		//if no parent, must be a root node. Do nothing.
		std::cerr << "ERR: Node<Elem>::removeNode(): Node not removed because it is a root node.\n";
		return false;
	}
	return true;
}
