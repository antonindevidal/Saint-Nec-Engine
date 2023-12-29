#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const std::string path = "../../../Saint-Nec-Engine/Saint-Nec-Engine-Test/test/data/";

std::ofstream open(const std::string &filename)
{
    std::ofstream myfile(path +filename);
    if (!myfile.is_open()) {
        std::cout << "Unable to open file: " << filename << std::endl;
    }

    return myfile;
}

void schriben(std::ofstream &ofs, const glm::vec3 &v)
{
    ofs << "(" << v[0] << "," << v[1] << "," << v[2] << ")\n";
}