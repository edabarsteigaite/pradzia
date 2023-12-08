#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

struct StudentasV {
    std::string vardas;
    std::string pavarde;
    std::vector<int> namu_darbai;
    int egzamino_rezultatas;
    float galutinisBalas;
};

struct StudentasL {
    std::string vardas;
    std::string pavarde;
    std::list<int> namu_darbai;
    int egzamino_rezultatas;
    float galutinisBalas;
};

#endif
