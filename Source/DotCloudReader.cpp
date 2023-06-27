#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <iomanip>
#include "../Header/DotCloud.h"
#include <ctype.h>

using namespace std;
using namespace dt;

vector<Vector3D*> DotCloudReader::GetDotCloud(std::string filename)
{
    vector<Vector3D*> dots = vector<Vector3D*>();
    ifstream file(filename);

    double x = 0, y = 0, z = 0;
    int red = 0, green = 0, blue = 0;

    string line;
    string s;

    while (getline(file, line))
    {
        if (line[0] == '*' || line.empty()) {
            continue;
        }

        size_t pos = line.find(',');
        if (pos == std::string::npos) {
            continue;
        }

        x = stod(line.substr(pos + 1));
        line = line.substr(pos + 1);
        pos = line.find(',');
        if (pos == std::string::npos) {
            continue;
        }
        y = stod(line.substr(pos + 1));
        line = line.substr(pos + 1);
        pos = line.find(',');
        if (pos == std::string::npos) {
            continue;
        }
        z = stod(line.substr(pos + 1));

        Vector3D* dot = new Vector3D(x, y, z, (uint8_t)red, (uint8_t)green, (uint8_t)blue);
        dots.push_back(dot);
    }

    file.close();

    return dots;
}

void DotCloudReader::writeToFile(std::vector<std::tuple<int, int, int>*> mesh, std::vector<Vector3D*> dots, std::string filename) {
    ofstream file(filename);
    int counter = 1;
    if (file.is_open()) {
        file << "*" << setw(5) << "N," << setw(13) << "X" << setw(14) << "Y" << setw(14) << "Z" << endl;
        file << "*Nodes" << endl;
        for (auto &nodes : dots) {
            file << setw(5) << counter << "," << setw(13) << nodes->X << "," << setw(13) << nodes->Y << "," << setw(13) << nodes->Z << endl;
            counter++;
        }
        file << "*Elements\n";
        counter = 1;
        for (auto &triangle : mesh) {
            file << setw(5) << counter << "," << setw(13) << get<0>(*triangle) << "," << setw(13) << get<1>(*triangle) << "," << setw(13) << get<2>(*triangle) << endl;
            counter++;
        }
        file.close();
    } else {
        cout << "error" << endl;
    }
}