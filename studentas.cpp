#include "studentas.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

int generuotiAtsitiktiniBalai(int min, int max) {
    return rand() % (max - min + 1) + min;
}
bool lyginimasPagalVardus(const Studentas& a, const Studentas& b) {
    if (a.vardas == b.vardas) {
        return a.pavarde < b.pavarde;
    }
    return a.vardas < b.vardas;
}

double skaiciuotiGalutiniVidurki(const std::vector<int>& namu_darbai, int egzamino_rezultatas) {
    double namuDarbuVidurkis = 0.0;
    if (!namu_darbai.empty()) {
        for (int rezultatas : namu_darbai) {
            namuDarbuVidurkis += rezultatas;
        }
        namuDarbuVidurkis /= namu_darbai.size();
    }
    return 0.4 * namuDarbuVidurkis + 0.6 * egzamino_rezultatas;
}

double skaiciuotiGalutiniMediana(const std::vector<int>& namu_darbai, int egzamino_rezultatas) {
    std::vector<int> surikiuoti_namu_darbai = namu_darbai;
    std::sort(surikiuoti_namu_darbai.begin(), surikiuoti_namu_darbai.end());

    if (surikiuoti_namu_darbai.size() % 2 == 0) {
        int vidurinis1 = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2 - 1];
        int vidurinis2 = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2];
        double mediana = (vidurinis1 + vidurinis2) / 2.0;
        return 0.4 * mediana + 0.6 * egzamino_rezultatas;
    }
    else {
        int vidurinis = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2];
        return 0.4 * vidurinis + 0.6 * egzamino_rezultatas;
    }
}

void skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai) {
    std::ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        throw std::runtime_error("Klaida: Nepavyko atidaryti failo " + failoPavadinimas);
    }

    std::string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        std::istringstream iss(eilute);
        Studentas naujasStudentas;

        iss >> naujasStudentas.vardas >> naujasStudentas.pavarde;
        int balas;

        while (iss >> balas) {
            naujasStudentas.namu_darbai.push_back(balas);
        }

        if (naujasStudentas.namu_darbai.size() > 0) {
            naujasStudentas.egzamino_rezultatas = naujasStudentas.namu_darbai.back();
            naujasStudentas.namu_darbai.pop_back();
        }

        studentai.push_back(naujasStudentas);
    }

    failas.close();
}
