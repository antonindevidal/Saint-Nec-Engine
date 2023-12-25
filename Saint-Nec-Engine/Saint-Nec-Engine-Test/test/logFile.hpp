#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

std::ofstream open(const std::string &filename)
{
    std::ofstream myfile;
    myfile.open(filename);
    return myfile;
}

void schriben(std::ofstream &ofs, const glm::vec3 &v)
{
    ofs << "(" << v[0] << "," << v[1] << "," << v[2] << ")\n";
}