#pragma once
#include <cmath>

class SimpleLine;
class StraightLine;
class Vector;

class Utils
{
	static const double threshold;
	static const double PI;
public:
	static bool IsDoubleEqual(double a, double b);
	static Vector Intersect(SimpleLine l1, SimpleLine l2);
	static Vector Intersect(StraightLine l1, StraightLine l2);
	static double Angle2Radians(double angle);
	static double Radians2Angle(double radians);
};
