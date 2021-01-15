#include"Node.h"

Node::Node()
{

}
void Node::addNeighbour(Node* neighbour)
{
	neighbours.push_back(neighbour);
}
SDL_Rect Node::toRect()
{
	SDL_Rect rect{ static_cast<int>(pos.getX()), static_cast<int>(pos.getY()),w,h };
	return rect;
}
void Node::handleInputs(SDL_Event* e)
{
	if (e->type == SDL_MOUSEMOTION)
	{
		int xM;
		int yM;
		SDL_GetMouseState(&xM, &yM);
		if (xM > pos.getX() && xM < pos.getX() + w && yM > pos.getY() && yM < pos.getY() + h)
		{
			isHovered = true;
		}
		else
		{
			isHovered = false;
		}
	}
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (isHovered)
		{
			isClicked = true;
			//Check selection process
		}
	}
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		isClicked = false;
	}
}
void Node::draw(Renderer* renderer)
{
	SDL_Rect rect = toRect();

	switch (locType)
	{
	//case Undefined:
	case Start:
	case End:
		renderer->drawRect(rect, 0, 0, 0, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	case Uncharted:
		renderer->drawRect(rect, 0, 0, 255, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	case Civilised:
		renderer->drawRect(rect, 0, 255, 0, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	case Asteroid:
		renderer->drawRect(rect, 255, 0, 0, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	case Stranded:
		renderer->drawRect(rect, 146, 230, 140, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	case Trade:
		renderer->drawRect(rect, 245, 230, 64, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	case Wreck:
		renderer->drawRect(rect, 215, 179, 255, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	case Live:
		renderer->drawRect(rect, 34, 117, 242, 255);
		if (isHovered)
		{
			renderer->drawRectOutline(rect, 255, 255, 255, 255);
		}
		if (isClicked)
		{
			renderer->drawRect(rect, 255, 0, 208, 255);
		}
		break;
	default:
		break;
	}
}
void Node::drawEdges(Renderer* renderer)
{
	for (int i = 0; i < neighbours.size(); i++)
	{
		int x = static_cast<int>(pos.getX());
		int y = static_cast<int>(pos.getY());
		int x2 = static_cast<int>(neighbours.at(i)->getX());
		int y2 = static_cast<int>(neighbours.at(i)->getY());

		SDL_SetRenderDrawColor(renderer->toSDLRenderer(), 0, 0, 0, 0);
		SDL_RenderDrawLine(renderer->toSDLRenderer(), x, y, x2, y2);
	}
}