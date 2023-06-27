#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "DataStructure.h"

namespace dt
{
    class Visualization
    {
    public:

        Visualization();
        ~Visualization();

        void visualize(std::vector<Vector3D*> &dots, std::vector<std::tuple<int, int, int>*> &mesh);

    };
}

#endif