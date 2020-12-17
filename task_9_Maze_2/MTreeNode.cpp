#include <iostream>
#include "MTreeNode.h"

MTreeNode::MTreeNode(MTreeNode * parent = nullptr)
{
	m_parent = parent;

	m_children[0] = nullptr;
	m_children[1] = nullptr;
}

MTreeNode::~MTreeNode()
{
	delete m_children[0];
	delete m_children[1];

	delete[] m_children;
}

int MTreeNode::i() const { return m_i; }
int MTreeNode::j() const { return m_j; }

const MTreeNode * MTreeNode::parent() const { return m_parent; }
const MTreeNode * MTreeNode::child(int i) const { return m_children[i]; }

int MTreeNode::distance() const { return m_distance; }

int MTreeNode::childCount() const
{
	return
		(m_children[0] != nullptr) +
		(m_children[1] != nullptr);
}

bool MTreeNode::addChild(int i, int j)
{
	MTreeNode* child = new MTreeNode(this);
	child->m_i = i;
	child->m_j = j;
	
	if (m_i == i || m_j == j) {
		int axis = m_j == j ? 0 : 1;
		
		delete m_children[axis];

		child->m_distance = i - m_i ^ j - m_j;
		m_children[axis] = child;
		return true;
	}

	return false;
}

MTreeNode * MTreeNode::hasChild(int i, int j)
{
	if (m_i == i) return m_children[0];
	if (m_j == j) return m_children[1];

	return nullptr;
}

MTreeNode * MTreeNode::beginTree(int i, int j)
{
	MTreeNode* node = new MTreeNode();
	node->m_i = i;
	node->m_j = j;

	return node;
}
