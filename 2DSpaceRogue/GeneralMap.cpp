#include"GeneralMap.h"


GeneralMap::GeneralMap()
{

}
void GeneralMap::load()
{
	Ship shipy = Ship(100, 500, 50, 50);
	ship = shipy;

	generateMap();

}
void GeneralMap::addNode(int i, float x, float y)
{
		//Pointer to a node
	Vector2 vec = Vector2(x, y);
	Node* node = new Node(vec);
		//set node index
	/*node->setIndex(i);*/

		//Store node in general Map  grid vector
	genMapGridVec.push_back(node);

}
void GeneralMap::generateMap()
{
	float x;
	float y;


	for (int i = 0; i < numNodes; i++)
	{
		x = coord[i][0];
		y = coord[i][1];
		addNode(i, x, y);
	}
	generateEdges();
	generateType();

	generateLocalMap();
	currentMap = locMapVec.front();
}
void GeneralMap::generateLocalMap()
{
	for (int i = 0; i < genMapGridVec.size(); i++)
	{
		int type = genMapGridVec.at(i)->getLocType();
		LocalMap* local = new LocalMap();
		locMapVec.push_back(local);
		local->setType(type);
		local->generateMap();
	}
}
void GeneralMap::generateType()
{

	//Type rules:
	//#1 the firts and last node are the start and end node
	//#2 at least one neighbour of the start and end node has to be civilised type
	//#3 at least one neighbour of the start and end node has to be asteroid type
	//#4 neighbours of asteroid type has a 60% chance of being uncharted type
	//#5 everynode has a 10% chance of being an asteroid type

	//Type setting process:
	//#1 set start and end nodes
	//#2 set asteroid type in start and end node neighbours
	//#3 go over all nodes with no type and apply 10% chance to make them asteroids
	//#4 go over all asteroid neighbours with no type and apply 60% chance of uncharted
	//#5 go over every node, if no type, then apply civilised type

	//generate seed
	srand((unsigned int)time(0));


//#1 set start and end nodes
	genMapGridVec.front()->setLocType(Node::Start);
	genMapGridVec.back()->setLocType(Node::End);

//#2 set asteroid type in start and end node neighbours
		//retrieve how many neighbours to use as range
	size_t rangeStart = genMapGridVec.front()->getNeighbours().size();
		//pick a random number in range to choose a neighbour
	int chosenStartAst = rand() % rangeStart ;
		//assign asteroid type to chosen neighbour
	genMapGridVec.front()->getNeighbour(chosenStartAst)->setLocType(5);

	//NEEDS FIXING
	for (int a = 0; a < genMapGridVec.back()->getNeighbours().size(); a++)
	{
		int chosenStartCiv = rand() % rangeStart;
		if (genMapGridVec.front()->getNeighbour(chosenStartCiv)->getLocType() == Node::Undefined && a == 0)
		{
			genMapGridVec.front()->getNeighbour(chosenStartCiv)->setLocType(Node::Asteroid);
		}
		else if (genMapGridVec.front()->getNeighbour(chosenStartCiv)->getLocType() == Node::Undefined && a == 1)
		{
			genMapGridVec.front()->getNeighbour(chosenStartCiv)->setLocType(Node::Civilised);
		}
	}

	//retrieve how many neighbours to use as range
	size_t rangeEnd = genMapGridVec.back()->getNeighbours().size();
	//pick a random number in range to choose a neighbour
	int chosenEndAst = rand() % rangeEnd ;
	//assign asteroid type to chosen neighbour. (might need to retrieve index first to change in gen map vec)
	genMapGridVec.back()->getNeighbour(chosenEndAst)->setLocType(Node::Asteroid);


	//NEEDS FIXING
	for (int b = 0; b < genMapGridVec.back()->getNeighbours().size(); b++)
	{
		int chosenEndCiv = rand() % rangeStart;
		if (genMapGridVec.back()->getNeighbours().at(chosenEndCiv)->getLocType() == Node::Undefined && b == 0)
		{
			genMapGridVec.back()->getNeighbours().at(chosenEndCiv)->setLocType(Node::Asteroid);
		}
		else if (genMapGridVec.back()->getNeighbours().at(chosenEndCiv)->getLocType() == Node::Undefined && b == 1)
		{
			genMapGridVec.back()->getNeighbours().at(chosenEndCiv)->setLocType(Node::Civilised);
		}
	}




//#3 go over all nodes with no type and apply 10% chance to make them asteroids

	for (int i = 0; i < numNodes; i++)
	{
		if (genMapGridVec.at(i)->getLocType() == Node::Undefined)
		{
			int ranNum = rand() % 100 + 1;

			if (ranNum <= 10)
			{
				genMapGridVec.at(i)->setLocType(Node::Asteroid);
			}
		}
	}
//#4 go over all asteroid neighbours with no type and apply 60% chance of uncharted
	for (int j = 0; j < numNodes; j++)
	{
		if (genMapGridVec.at(j)->getLocType() == Node::Asteroid)
		{
			for (int k = 0; k < genMapGridVec.at(j)->getNeighbours().size(); k++)
			{
				int ranNum = rand() % 100 + 1;

				if (ranNum <= 40 && genMapGridVec.at(j)->getNeighbour(k)->getLocType() == 0 )
				{
					genMapGridVec.at(j)->getNeighbour(k)->setLocType(Node::Uncharted);
				}
			}
		}
	}

//#5 go over every node, if no type, then apply civilised type
	for (int l = 0; l < numNodes; l++)
	{
		if (genMapGridVec.at(l)->getLocType() == Node::Undefined)
		{
			genMapGridVec.at(l)->setLocType(Node::Civilised);
		}
	}
}
void GeneralMap::generateEdges()
{
	addEdge(0,1);
	addEdge(0,5);
	addEdge(0,4); 
	addEdge(1,4);
	addEdge(1,5);
	addEdge(1,2);
	addEdge(1,6);
	addEdge(2,5);
	addEdge(2,6);
	addEdge(2,7);
	addEdge(2,3);
	addEdge(3,6);
	addEdge(3,7);
	addEdge(4,5);
	addEdge(4,9);
	addEdge(4,8);
	addEdge(5,6);
	addEdge(5,10);
	addEdge(5,9);
	addEdge(5,8);
	addEdge(6,7);
	addEdge(6,11);
	addEdge(6,10);
	addEdge(6,9);
	addEdge(7,11);
	addEdge(7,10);
	addEdge(8,9);
	addEdge(8,13);
	addEdge(8,12);
	addEdge(9,10);
	addEdge(9,14);
	addEdge(9,13);
	addEdge(9,12);
	addEdge(10,11);
	addEdge(10,15);
	addEdge(10,14);
	addEdge(10,15);
	addEdge(11,15);
	addEdge(11,14);
	addEdge(12,13);
	addEdge(13,14);
	addEdge(14,15);
}
void GeneralMap::addEdge(int u, int v)
{
	Node* nodeU = genMapGridVec.at(u);
	Node* nodeV = genMapGridVec.at(v);

	//add connection in each Node's neighbour vector. Store each nodes connections
	nodeU->addNeighbour(nodeV);
	nodeV->addNeighbour(nodeU);

}
void GeneralMap::draw(Renderer* renderer)
{
	/*ship.draw(renderer);*/

	for (int i = 0; i < numNodes; i++)
	{
		genMapGridVec.at(i)->draw(renderer);
		currentMap->draw(renderer);
	}

}
void GeneralMap::handleInputs(SDL_Event* e)
{
	getCurrentMap()->handleInputs(e);

	for (int i = 0; i < genMapGridVec.size(); i++)
	{
		genMapGridVec.at(i)->handleInputs(e);
		if (genMapGridVec.at(i)->isHovered)
		{
			//display text description of type
		}
		if (genMapGridVec.at(i)->isClicked)
		{
			//if it's a neighbour of current node
			currentMap = locMapVec.at(i);
		}
	}
	//check inputs for current local map
	//	localMapVec.at(i).handleInputs(e);

}
void GeneralMap::setCurrentMap(LocalMap* localMap)
{
	currentMap = localMap;
	//Set ship general position to gen node
	//Set ship local position to start of local Map 
	//ship.setPos();
}