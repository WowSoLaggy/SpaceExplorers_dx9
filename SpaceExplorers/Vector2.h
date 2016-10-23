#pragma once

#ifndef INC_VECTOR2_H
#define INC_VECTOR2_H


class Vector2
{
public:

	Vector2(int pX, int pY)
		: x(pX), y(pY) { }

	Vector2(float pX, float pY)
		: x((int)pX), y((int)pY) { }

	int x;
	int y;


	static Vector2 Empty() { return Vector2(0, 0); }

};


#endif // INC_VECTOR2_H
