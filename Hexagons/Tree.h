#pragma once
#include "GameState.h"		//header files
#include <algorithm>

class Tree
{
public:
	Tree();
	//~Tree();
	double GenerateTree(std::shared_ptr<GameState> _root);
	double CalculateNodeValues(std::shared_ptr<GameState>& _node);
	std::shared_ptr<GameState> GetNode();
	void SetNode(std::shared_ptr<GameState> _node);
	void Reset();
private:
	std::shared_ptr<GameState> rootNode;
	std::shared_ptr<GameState> generatedTree;
};

