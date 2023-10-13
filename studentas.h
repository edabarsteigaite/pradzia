#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> namu_darbai;
    int egzamino_rezultatas;

    Studentas() : egzamino_rezultatas(0) {}

};

double skaiciuotiGalutiniVidurki(const std::vector<int>& namu_darbai, int egzamino_rezultatas);
double skaiciuotiGalutiniMediana(const std::vector<int>& namu_darbai, int egzamino_rezultatas);
void skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);
bool lyginimasPagalVardus(const Studentas& a, const Studentas& b);

#endif
