#define VISUAL
#include <iostream>
#include <string>
#include <vector>
#include "Header/DotCloud.h"
#include "Header/Triangulation.h"
#ifdef VISUAL
#include "Header/Visualization.h"
#endif

using namespace std;
using namespace dt;

void ClearMemory(vector<Vector3D*>&, vector<tuple<int, int, int>*>&);
vector<string> parseArgs(int argc, char **argv);

int main(int argc, char **argv)
{
    vector<string> files = parseArgs(argc, argv);
    if (files.empty()) return 1;
    try
    {
        int cmd = 2;

        vector<Vector3D*> dots
            = cmd == 1
            ? DotCloudGenerator().GetSphericalDots()
            : DotCloudReader().GetDotCloud(files[1]);

        DelaunayTriangulation triangulation = DelaunayTriangulation();
        vector<tuple<int, int, int>*> mesh = triangulation.GetTriangulationResult(dots);
#ifdef VISUAL
        Visualization visualization = Visualization(false);
        visualization.ReconstructIn3D(dots, mesh);
#endif

        DotCloudReader().writeToFile(mesh, dots, files[0]);

        ClearMemory(dots, mesh);
    }
    catch (exception e)
    {
        cout << e.what() << endl;
        system("pause");
    }

    return 0;
}

void ClearMemory(vector<Vector3D*> &dots, vector<tuple<int, int, int>*> &mesh)
{
    vector<Vector3D*>::iterator itDots;
    for (itDots = dots.begin(); itDots != dots.end(); itDots++)
    {
        delete *itDots;
    }

    vector<tuple<int, int, int>*>::iterator itMesh;
    for (itMesh = mesh.begin(); itMesh != mesh.end(); itMesh++)
    {
        delete *itMesh;
    }
}

vector<string> parseArgs(int argc, char **argv) {
    vector<string> files;
    if (argc != 5) return {};
    else {
        string outputFile;
        string inputFile;
        for (int i = 1; i < 5; i++) {
            if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
                if (i + 1 < argc) outputFile = string(argv[i + 1]);
            } else if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")) {
                if (i + 1 < argc) inputFile = string(argv[i + 1]);
            }
        }
        if (!outputFile.empty() && !inputFile.empty()) {
            files.push_back(outputFile);
            files.push_back(inputFile);
        } else {
            return {};
        }
    }
    return files;
}