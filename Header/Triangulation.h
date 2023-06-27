#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#define VERTICES_COUNT 6
#define FACES_COUNT 8
#define VECTOR_LENGTH 1

#include "DataStructure.h"
#include <vector>
#include <tuple>

namespace dt
{
    class DelaunayTriangulation
    {
    private:
        Vector3D * _auxiliaryDots[VERTICES_COUNT];
        std::vector<Vector3D*>* _projectedDots;
        std::vector<Triangle*>* _mesh;

        void buildHull(std::vector<Vector3D*>* dots);
        void insertDot(Vector3D* dot);
        void removeSuperTriangles();
        void splitTriangle(Triangle* triangle1, Vector3D* dot);
        void fixNeighborhood(Triangle* tr, Triangle* oldNeighbor, Triangle* newNeighbor);
        void optimize(Triangle* triangle0, Triangle* triangle1);
        bool swapDiagonal(Triangle* triangle0, Triangle* triangle1);
        bool isMinimumValueInArray(double arr[], int length, int index);
        double distanceTo(Vector3D* vect0, Vector3D* vect1);
        double getDeterminant(Vector3D* vect0, Vector3D* vect1, Vector3D* vect2);
        double getDeterminant(double matr[]);

    public:
        DelaunayTriangulation();
        ~DelaunayTriangulation();

        std::vector<std::tuple<int, int, int>*> getResult(std::vector<Vector3D*> &dots);
    };
}

#endif