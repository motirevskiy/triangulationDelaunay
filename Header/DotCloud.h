#ifndef DOTCLOUD_H
#define DOTCLOUD_H
#include "DataStructure.h"

namespace dt
{
    class DotCloudGenerator
    {
    private:
        Vector3D* GetRandomDot();
        Vector3D* GetRandomDotEvenlyDistributed();
    public:
        std::vector<Vector3D*> GetSphericalDots();
    };

    class DotCloudReader
    {
    public:
        std::vector<Vector3D*> GetDotCloud(std::string filename);
        void writeToFile(std::vector<std::tuple<int, int, int>*> mesh, std::vector<Vector3D*> dots, std::string filename);
    };
}

#endif