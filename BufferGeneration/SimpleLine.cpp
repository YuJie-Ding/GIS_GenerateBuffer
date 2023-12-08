#include "SimpleLine.h"
#include "StraightLine.h"

SimpleLine::SimpleLine()
{
	startX = startY = endX = endY = 0;
}

SimpleLine::SimpleLine(double startX, double startY, double endX, double endY)
{
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
}

SimpleLine::SimpleLine(const Vector& startPoint, const Vector& endPoint)
{
	this->startX = startPoint.x;
	this->startY = startPoint.y;
	this->endX = endPoint.x;
	this->endY = endPoint.y;
}

SimpleLine::SimpleLine(const SimpleLine& sl)
{
	this->startX = sl.startX;
	this->startY = sl.startY;
	this->endX = sl.endX;
	this->endY = sl.endY;
}

double SimpleLine::GetSlopes() const
{
	double denominator = endX - startX;
	if (Utils::IsDoubleEqual(denominator, 0.0))
		return NAN;
	else
		return (endY - startY) / denominator;
}

StraightLine SimpleLine::ToStraightLine() const
{
	return StraightLine(*this);
}

SimpleLine SimpleLine::TranslationLeft(double dis)
{
	Vector vectorOfSimpleLine = Vector(endX - startX, endY - startY);
	Vector leftVec = Vector(-vectorOfSimpleLine.y, vectorOfSimpleLine.x).Normalize(); // 往左侧旋转90°
	double offsetX = dis * leftVec.x;
	double offsetY = dis * leftVec.y;
	return SimpleLine(startX + offsetX, startY + offsetY, endX + offsetX, endY + offsetY);
}

SimpleLine SimpleLine::TranslationRight(double dis)
{
	Vector vectorOfSimpleLine = Vector(endX - startX, endY - startY);
	Vector rightVec = Vector(vectorOfSimpleLine.y, -vectorOfSimpleLine.x).Normalize(); // 往右侧旋转90°
	double offsetX = dis * rightVec.x;
	double offsetY = dis * rightVec.y;
	return SimpleLine(startX + offsetX, startY + offsetY, endX + offsetX, endY + offsetY);
}
