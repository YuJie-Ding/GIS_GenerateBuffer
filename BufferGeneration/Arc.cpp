#include "Arc.h"
#include "SimpleLine.h"

Arc::Arc()
{
	startX = startY = endX = endY = circleCenterX = circleCenterY = 0;
}

Arc::Arc(double startX, double startY, double endX, double endY, double circleCenterX, double circleCenterY)
{
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	this->circleCenterX = circleCenterX;
	this->circleCenterY = circleCenterY;
}

Arc::Arc(const Vector& stratPoint, const Vector& endPoint, double circleCenterX, double circleCenterY)
{
	this->startX = stratPoint.x;
	this->startY = stratPoint.y;
	this->endX = endPoint.x;
	this->endY = endPoint.y;
	this->circleCenterX = circleCenterX;
	this->circleCenterY = circleCenterY;
}

Arc::Arc(double startAngle, double endAngle, double radius, double circleCenterX, double circleCenterY)
{
	startAngle = fmod(startAngle, 360.0);
	endAngle = fmod(endAngle, 360.0);
	double startRadians = Utils::Angle2Radians(startAngle);
	double endRadians = Utils::Angle2Radians(endAngle);
	double startPointOffsetX = radius * cos(startRadians);
	double startPointOffsetY = radius * sin(startRadians);
	double endPointOffsetX = radius * cos(endRadians);
	double endPointOffsetY = radius * sin(endRadians);
	startX = circleCenterX + startPointOffsetX;
	startY = circleCenterY + startPointOffsetY;
	endX = circleCenterX + endPointOffsetX;
	endY = circleCenterY + endPointOffsetY;
	this->circleCenterX = circleCenterX;
	this->circleCenterY = circleCenterY;
}

double Arc::GetStartAngle() const
{
	SimpleLine line = { circleCenterX, circleCenterY, startX, startY };
	Vector c2p = { startX - circleCenterX, startY - circleCenterY };
	double slopes = line.GetSlopes();
	if (isnan(slopes))
	{
		if (c2p.y > 0)
			return 90;
		else
			return -90;
	}
	else
	{
		double radians = atan(slopes);
		double angles = Utils::Radians2Angle(radians);
		if (c2p.x > 0)
			return angles;
		else
			return angles + 180;
	}
}

double Arc::GetEndAngle() const
{
	SimpleLine line = { circleCenterX, circleCenterY, endX, endY };
	Vector c2p = { endX - circleCenterX, endY - circleCenterY };
	double slopes = line.GetSlopes();
	if (isnan(slopes))
	{
		if (c2p.y > 0)
			return 90;
		else
			return -90;
	}
	else
	{
		double radians = atan(slopes);
		double angles = Utils::Radians2Angle(radians);
		if (c2p.x > 0)
			return angles;
		else
			return angles + 180;
	}
}

Vector Arc::GetPointFromAngle(double angle) const
{
	angle = fmod(angle, 360);
	
	double radians = Utils::Angle2Radians(angle);
	double radius = GetRadius();
	double XOffset = cos(radians) * radius;
	double YOffset = sin(radians) * radius;
	return Vector(circleCenterX + XOffset, circleCenterY + YOffset);
}

double Arc::GetRadius() const
{
	return Vector(startX - circleCenterX, startY - circleCenterY).GetLength();
}

std::vector<Vector> Arc::DivideArc(int num, bool flag)
{
	std::vector<Vector> Points;
	double startAngle = GetStartAngle();
	double endAngle = GetEndAngle();
	startAngle = fmod(startAngle, 360.0);
	endAngle = fmod(endAngle, 360.0);
	
	if (flag == false) // 逆时针
	{
		if (endAngle < startAngle)
			endAngle += 360;
		double gap = (endAngle - startAngle) / num;
		for (double angle = startAngle; angle < endAngle || Utils::IsDoubleEqual(angle, endAngle); angle += gap)
		{
			Points.push_back(GetPointFromAngle(angle));
		}
	}
	else // 顺时针
	{
		if (endAngle > startAngle)
			startAngle += 360;
		double gap = (startAngle - endAngle) / num;
		for (double angle = endAngle; angle < startAngle || Utils::IsDoubleEqual(angle, startAngle); angle += gap)
		{
			Points.push_back(GetPointFromAngle(angle));
		}
		std::reverse(Points.begin(), Points.end());
	}

	return Points;	
}

