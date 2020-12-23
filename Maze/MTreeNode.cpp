#include <iostream>
#include "MTreeNode.h"

MTreeNode::MTreeNode(MTreeNode * parent = nullptr)
{
	m_parent = parent;

	int m_children_length =
		sizeof(m_children) /
		sizeof(*m_children);

	for (int i = 0; i < m_children_length; i++)
		m_children[i] = nullptr; // IMPORTANT: to check nullptr
}

MTreeNode::~MTreeNode()
{
	int m_children_length =
		sizeof(m_children) /
		sizeof(*m_children);

	for (int i = 0; i < m_children_length; i++)
		delete m_children[i];
	delete[] m_children;
}

int MTreeNode::i() const { return m_i; }
int MTreeNode::j() const { return m_j; }

const MTreeNode * MTreeNode::parent() const { return m_parent; }
const MTreeNode * MTreeNode::child(int i) const { return m_children[i]; }

int MTreeNode::distance() const { return m_distance; }

int MTreeNode::childCount() const
{
	int child_count = 0;

	int m_children_length =
		sizeof(m_children) /
		sizeof(*m_children);

	for (int i = 0; i < m_children_length; i++)
		if (m_children[i] != nullptr)
			child_count++;

	return child_count;
}

bool MTreeNode::addChild(int i, int j)
{
	MTreeNode* child = MTreeNode::beginTree(i, j);
	
	if ((m_i == i) ^ (m_j == j)) {
		int axis = m_j == j ? 0 : 1; // ATTENTION: implemented for only TWO children, by x and y axis
		
		delete m_children[axis];

		child->m_distance = (i - m_i) ^ (j - m_j);
		m_children[axis] = child;
		return true;
	}

	return false;
}

MTreeNode * MTreeNode::hasChild(int i, int j)
{
	int children_count =
		sizeof(m_children) /
		sizeof(*m_children);

	for (int k = 0; k < children_count; k++) {
		MTreeNode* node = m_children[k];
		if (node != nullptr &&
			node->i() == i &&
			node->j() == j)
			return node;
	}

	return nullptr;
}

MTreeNode * MTreeNode::beginTree(int i, int j)
{
	MTreeNode* node = new MTreeNode();
	node->m_i = i;
	node->m_j = j;

	return node;
}