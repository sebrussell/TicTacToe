#pragma once
#include "GameState.h"
#include <algorithm>>

class Tree
{
public:
	Tree();
	//~Tree();
	void GenerateTree();
	int CalculateNodeValues(std::shared_ptr<GameState>& _node);
private:
	//std::vector<std::shared_ptr<GameState>> m_nodes;
	std::shared_ptr<GameState> rootNode;
};

