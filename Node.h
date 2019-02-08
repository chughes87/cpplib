/*=============================================================================
File: ChildListIterator.h

Description:
This class provides an iterator to iterate through a tree node's child list.
===============================================================================*/
#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

/*=============================================================================
File: Node.h

Description:
	This class provides a node object for the tree model of our database data.
===============================================================================*/


template<class Elem>
class Node
{
public:
	class DFSIterator;
	class DFSIteratorConst;
	class ChildListIterator;
	class ChildListIteratorConst;

	Node();
	~Node();
	Node(const Elem& value);
	Node(const Node& rNode);

	// setters and getters
	void setKey(std::wstring key){m_key = key;}
	const std::wstring& getKey() const {return m_key;}

	// tree mutators
	Node* addChild(const Node& childNode); // copy subtree
	Node* addChild(Node* pChildNode); // insert subtree
	Node* addChild(const Elem& value);
	DFSIterator addChild(const DFSIterator& DFSIterator);
	bool removeDescendant(DFSIterator& it);
	void removeChild(ChildListIterator& it);

	// tree accessors
	ChildListIterator firstChild();
	ChildListIteratorConst firstChild() const;
	ChildListIterator lastChild();
	ChildListIteratorConst lastChild() const;
	DFSIterator begin();
	DFSIteratorConst begin() const;
	static const DFSIterator& end();
	DFSIterator find(const Elem& findElem);
	DFSIteratorConst find(const Elem& findElem) const;

	// operator overloads
	const Elem& operator*() const;
	Elem& operator*();
	Elem* operator->();
	void operator=(const Elem& rhs);
	bool operator==(const Node<Elem>& rhs) const;

private:
	bool hasChild() const;

	Node* m_pParentNode;
	std::wstring m_key;
	Elem m_value;
	std::vector<Node*> m_childList;
	static std::set<Node*> sNodeSet; //to prevent malformed trees
	static Node endNode;
	static DFSIterator endNodeIter;
};

template<class Elem>
class Node<Elem>::ChildListIteratorConst
{
public:
	ChildListIteratorConst(const Node& rNode, const std::wstring& findKey = L"");
	ChildListIteratorConst(const ChildListIterator& iter);
	~ChildListIteratorConst(){}

	ChildListIteratorConst* operator++();
	ChildListIteratorConst* operator--();
	const Node& operator*() const;
	const Node* operator->() const;
	bool operator==(const ChildListIteratorConst& rhs) const;
	bool operator!=(const ChildListIteratorConst& rhs) const;

	ChildListIteratorConst& operator=(const ChildListIterator& rhs);
	bool operator==(const ChildListIterator& rhs) const;
	bool operator!=(const ChildListIterator& rhs) const;

	friend class Node;

private:
	ChildListIteratorConst(const Node& rNode, typename const std::vector<Node*>::const_iterator& it);
	void initialize(const std::wstring& findKey);

	const std::vector<Node*>* m_pList;
	typename std::vector<Node*>::const_iterator m_Iter;
	std::wstring m_findKey;
};

template<class Elem>
class Node<Elem>::ChildListIterator 
{
public:
	ChildListIterator(Node& rNode, const std::wstring& findKey = L"");
	~ChildListIterator(){}

	ChildListIterator* operator++();
	ChildListIterator* operator--();
	Node& operator*() const;
	Node* operator->() const;
	ChildListIteratorConst& operator=(const ChildListIteratorConst& rhs);
	bool operator==(const ChildListIterator& rhs) const;
	bool operator!=(const ChildListIterator& rhs) const;
	operator ChildListIteratorConst() const {return ChildListIteratorConst(this);}
	
	friend class Node;
	friend class ChildListIteratorConst;

private:
	ChildListIterator(Node& rNode, typename const std::vector<Node*>::iterator& it);
	void initialize(const std::wstring& findKey);

	std::vector<Node*>* m_pList;
	typename std::vector<Node*>::iterator m_Iter;
	std::wstring m_findKey;
	//typename std::vector<Node*>::iterator m_FindIter;
};


template<class Elem>
class Node<Elem>::DFSIteratorConst
{
public:
	DFSIteratorConst();
	DFSIteratorConst(Node& rRootNode);
	DFSIteratorConst(const DFSIteratorConst& rDFSIteratorConst);
	DFSIteratorConst(const DFSIterator& rDFSIterator);
	~DFSIteratorConst();

	const Node& operator*() const;
	const Node* operator->() const;
	DFSIteratorConst* operator++();
	DFSIteratorConst& operator=(const DFSIteratorConst& rhs);
	bool operator==(const DFSIteratorConst& rhs) const;
	bool operator!=(const DFSIteratorConst& rhs) const;

	DFSIteratorConst& operator=(const DFSIterator& rhs);
	bool operator==(const DFSIterator& rhs) const;
	bool operator!=(const DFSIterator& rhs) const;

	friend class Node;

private:
	DFSIterator* m_pDFSIterator;
};

template<class Elem>
class Node<Elem>::DFSIterator
{
public:
	DFSIterator();
	DFSIterator(Node& rRootNode);
	DFSIterator(const DFSIterator& rDFSIterator);
	~DFSIterator();

	DFSIterator* operator++();
	Node& operator*() const;
	Node* operator->() const;
	DFSIterator& operator=(const DFSIterator& rhs);
	bool operator==(const DFSIterator& rhs) const;
	bool operator!=(const DFSIterator& rhs) const;
	operator DFSIteratorConst() const {return DFSIteratorConst(*m_pCurrentNode);}

	friend class Node;

private:
	bool removeNode();
	bool traverseDown();
	bool traverseUp();
	void endTraversal();
	void initChildListIterator();

	Node* m_pRootNode;
	Node* m_pCurrentNode;
	ChildListIterator* m_pCurrentListIter;
	std::map<Node*, ChildListIterator>  m_listMap;
};


#include "ChildListIteratorConst.inl"
#include "ChildListIterator.inl"
#include "DFSIteratorConst.inl"
#include "DFSIterator.inl"
#include "Node.inl"
