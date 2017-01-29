#include "Tree.h"
#include <iostream>
#include <iterator>

Tree::Tree()
{
	GameState temp("         ");
	rootNode = std::make_shared<GameState>(temp);
	GenerateTree();
}


//Tree::~Tree()
//{
//}

void Tree::GenerateTree()
{
	std::list<std::shared_ptr<GameState>> m_nodesToExpand;

	m_nodesToExpand.push_back(rootNode);

	while (m_nodesToExpand.size() > 0)
	{
		if (m_nodesToExpand.front()->GetGameStatus() == GameState::playing)
		{
			for (size_t i = 0; i < 9; i++) {
				std::string tempString = m_nodesToExpand.front()->GetBoardString();
				std::shared_ptr<GameState> tempBoard(new GameState);
				if (tempString[i] == ' ')
				{
					if (m_nodesToExpand.front()->DidXGoLast() == false)
					{
						tempString[i] = 'x';
						tempBoard->TurnPlaced(true);
					}
					else
					{
						tempString[i] = 'o';
						tempBoard->TurnPlaced(false);
					}
					tempBoard->SetBoardString(tempString);
					tempBoard->CheckForWin();
					m_nodesToExpand.front()->AddChild(tempBoard);
					m_nodesToExpand.push_back(tempBoard);
				}
			}
		}
		m_nodesToExpand.erase(m_nodesToExpand.begin());
	}

	std::cout << "Generated the tree" << std::endl;

	CalculateNodeValues(rootNode);

	std::cout << "Given the node values" << std::endl;
}

double Tree::CalculateNodeValues(std::shared_ptr<GameState>& _node)
{
	double t = 0;

	for (std::shared_ptr<GameState> l : _node->GetChildNodes())		//change this to actual not 2015 stuff
	{
		t = CalculateNodeValues(l);
		_node->SetNodeValue(t);
	}

	return _node->GetNodeValue();
}

std::shared_ptr<GameState> Tree::GetNode()
{
	return rootNode;
}

void Tree::SetNode(std::shared_ptr<GameState> _node)
{
	rootNode = _node;
}