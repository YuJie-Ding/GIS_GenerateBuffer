#pragma once

#include "SimpleLine.h"

class StraightLine
{
public:
	double A;
	double B;
	double C;

public:
	StraightLine();
	StraightLine(double A, double B, double C);
	StraightLine(double slopes, double yIntercept);
	StraightLine(const Vector& p1, const Vector& p2);
	StraightLine(const SimpleLine& sl);

	double GetSlopes() const;

	static bool IsParallel(const StraightLine& l1, const StraightLine& l2);
};

