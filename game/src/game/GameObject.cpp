#include"../../inc/game/GameObject.h"

GameObject::GameObject(double width, double height) :_width(width), _height(height) {}

GameObject* GameObject::SetCoordinate(const Coordinate& coord)
{
	_pos = coord;
	return this;
}
GameObject* GameObject::SetX(double x)
{
	_pos.givex(x);
	return this;
}
GameObject* GameObject::SetY(double y)
{
	_pos.givey(y);
	return this;
}
GameObject* GameObject::SetWidth(double width)
{
	_width = width;
	return this;
}
GameObject* GameObject::SetHeight(double height)
{
	_height = height;
	return this;
}

Rect GameObject::GetBorder() const
{
	return Rect(_pos.getx(), _pos.gety(), _width, _height);
}

Coordinate GameObject::GetCoordinate() const
{
	return _pos;
}

double GameObject::GetX() const
{
	return _pos.getx();
}
double GameObject::GetY() const
{
	return _pos.gety();
}
double GameObject::GetWidth() const
{
	return _width;
}
double GameObject::GetHeight() const
{
	return _height;
}

void GameObject::Draw()
{

}

