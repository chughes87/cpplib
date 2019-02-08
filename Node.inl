/*=============================================================================
File: Node.inl

Description:
	This file provides the class definitions for Node.h without cluttering the
	file.
===============================================================================*/

template<class Elem>
std::set<Node<Elem>*> Node<Elem>::sNodeSet;

template<class Elem>
typename Node<Elem> Node<Elem>::endNode = Node();

template<class Elem>
typename Node<Elem>::DFSIterator Node<Elem>::endNodeIter = DFSIterator(endNode);

//template<class Elem>
//std::set<Node<Elem>*>&  Node<Elem>::getNodeSet()
//{
//    static std::set<Node<Elem>*>   Node<Elem>::sNodeSet;
//    return Node<Elem>::sNodeSet;
//}

template<class Elem>
typename const Node<Elem>::DFSIterator& Node<Elem>::end()
{
	return endNodeIter;
}

template<class Elem>
Node<Elem>::Node()
	:m_pParentNode(NULL)
{
}

/*------------------------------------------------------------------------------
Constructor: Node

Description:
	Instantiates member variables of the Node object
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>::Node(const Elem& value)
	:m_value(value), 
	 m_pParentNode(NULL)
{
	//std::cout << "Creating Node:\t" << this << " of value:\t" << m_value << std::endl;
} 

/*------------------------------------------------------------------------------
Constructor: Node (copy ctor)

Description:
	Instantiates this node object based on a previously existing one.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>::Node(const Node& rNode)
	:m_value(*rNode),
	 m_pParentNode(NULL)
{
	ChildListIteratorConst listIter = rNode.firstChild();
	for(;listIter != rNode.lastChild(); listIter++)
	{
		Node* pChild = new Node(*listIter);
		addChild(pChild);
	}
} 

/*------------------------------------------------------------------------------
Destructor: Node

Description:
	Deletes the entire subtree that is rooted at this node.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>::~Node()
{
	//std::cout << "deleting Node:\t" << this << " of value:\t" << m_value << std::endl;
	std::vector<Node*>::iterator it = m_childList.begin();
	for(; it!=m_childList.end(); ++it)
	{
		if(*it)
		{
			Node::sNodeSet.erase(*it);
			delete *it;
		}
	}
	Node::sNodeSet.erase(this);
}

/*------------------------------------------------------------------------------
Method: operator*

Description:
	Simple getter method to expose this private variable's value to users.

Returns:
	The variable stored in this node.
-------------------------------------------------------------------------------*/
template<class Elem>
const Elem& Node<Elem>::operator*() const
{
	return m_value;
}

template<class Elem>
Elem& Node<Elem>::operator*()
{
	return m_value;
}

/*------------------------------------------------------------------------------
Method: operator->

Description:
	Simple getter method to expose this private variable's value to users.

Returns:
	The variable stored in this node.
-------------------------------------------------------------------------------*/
template<class Elem>
Elem* Node<Elem>::operator->()
{
	return &m_value;
}

/*------------------------------------------------------------------------------
Method: operator= (assignment operator) 

Description:
	Simple setter method to set the node's internal value member.

Returns:
	Coded result indicating success or failure of the operation.
-------------------------------------------------------------------------------*/
template<class Elem>
void Node<Elem>::operator=(const Elem& value)
{
	m_value = value;
}

