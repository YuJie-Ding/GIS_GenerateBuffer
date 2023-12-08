#pragma once

#include "Vector.h"
#include <vector>

class Arc
{
public:
	double startX;
	double startY;
	double endX;
	double endY;
	double circleCenterX;
	double circleCenterY;

public:
	Arc();
	Arc(double startX, double startY, double endX, double endY, double circleCenterX, double circleCenterY);
	Arc(const Vector& stratPoint, const Vector& endPoint, double circleCenterX, double circleCenterY);
	Arc(double startAngle, double endAngle, double radius, double circleCenterX, double circleCenterY);

	double GetStartAngle() const;
	double GetEndAngle() const;
	Vector GetPointFromAngle(double angle) const;
	double GetRadius() const;
	/// <summary>
	/// 分割弧段，顺序是从startPoint到endPoint，默认逆时针方向
	/// </summary>
	/// <param name="num">段数</param>
	/// <param name="flag">flag==true表示顺时针， flag==false表示逆时针</param>
	/// <returns></returns>
	std::vector<Vector> DivideArc(int num, bool flag = false);
};

