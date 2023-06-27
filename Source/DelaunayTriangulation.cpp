#include <regex>
#include <string>
#include <tuple>
#include <vector>
#include "../Header/Triangulation.h"

using namespace std;
using namespace dt;

DelaunayTriangulation::DelaunayTriangulation()
{
    for (int i = 0; i < VERTICES_COUNT; i++)
    {
        _auxiliaryDots[i] = new Vector3D(
            (i % 2 != 0 ? -1 : 1) * (i / 2 == 0 ? VECTOR_LENGTH : 0),
            (i % 2 != 0 ? -1 : 1) * (i / 2 == 1 ? VECTOR_LENGTH : 0),
            (i % 2 != 0 ? -1 : 1) * (i / 2 == 2 ? VECTOR_LENGTH : 0),
            true
        );
    }

    _projectedDots = new vector<Vector3D*>();
    _mesh = new vector<Triangle*>();

}

DelaunayTriangulation::~DelaunayTriangulation()
{
    for (int i = 0; i < VERTICES_COUNT; i++)
    {
        delete _auxiliaryDots[i];
    }

    vector<Vector3D*>::iterator dotsIt;
    for (dotsIt = _projectedDots->begin(); dotsIt != _projectedDots->end(); dotsIt++)
    {
        delete *dotsIt;
    }

    vector<Triangle*>::iterator meshIt;
    for (meshIt = _mesh->begin(); meshIt != _mesh->end(); meshIt++)
    {
        delete *meshIt;
    }

    delete _projectedDots;
    delete _mesh;
}

vector<tuple<int, int, int>*> DelaunayTriangulation::getResult(vector<Vector3D*> &dots)
{

    _projectedDots->reserve(dots.size());

    _mesh->reserve(8 + (dots.size() - 6) * 2);

    vector<Vector3D*>::iterator dotsIt;
    for (dotsIt = dots.begin(); dotsIt != dots.end(); dotsIt++)
    {
        Vector3D* projectedDot = new Vector3D((*dotsIt), VECTOR_LENGTH);
        _projectedDots->push_back(projectedDot);
    }

    buildHull(_projectedDots);

    for (dotsIt = _projectedDots->begin(); dotsIt != _projectedDots->end(); dotsIt++)
    {
        Vector3D* dot = *dotsIt;
        if (!dot->wasLooked)
        {
            insertDot(dot);
        }
    }

    removeSuperTriangles();

    // generate output
    vector<tuple<int, int, int>*> mesh = vector<tuple<int, int, int>*>();
    for (vector<Triangle*>::iterator meshIt = _mesh->begin(); meshIt != _mesh->end(); meshIt++)
    {
        Triangle* tr = *meshIt;
        mesh.push_back(new tuple<int, int, int>(
            tr->Vertex[0]->Id,
            tr->Vertex[1]->Id,
            tr->Vertex[2]->Id
            ));
    }


    return mesh;
}

void DelaunayTriangulation::buildHull(vector<Vector3D*>* dots)
{
    Vector3D* initialVertices[VERTICES_COUNT];
    Triangle* initialHullFaces[FACES_COUNT];

    for (int i = 0; i < VERTICES_COUNT; i++)
    {
        initialVertices[i] = _auxiliaryDots[i];
    }

    double minDistance[VERTICES_COUNT] = { 0, 0, 0, 0, 0, 0 };
    vector<Vector3D*>::iterator it;
    for (it = dots->begin(); it != dots->end(); it++)
    {
        double distance[VERTICES_COUNT];
        for (int i = 0; i < VERTICES_COUNT; i++)
        {
            distance[i] = distanceTo(_auxiliaryDots[i], *it);
            if (minDistance[i] == 0 || distance[i] < minDistance[i])
            {
                minDistance[i] = distance[i];
            }
        }

        for (int i = 0; i < VERTICES_COUNT; i++)
        {
            if (minDistance[i] == distance[i] && isMinimumValueInArray(distance, VERTICES_COUNT, i))
            {
                initialVertices[i] = *it;
            }
        }
    }

    int vertexIndex0[] = { 1, 1, 1, 1, 0, 0, 0, 0 };
    int vertexIndex1[] = { 5, 3, 4, 2, 2, 5, 3, 4 };
    int vertexIndex2[] = { 2, 5, 3, 4, 5, 3, 4, 2 };

    for (int i = 0; i < FACES_COUNT; i++)
    {
        Vector3D* vect0 = initialVertices[vertexIndex0[i]];
        Vector3D* vect1 = initialVertices[vertexIndex1[i]];
        Vector3D* vect2 = initialVertices[vertexIndex2[i]];

        Triangle* tr = new Triangle(vect0, vect1, vect2);
        initialHullFaces[i] = tr;

        _mesh->push_back(tr);
    }

    int neighborIndex0[] = { 1, 2, 3, 0, 7, 4, 5, 6 };
    int neighborIndex1[] = { 4, 5, 6, 7, 0, 1, 2, 3 };
    int neighborIndex2[] = { 3, 0, 1, 2, 5, 6, 7, 4 };

    for (int i = 0; i < FACES_COUNT; i++)
    {
        Triangle* n0 = initialHullFaces[neighborIndex0[i]];
        Triangle* n1 = initialHullFaces[neighborIndex1[i]];
        Triangle* n2 = initialHullFaces[neighborIndex2[i]];
        initialHullFaces[i]->AssignNeighbors(n0, n1, n2);
    }

    for (int i = 0; i < VERTICES_COUNT; i++)
    {
        initialVertices[i]->wasLooked = true;
    }
}

