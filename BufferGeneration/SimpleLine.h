#pragma once

#include "Vector.h"

class StraightLine;

class SimpleLine
{
public:
	double startX;
	double startY;
	double endX;
	double endY;

public:
	SimpleLine();
	SimpleLine(double startX, double startY, double endX, double endY);
	SimpleLine(const Vector& startPoint, const Vector& endPoint);
	SimpleLine(const SimpleLine& sl);

	double GetSlopes() const;
	StraightLine ToStraightLine() const;
	/// <summary>
	/// 往左侧平移
	/// </summary>
	SimpleLine TranslationLeft(double dis);
	/// <summary>
	/// 往右侧平移
	/// </summary>
	SimpleLine TranslationRight(double dis);
};

