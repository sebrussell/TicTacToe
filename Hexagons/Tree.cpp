#include "Tree.h"
#include <iostream>


Tree::Tree()
{
	GameState temp("         ");
	rootNode = std::make_shared<GameState>(temp);
}


//Tree::~Tree()
//{
//}

void Tree::GenerateTree()
{
	std::list<std::shared_ptr<GameState>> m_nodesToExpand;
	//std::list<GameState> m_nodesToExpand;

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

	CalculateNodeValues(rootNode);
}

int Tree::CalculateNodeValues(std::shared_ptr<GameState>& _node)
{
	if (_node->GetNodeValue() == 0)
	{
		for (auto &node : _node->GetChildNodes())
		{
			int t = CalculateNodeValues(node);
			_node->SetNodeValue(t);
		}
	}
	else
	{
		return _node->GetNodeValue();
	}
}