void DelaunayTriangulation::insertDot(Vector3D* dot)
{
    double determ[] = { 0, 0, 0 };

    vector<Triangle*>::iterator it;
    it = _mesh->begin();
    Triangle* tr = *it;

    while (it != _mesh->end())
    {

        determ[0] = getDeterminant(tr->Vertex[0], tr->Vertex[1], dot);
        determ[1] = getDeterminant(tr->Vertex[1], tr->Vertex[2], dot);
        determ[2] = getDeterminant(tr->Vertex[2], tr->Vertex[0], dot);

        if (determ[0] >= 0 && determ[1] >= 0 && determ[2] >= 0)
        {
            if (!tr->HasVertexCoincidentWith(dot))
            {
                splitTriangle(tr, dot);
            }

            return;
        }

        else if (determ[1] >= 0 && determ[2] >= 0)
            tr = tr->Neighbor[0];
        else if (determ[0] >= 0 && determ[2] >= 0)
            tr = tr->Neighbor[1];
        else if (determ[0] >= 0 && determ[1] >= 0)
            tr = tr->Neighbor[2];

        else if (determ[0] >= 0)
            tr = tr->Neighbor[1];
        else if (determ[1] >= 0)
            tr = tr->Neighbor[2];
        else if (determ[2] >= 0)
            tr = tr->Neighbor[0];
        else
            tr = *it++;
    }
}

void DelaunayTriangulation::removeSuperTriangles()
{
    vector<Triangle*>::iterator it;
    for (it = _mesh->begin(); it != _mesh->end();)
    {
        Triangle* tr = *it;
        bool isSuperTriangle = false;
        for (int i = 0; i < 3; i++)
        {
            if (tr->Vertex[i]->isInitDot)
            {
                isSuperTriangle = true;
                break;
            }
        }

        if (isSuperTriangle)
        {
            delete *it;
            it = _mesh->erase(it);
        }
        else
        {
            it++;
        }
    }
}

void DelaunayTriangulation::splitTriangle(Triangle* triangle1, Vector3D* dot)
{
    Triangle* triangle2 = new Triangle(dot, triangle1->Vertex[1], triangle1->Vertex[2]);
    Triangle* triangle3 = new Triangle(dot, triangle1->Vertex[2], triangle1->Vertex[0]);

    triangle1->Vertex[2] = triangle1->Vertex[1];
    triangle1->Vertex[1] = triangle1->Vertex[0];
    triangle1->Vertex[0] = dot;

    triangle2->AssignNeighbors(triangle1, triangle1->Neighbor[1], triangle3);
    triangle3->AssignNeighbors(triangle2, triangle1->Neighbor[2], triangle1);
    triangle1->AssignNeighbors(triangle3, triangle1->Neighbor[0], triangle2);

    fixNeighborhood(triangle2->Neighbor[1], triangle1, triangle2);
    fixNeighborhood(triangle3->Neighbor[1], triangle1, triangle3);

    _mesh->push_back(triangle2);
    _mesh->push_back(triangle3);

    optimize(triangle1, triangle1->Neighbor[1]);
    optimize(triangle2, triangle2->Neighbor[1]);
    optimize(triangle3, triangle3->Neighbor[1]);
}

void DelaunayTriangulation::fixNeighborhood(Triangle* tr, Triangle* oldNeighbor, Triangle* newNeighbor)
{
    for (int i = 0; i < 3; i++)
    {
        if (tr->Neighbor[i] == oldNeighbor)
        {
            tr->Neighbor[i] = newNeighbor;
            break;
        }
    }
}

