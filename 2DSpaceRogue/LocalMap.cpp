#include"LocalMap.h"

LocalMap::LocalMap()
{

}
void LocalMap::generateMap()
{
//NODE CREATION LOOP
//1. Create start node (set type)
//2. add it to nodeVec
//3. add it to node neighbours

	vector <Vector2> coords;

	while (nodeVec.size() < numNodes)
	{

		if (nodeVec.size() == 0)
		{
			Vector2 startingPos = generateCoord();
			coords.push_back(startingPos);
			addNode(startingPos);
		}
		else
		{
			Vector2 newCoord = generateCoord();
			int checked = 0;
			for (int j = 0; j < coords.size(); j++)
			{
				Vector2 existingCoord = coords.at(j);
				Vector2 tempVector = existingCoord - newCoord;

				if (tempVector.length() < 50 || tempVector.length() > 600)
				{
					break;
				}
				else
				{
					checked++;
				}
			}
			if (checked == coords.size())
			{
				addNode(newCoord);
				coords.push_back(newCoord);
				generateEdges(nodeVec.back());
			}
		}
	}
	generateType();
}
void LocalMap::addNode(Vector2 pos)
{
	Node* node = new Node(pos);
	nodeVec.push_back(node);

}
void LocalMap::generateType()
{
//-----------DETERMINE START AND END NODES-----------//
	//loop through all nodes to check if they have the haighest or lowest x value. Highest x = end, lowest x = start.
	float lowestX = 1000000;
	int lowestXIndex = 0;
	float highestX = 0;
	int highestXIndex = 0;

	for (int i = 0; i < nodeVec.size(); i++)
	{
		float tempX = nodeVec.at(i)->getX();

		if (tempX < lowestX)
		{
			lowestX = tempX;
			lowestXIndex = i;
		}
		if (tempX > highestX)
		{
			highestX = tempX;
			highestXIndex = i;
		}
	}
	nodeVec.at(lowestXIndex)->setLocType(Node::Start);
	nodeVec.at(highestXIndex)->setLocType(Node::End);

//---------DETERMINE OTHER TYPES-------------//
	//loop through all node with type 0 and apply probability for each LocalMap type
	int defined = 2;

		switch (type)
		{
		case Node::Start:
		case Node::End:
			defined = 2;
			while (defined < nodeVec.size())
			{
				for (int i = 0; i < nodeVec.size(); i++)
				{
					if (nodeVec.at(i)->getLocType() == Node::Undefined)
					{
						int randNum = rand() % 100 + 1;
						if (randNum <= 25)
						{
							nodeVec.at(i)->setLocType(Node::Stranded);
							defined++;
						}
						if (randNum > 25 && randNum <= 50)
						{
							nodeVec.at(i)->setLocType(Node::Trade);
							defined++;
						}
						if (randNum > 50 && randNum <= 75)
						{
							nodeVec.at(i)->setLocType(Node::Wreck);
							defined++;
						}
						if (randNum > 75)
						{
							nodeVec.at(i)->setLocType(Node::Live);
							defined++;
						}
					}
				}
			}
			break;
		case Node::Uncharted:
			defined = 2;
			while (defined < nodeVec.size())
			{
				for (int i = 0; i < nodeVec.size(); i++)
				{
					if (nodeVec.at(i)->getLocType() == Node::Undefined)
					{
						int randNum = rand() % 100 + 1;
						if (randNum <= 10)
						{
							nodeVec.at(i)->setLocType(Node::Stranded);
							defined++;
						}
						if (randNum > 10 && randNum <= 50)
						{
							nodeVec.at(i)->setLocType(Node::Trade);
							defined++;
						}
						if (randNum > 50 && randNum <= 60)
						{
							nodeVec.at(i)->setLocType(Node::Wreck);
							defined++;
						}
						if (randNum > 60)
						{
							nodeVec.at(i)->setLocType(Node::Live);
							defined++;
						}
					}
				}
			}
			break;
		case Node::Civilised:
			defined = 2;
			while (defined < nodeVec.size())
			{
				for (int i = 0; i < nodeVec.size(); i++)
				{
					if (nodeVec.at(i)->getLocType() == Node::Undefined)
					{
						int randNum = rand() % 100 + 1;
						if (randNum <= 40)
						{
							nodeVec.at(i)->setLocType(Node::Stranded);
							defined++;
						}
						if (randNum > 40 && randNum <= 45)
						{
							nodeVec.at(i)->setLocType(Node::Trade);
							defined++;
						}
						if (randNum > 45 && randNum <= 85)
						{
							nodeVec.at(i)->setLocType(Node::Wreck);
							defined++;
						}
						if (randNum > 85)
						{
							nodeVec.at(i)->setLocType(Node::Live);
							defined++;
						}
					}
				}
			}
			break;
		case Node::Asteroid:
			defined = 2;
			while (defined < nodeVec.size())
			{
				for (int i = 0; i < nodeVec.size(); i++)
				{
					if (nodeVec.at(i)->getLocType() == Node::Undefined)
					{
						int randNum = rand() % 100 + 1;
						if (randNum <= 40)
						{
							nodeVec.at(i)->setLocType(Node::Stranded);
							defined++;
						}
						if (randNum > 40 && randNum <= 50)
						{
							nodeVec.at(i)->setLocType(Node::Trade);
							defined++;
						}
						if (randNum > 45 && randNum <= 90)
						{
							nodeVec.at(i)->setLocType(Node::Wreck);
							defined++;
						}
						if (randNum > 90)
						{
							nodeVec.at(i)->setLocType(Node::Live);
							defined++;
						}
					}
				}
			}
			break;
		default:
			break;
		}

}
void LocalMap::generateEdges(Node* currentNode)
{
//-------------DETERMINE NODES WITHIN EDGE RANGE----------//
	int connectedNodes = 0;

	for (int j = 0; j < nodeVec.size(); j++)
	{
		Vector2 checking = nodeVec.at(j)->getPos();
		Vector2 temp = currentNode->getPos() - checking;
		float distance = temp.length();
		if (distance < 200 && distance != 0)
		{
			addEdges(currentNode, nodeVec.at(j));
			connectedNodes++;
		}
	}
	if (connectedNodes == 0)
	{
		int closestNodeIndex = 0;
		float closestDist = 100000;

//-------------DETERMINE CLOSEST NODE -------------------//
		for (int i = 0; i < nodeVec.size(); i++)
		{
			Vector2 check = nodeVec.at(i)->getPos();
			Vector2 temp = currentNode->getPos() - check;
			float distance = temp.length();

			if (distance < closestDist && distance != 0)
			{
				closestDist = distance;
				closestNodeIndex = i;
			}
		}

		addEdges(currentNode, nodeVec.at(closestNodeIndex));
	}
}
void LocalMap::addEdges(Node* u, Node* v)
{
	//add connection in each Node's neighbour vector. Store each nodes connections
	u->addNeighbour(v);
	v->addNeighbour(u);

}
Vector2 LocalMap::generateCoord()
{
	float randomX = 0;
	float randomY = 0;

	randomX = float(rand() % 924 +50);
	randomY = float(rand() % 384 +192);

	Vector2 coord = Vector2(randomX, randomY);
	return coord;
}
void LocalMap::draw(Renderer* renderer)
{
	for (int i = 0; i < nodeVec.size(); i++)
	{
		nodeVec.at(i)->draw(renderer);
		nodeVec.at(i)->drawEdges(renderer);
	}
}
void LocalMap::handleInputs(SDL_Event* e)
{
	//callind node::handleInputs()
	for (int i = 0; i < nodeVec.size(); i++)
	{
		nodeVec.at(i)->handleInputs(e);
		if (nodeVec.at(i)->isHovered)
		{
			//display text describing type
		}
		if (nodeVec.at(i)->isClicked)
		{
			//If it's a neighbour of current node
				//move player to this position
				//open event display
		}
	}
	//Applying behavior
}