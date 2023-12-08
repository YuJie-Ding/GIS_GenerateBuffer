#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <istream>
#include <sstream>
#include <stdexcept>

#include "Utils.h"
#include "Vector.h"
#include "SimpleLine.h"
#include "StraightLine.h"
#include "Arc.h"

std::vector<Vector> ReadDataFromFile()
{
	std::string filePath = "./nanjing-polygon-points-simple.txt";
	std::ifstream inFile;
	inFile.open(filePath, std::ios::in);
	if (!inFile.is_open())
		throw "open file failed";
	std::string line;
	std::vector<Vector> result;
	while (std::getline(inFile, line))
	{
		std::istringstream tempStringStream(line);
		std::string coordX;
		std::string coordY;
		std::getline(tempStringStream, coordX, ',');
		std::getline(tempStringStream, coordY, ',');
		double X = atof(coordX.c_str());
		double Y = atof(coordY.c_str());
		result.push_back({ X,Y });
	}
	inFile.close();
	return result;
}

int main()
{
	std::vector<Vector> Points = ReadDataFromFile();
	//std::vector<Vector> Points;
	//Points.push_back(Vector{ 3, 3 });
	//Points.push_back(Vector{ 4, 4 });
	//Points.push_back(Vector{ 5, 4 });
	//Points.push_back(Vector{ 5, 5 });
	//Points.push_back(Vector{ 6, 5 });
	//Points.push_back(Vector{ 8, 5 });
	//Points.push_back(Vector{ 8, 8 });
	//Points.push_back(Vector{ 9, 9 });
	//Points.push_back(Vector{ 10, 10 });

	std::vector<Vector> leftPoints;
	std::vector<Vector> rightPoints;

	double bufferDis = 0.001;

	for (int i = 2; i <= Points.size() - 1; i++)
	{
		Vector* P1 = &Points[i - 2];
		Vector* P2 = &Points[i - 1];
		Vector* P3 = &Points[i];
		SimpleLine srcLine_1 = SimpleLine(*P1, *P2);
		SimpleLine srcLine_2 = SimpleLine(*P2, *P3);
		Vector v1 = *P2 - *P1;
		Vector v2 = *P3 - *P2;
		double cross = Vector::Cross(v1, v2);

		SimpleLine leftLine1 = srcLine_1.TranslationLeft(bufferDis);
		SimpleLine rightLine1 = srcLine_1.TranslationRight(bufferDis);
		SimpleLine leftLine2 = srcLine_2.TranslationLeft(bufferDis);
		SimpleLine rightLine2 = srcLine_2.TranslationRight(bufferDis);

		if (i == 2)
		{
			Arc startArc = { leftLine1.startX, leftLine1.startY, rightLine1.startX, rightLine1.startY, P1->x, P1->y };
			std::vector<Vector> startArcPoints = startArc.DivideArc(10);
			for (const Vector& point : startArcPoints)
			{
				rightPoints.push_back(point);
			}
		}

		if (Utils::IsDoubleEqual(cross, 0.0)) // 共线
		{
			leftPoints.push_back(Vector{ leftLine1.endX, leftLine1.endY });
			rightPoints.push_back(Vector{ rightLine1.endX, rightLine1.endY });
		}
		else if (cross > 0) // 左拐
		{
			Vector inner_IntersectPoint = Utils::Intersect(leftLine1, leftLine2);
			leftPoints.push_back(inner_IntersectPoint);
			Arc outerArc = Arc(rightLine1.endX, rightLine1.endY, rightLine2.startX, rightLine2.startY, P2->x, P2->y);
			std::vector<Vector> pointsOfArcDivide = outerArc.DivideArc(10);
			for (const Vector& point : pointsOfArcDivide)
			{
				rightPoints.push_back(point);
			}
		}
		else // 右拐
		{
			Vector inner_IntersectPoint = Utils::Intersect(rightLine1, rightLine2);
			rightPoints.push_back(inner_IntersectPoint);
			Arc outerArc = Arc(leftLine1.endX, leftLine1.endY, leftLine2.startX, leftLine2.startY, P2->x, P2->y);
			std::vector<Vector> pointsOfArcDivide = outerArc.DivideArc(10, true);
			for (const Vector& point : pointsOfArcDivide)
			{
				leftPoints.push_back(point);
			}
		}

		if (i == Points.size() - 1)
		{
			Arc endArc = { rightLine2.endX, rightLine2.endY, leftLine2.endX, leftLine2.endY, P3->x, P3->y };
			std::vector<Vector> endArcPoints = endArc.DivideArc(10);
			for (const Vector& point : endArcPoints)
			{
				rightPoints.push_back(point);
			}
		}
	}

	std::ofstream outFile;
	outFile.precision(10);
	outFile.open("BufferPoints.txt", std::ios::out);
	for (const Vector& point : rightPoints)
	{
		outFile << point.x << "," << point.y << std::endl;
	}
	for (auto point = leftPoints.rbegin(); point != leftPoints.rend(); point++)
	{
		outFile << point->x << "," << point->y << std::endl;
	}
	return 0;
}