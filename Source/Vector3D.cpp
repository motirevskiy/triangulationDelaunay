#include <cmath>
#include <string>
#include "../Header/DataStructure.h"

using namespace std;
using namespace dt;

Vector3D::Vector3D(double x, double y, double z)
{
    Id = GenerateRunningId();

    X = x;
    Y = y;
    Z = z;
}

Vector3D::Vector3D(double x, double y, double z, bool isAuxiliaryDot)
{
    Id = GenerateRunningId();

    IsAuxiliaryDot = isAuxiliaryDot;

    X = x;
    Y = y;
    Z = z;
}

Vector3D::Vector3D(Vector3D* dot, double lengthAfterProjection)
{
    Id = dot->Id;
    IsVisited = dot->IsVisited;
    IsAuxiliaryDot = dot->IsAuxiliaryDot;

    double length = sqrt(pow(dot->X, 2) + pow(dot->Y, 2) + pow(dot->Z, 2));
    double scaleFactor = lengthAfterProjection / length;

    X = scaleFactor * dot->X;
    Y = scaleFactor * dot->Y;
    Z = scaleFactor * dot->Z;
}

Vector3D::~Vector3D()
{
}

int Vector3D::GenerateRunningId()
{
    static int id = 0;
    return id++;
}

bool Vector3D::IsCoincidentWith(Vector3D* dot)
{
    return (X == dot->X && Y == dot->Y && Z == dot->Z);
}