template<class Elem>
bool Node<Elem>::operator==(const Node& rhs) const
{
	if( m_pParentNode == rhs.m_pParentNode &&
		m_key == rhs.m_key &&
		m_value == rhs.m_value &&
		m_childList == rhs.m_childList )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*------------------------------------------------------------------------------
Method: addChild

Description:
	Adds a child node to this node's child list. Having the user pass nodes by 
	pointer instead of a reference makes it easier for the user to build a tree.

Returns:
	A coded result indicating success or failure of the operation.
-------------------------------------------------------------------------------*/
template<class Elem>
Node<Elem>* Node<Elem>::addChild(Node* pChildNode)
{
	//sanity check
	if(pChildNode == NULL)
	{
		std::cerr << "Node::addChild ERR: given pointer is NULL. No child added.\n";
		return NULL;
	}
	std::set<Node*>::iterator it = Node::sNodeSet.find(pChildNode);
	if(it==Node::sNodeSet.end())
	{
		Node::sNodeSet.insert(pChildNode);
		pChildNode->m_pParentNode = this;
		m_childList.push_back(pChildNode);
		return pChildNode;
	}
	else
	{
		std::cerr << "Node::addChild ERR: This node already exists. \
					  in this tree. No child added.\n";
		return NULL;
	}
}

template<class Elem>
Node<Elem>* Node<Elem>::addChild(const Node& childNode)
{
	Node* pChildNode = new Node(childNode);
	Node::sNodeSet.insert(pChildNode);
	pChildNode->m_pParentNode = this;
	m_childList.push_back(pChildNode);
	return pChildNode;
}

template<class Elem>
Node<Elem>* Node<Elem>::addChild(const Elem& value)
{
	Node* newNode = new Node(value);
	Node::sNodeSet.insert(newNode);
	newNode->m_pParentNode = this;
	m_childList.push_back(newNode);
	return newNode;
}

template<class Elem>
typename Node<Elem>::DFSIterator Node<Elem>::addChild(const DFSIterator& DFSIterator)
{
	Node* newNode = new Node(*DFSIterator.m_pCurrentNode);
	Node* addedNode = addChild(newNode);
	Node::DFSIterator retVal;
	if(addedNode != NULL)
	{
		retVal = Node::DFSIterator(*addedNode);
	}
	return retVal;
}

/*------------------------------------------------------------------------------
Method: hasChild

Description:
	Informs the user wether or not this node has any children.
-------------------------------------------------------------------------------*/
template<class Elem>
bool Node<Elem>::hasChild() const
{
	return m_childList.size() > 0;
}

/*------------------------------------------------------------------------------
Method: deleteChild

Description:
	removes the indicated child from this node's child list.
-------------------------------------------------------------------------------*/
template<class Elem>
bool Node<Elem>::removeDescendant(DFSIterator& rDFSIter)
{
	return rDFSIter.removeNode();
}

template<class Elem>
void Node<Elem>::removeChild(ChildListIterator& rChildListIter)
{
	if(*rChildListIter.m_Iter != NULL)
	{
		delete *rChildListIter.m_Iter;
		*rChildListIter.m_Iter = NULL;
	}
	rChildListIter.m_Iter = m_childList.erase(rChildListIter.m_Iter);
}

/*------------------------------------------------------------------------------
Method: begin

Description:
	Returns the iterator to the root node of the tree.
-------------------------------------------------------------------------------*/
template<class Elem>
typename Node<Elem>::DFSIterator Node<Elem>::begin()
{
	return DFSIterator(*this);
}

/*------------------------------------------------------------------------------
Method: begin

Description:
	Returns the iterator to the root node of the tree.
-------------------------------------------------------------------------------*/
template<class Elem>
typename Node<Elem>::DFSIteratorConst Node<Elem>::begin() const
{
	return DFSIteratorConst(*this);
}


template<class Elem>
typename Node<Elem>::ChildListIterator Node<Elem>::firstChild()
{
	return ChildListIterator(*this);
}

template<class Elem>
typename Node<Elem>::ChildListIteratorConst Node<Elem>::firstChild() const
{
	return ChildListIteratorConst(*this);
}


template<class Elem>
typename Node<Elem>::ChildListIterator Node<Elem>::lastChild()
{
	return ChildListIterator(*this, m_childList.end());
}

template<class Elem>
typename Node<Elem>::ChildListIteratorConst Node<Elem>::lastChild() const
{
	return ChildListIteratorConst(*this, m_childList.end());
}

template<class Elem>
typename Node<Elem>::DFSIterator Node<Elem>::find(const Elem& findElem)
{
	if(**this == findElem)
	{
		return DFSIterator(*this);
	}

	for(DFSIterator find_iter(*this); find_iter != end(); find_iter++)
	{
		if(**find_iter == findElem)
		{
			return find_iter;
		}
	}
}

template<class Elem>
typename Node<Elem>::DFSIteratorConst Node<Elem>::find(const Elem& findElem) const
{
	if(**this == findElem)
	{
		return DFSIteratorConst(*this);
	}

	for(DFSIteratorConst find_iter(*this); find_iter != end(); find_iter++)
	{
		if(**find_iter == findElem)
		{
			return find_iter;
		}
	}
}
