#pragma once

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include"../../inc/Defines.h"

class GameObject
{
protected:
	Coordinate _pos;
	double _width;
	double _height;
public:
	GameObject(double width = 0.0, double height = 0.0);
	virtual ~GameObject() = default;

	GameObject* SetCoordinate(const Coordinate& coord);
	GameObject* SetX(double x);
	GameObject* SetY(double y);
	GameObject* SetWidth(double width);
	GameObject* SetHeight(double height);

	Coordinate GetCoordinate() const;
	double GetX() const;
	double GetY() const;
	double GetWidth() const;
	double GetHeight() const;

	Rect GetBorder() const;
	virtual void Draw();
};

#endif