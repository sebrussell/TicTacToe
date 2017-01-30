#pragma once
#include "GameState.h"
#include <algorithm>

class Tree
{
public:
	Tree();
	//~Tree();
	void GenerateTree();
	double CalculateNodeValues(std::shared_ptr<GameState>& _node);
	std::shared_ptr<GameState> GetNode();
	void SetNode(std::shared_ptr<GameState> _node);
	void Reset();
private:
	//std::vector<std::shared_ptr<GameState>> m_nodes;
	std::shared_ptr<GameState> rootNode;
	std::shared_ptr<GameState> generatedTree;
};

