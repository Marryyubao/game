#pragma once

#ifndef _DEFINES_H_
#define _DEFINES_H_

#include<easyx.h>

class Vector
{
public:
	Vector() : x(0.0), y(0.0) {}
	Vector(double _x, double _y) :x(_x), y(_y) {}
	double getx() const
	{
		return x;
	}
	double gety() const
	{
		return y;
	}
	void givex(double _x)
	{
		x = _x;
	}
	void givey(double _y)
	{
		y = _y;
	}
	Vector operator+(const Vector& obj) const
	{
		return { x + obj.x,y + obj.y };
	}
private:
	double x;
	double y;

	bool operator==(const Vector& obj) const
	{
		return x == obj.x && y == obj.y;
	}

	bool operator!=(const Vector& obj) const
	{
		return !(*this == obj);
	}



	Vector operator-(const Vector& obj) const
	{
		return { x - obj.x,y - obj.y };
	}

	Vector operator-() const
	{
		return { -x,-y };
	}

	friend Vector operator*(const Vector& obj, double r)
	{
		return { obj.x * r,obj.y * r };
	}

	friend Vector operator*(double r, const Vector& obj)
	{
		return { obj.x * r,obj.y * r };
	}

	friend Vector operator/(const Vector& obj, double r)
	{
		return { obj.x / r,obj.y / r };
	}

	friend Vector operator/(double r, const Vector& obj)
	{
		return { obj.x / r,obj.y / r };
	}

};

using Coordinate = Vector;

class Rect
{
public:
	Rect() :x(0.0), y(0.0), width(0.0), height(0.0) {}
	Rect(double _x, double _y, double _w, double _h) :x(_x), y(_y), width(_w), height(_h) {}

	union
	{
		Coordinate position;
		struct { double x; double y; };
	};
	double width;
	double height;

	Coordinate GetCenter() const
	{
		return { x + width * 0.5,y + height * 0.5 };
	}

	Coordinate Intersect(const Rect& rect) const
	{
		Coordinate overlap;
		if (this->x < rect.x)
		{
			overlap.givex(this->x + this->width - rect.x);
		}
		else
		{
			overlap.givex(rect.x + rect.width - this->x);
		}
		if (this->y < rect.y)
		{
			overlap.givey(this->y + this->height - rect.y);
		}
		else
		{
			overlap.givey(rect.y + rect.height - this->y);
		}
		return overlap;
	}

	bool Contains(const Coordinate& coord) const
	{
		return ((x < coord.getx() && coord.getx() < x + width) && (y < coord.gety() && coord.gety() < y + height));
	}

	RECT ToEasyXRect() const
	{
		return{ (LONG)x, (LONG)y, (LONG)(x + width), (LONG)(y + height) };
	}
};

#endif
