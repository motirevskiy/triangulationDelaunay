#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

namespace dt
{
    class Vector3D
    {
    private:
        int GenerateRunningId();
    public:
        int Id = 0;

        double X, Y, Z;


        bool wasLooked = false;
        bool isInitDot = false;

        Vector3D(double x, double y, double z);
        Vector3D(double x, double y, double z, bool isInitDot);
        Vector3D(Vector3D* dot, double lengthAfterProjection);
        ~Vector3D();

        bool IsCoincidentWith(Vector3D* dot);
    };

    class Triangle
    {
    private:
        int GenerateRunningId();
    public:
        int Id = 0;

        Vector3D* Vertex[3];

        Triangle* Neighbor[3];

        Triangle(Vector3D* v0, Vector3D* v1, Vector3D* v2);
        ~Triangle();

        bool HasVertexCoincidentWith(Vector3D* dot);
        void AssignNeighbors(Triangle* n0, Triangle* n1, Triangle* n2);
    };
}

#endif