void DelaunayTriangulation::optimize(Triangle* triangle0, Triangle* triangle1)
{

    for (int i = 0; i < 3; i++)
    {
        if (triangle1->Vertex[i] == triangle0->Vertex[0] ||
            triangle1->Vertex[i] == triangle0->Vertex[1] ||
            triangle1->Vertex[i] == triangle0->Vertex[2])
        {
            continue;
        }

        double matr[] = {
            triangle1->Vertex[i]->X - triangle0->Vertex[0]->X,
            triangle1->Vertex[i]->Y - triangle0->Vertex[0]->Y,
            triangle1->Vertex[i]->Z - triangle0->Vertex[0]->Z,

            triangle1->Vertex[i]->X - triangle0->Vertex[1]->X,
            triangle1->Vertex[i]->Y - triangle0->Vertex[1]->Y,
            triangle1->Vertex[i]->Z - triangle0->Vertex[1]->Z,

            triangle1->Vertex[i]->X - triangle0->Vertex[2]->X,
            triangle1->Vertex[i]->Y - triangle0->Vertex[2]->Y,
            triangle1->Vertex[i]->Z - triangle0->Vertex[2]->Z
        };

        if (getDeterminant(matr) <= 0)
        {
            break;
        }

        if (swapDiagonal(triangle0, triangle1))
        {
            return;
        }
    }
}

bool DelaunayTriangulation::swapDiagonal(Triangle* triangle0, Triangle* triangle1)
{
    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            if (triangle0->Vertex[j] != triangle1->Vertex[0] &&
                triangle0->Vertex[j] != triangle1->Vertex[1] &&
                triangle0->Vertex[j] != triangle1->Vertex[2] &&
                triangle1->Vertex[k] != triangle0->Vertex[0] &&
                triangle1->Vertex[k] != triangle0->Vertex[1] &&
                triangle1->Vertex[k] != triangle0->Vertex[2])
            {
                triangle0->Vertex[(j + 2) % 3] = triangle1->Vertex[k];
                triangle1->Vertex[(k + 2) % 3] = triangle0->Vertex[j];

                triangle0->Neighbor[(j + 1) % 3] = triangle1->Neighbor[(k + 2) % 3];
                triangle1->Neighbor[(k + 1) % 3] = triangle0->Neighbor[(j + 2) % 3];
                triangle0->Neighbor[(j + 2) % 3] = triangle1;
                triangle1->Neighbor[(k + 2) % 3] = triangle0;

                fixNeighborhood(triangle0->Neighbor[(j + 1) % 3], triangle1, triangle0);
                fixNeighborhood(triangle1->Neighbor[(k + 1) % 3], triangle0, triangle1);

                optimize(triangle0, triangle0->Neighbor[j]);
                optimize(triangle0, triangle0->Neighbor[(j + 1) % 3]);
                optimize(triangle1, triangle1->Neighbor[k]);
                optimize(triangle1, triangle1->Neighbor[(k + 1) % 3]);

                return true;
            }
        }
    }

    return false;
}

bool DelaunayTriangulation::isMinimumValueInArray(double arr[], int length, int index)
{
    for (int i = 0; i < length; i++)
    {
        if (arr[i] < arr[index])
        {
            return false;
        }
    }

    return true;
}

double DelaunayTriangulation::distanceTo(Vector3D* vect0, Vector3D* vect1)
{
    return sqrt(pow((vect0->X - vect1->X), 2) +
        pow((vect0->Y - vect1->Y), 2) +
        pow((vect0->Z - vect1->Z), 2));
}

double DelaunayTriangulation::getDeterminant(Vector3D* vect0, Vector3D* vect1, Vector3D* vect2)
{
    double matr[] = {
        vect0->X, vect0->Y, vect0->Z,
        vect1->X, vect1->Y, vect1->Z,
        vect2->X, vect2->Y, vect2->Z
    };

    return getDeterminant(matr);
}

double DelaunayTriangulation::getDeterminant(double matr[])
{
    double determinant = matr[2] * matr[4] * matr[6]
        + matr[0] * matr[5] * matr[7]
        + matr[1] * matr[3] * matr[8]
        - matr[0] * matr[4] * matr[8]
        - matr[1] * matr[5] * matr[6]
        - matr[2] * matr[3] * matr[7];

    return abs(determinant) <= std::numeric_limits<double>::epsilon() ? 0 : determinant;
}