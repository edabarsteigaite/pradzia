#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::left;
using std::right;
using std::sort;

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> namu_darbai;
    int egzamino_rezultatas;
    float galutinisBalas;

};

  

    float galutinisBalas(const Studentas& studentas);
    void rusiavimas(std::vector<Studentas>& studentai);

    void generavimas(std::vector<Studentas>& studentai, int count, const std::string& failas);
    void saugojimas(const std::string& failas, const std::vector<Studentas>& studentai);
    void skaitymas(std::vector<Studentas>& studentai, const std::string& pav);

    void rusiavimas_pagal_balus(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakai);
    void isvedimas_vargsiukai(const std::string& failas_vargsiukai, const std::vector<Studentas>& vargsiukai);
    void isvedimas_kietiakai(const std::string& failas_kietiakai, const std::vector<Studentas>& kietiakai);

    void generavimo_laikas(std::vector<Studentas>& studentai, int skaicius, const std::string& failas);
    void skaitymo_laikas(std::vector<Studentas>& studentai, int skaicius, const std::string& failas);
    void rusiavimo_laikas(std::vector<Studentas>& studentai, int skaicius, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakai);
    void isvedimo_vargsiukai_laikas(const std::string& failas_vargsiukai, int skaicius, const std::vector<Studentas>& vargsiukai);
    void isvedimo_kietiakai_laikas(const std::string& failas_kietiakai, int skaicius, const std::vector<Studentas>& kietiakai);

    void testavimas(const std::string& failoPav, int skaicius, const std::string& kietiakaiF, const std::string& vargsiukaiF);


#endif

