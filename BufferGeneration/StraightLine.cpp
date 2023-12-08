#include "StraightLine.h"
#include <stdexcept>

StraightLine::StraightLine()
{
	A = B = C = 0;
}

StraightLine::StraightLine(double A, double B, double C)
{
	this->A = A;
	this->B = B;
	this->C = C;
}

StraightLine::StraightLine(double slopes, double yIntercept)
{
	if (isnan(slopes))
		throw std::logic_error("slopes is NAN!!");
	A = slopes;
	B = -1;
	C = yIntercept;
}

StraightLine::StraightLine(const Vector& p1, const Vector& p2)
{
	A = p2.y - p1.y;
	B = p1.x - p2.x;
	C = p2.x * p1.y - p1.x * p2.y;
}

StraightLine::StraightLine(const SimpleLine& sl)
{
	A = sl.endY - sl.startY;
	B = sl.startX - sl.endX;
	C = sl.endX * sl.startY - sl.startX * sl.endY;
	if(Utils::IsDoubleEqual(A, 0.0) && Utils::IsDoubleEqual(B, 0.0))
		throw std::logic_error("Can not construct StraightLine from SimpleLine");
}

double StraightLine::GetSlopes() const
{
	if (Utils::IsDoubleEqual(B, 0))
		return NAN;
	else
		return -A / B;
}

bool StraightLine::IsParallel(const StraightLine& l1, const StraightLine& l2)
{
	if (Utils::IsDoubleEqual(l1.A * l2.B, l1.B * l2.A))
		return true;
	else
		return false;
}
