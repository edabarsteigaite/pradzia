#include "studentas.h"
#include "studentas_list.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <numeric>

using namespace std;

void generavimas_list(list < StudentasL > & studentaiL, int count, const string& failas) {
    studentaiL.clear();
    srand(time(nullptr));

    for (int i = 1; i <= count; i++) {
        StudentasL studentas;
        studentas.vardas = "Vardas" + to_string(i);
        studentas.pavarde = "Pavarde" + to_string(i);
        for (int j = 0; j < 10; j++) {
            studentas.namu_darbai.push_back(rand() % 10 + 1);
        }
        studentas.egzamino_rezultatas = rand() % 10 + 1;
        studentaiL.push_back(studentas);
    }

    ofstream F(failas);
    if (!F) {
        cerr << "Nepavyko atidaryti failo " << failas << endl;
        return;
    }

    F << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= 10; i++) {
        F << setw(4) << "ND" + to_string(i);
    }
    F << setw(8) << "Egzaminas" << endl;

    for (const StudentasL& studentas : studentaiL) {
        F << setw(15) << studentas.vardas << " " << setw(15) << studentas.pavarde;
        for (int pazymys : studentas.namu_darbai) {
            F << setw(4) << pazymys;
        }
        F << setw(8) << studentas.egzamino_rezultatas << endl;
    }

    F.close();
}


void saugojimas_list(const string& failas, const list<StudentasL>& studentaiL) {
    ofstream file(failas);
    if (!file) {
        cerr << "Failed to open file " << failas << endl;
        return;
    }

    file << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << endl;

    for (const StudentasL& studentas : studentaiL) {
        file << setw(15) << studentas.vardas << " " << setw(15) << studentas.pavarde << endl;
    }

    file.close();
}



void skaitymas_list(list<StudentasL>& studentaiL, const string& pav) {
    ifstream F(pav);

    try {
        if (!F) {
            throw runtime_error("Failas neegzistuoja: " + pav);
        }

        string line;
        bool firstLine = true;
        while (getline(F, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            istringstream iss(line);
            StudentasL studentas;
            iss >> studentas.vardas >> studentas.pavarde;
            for (int i = 0; i < 10; i++) {
                int pazymys;
                iss >> pazymys;
                studentas.namu_darbai.push_back(pazymys);
            }
            iss >> studentas.egzamino_rezultatas;

            float vidurkis = accumulate(studentas.namu_darbai.begin(), studentas.namu_darbai.end(), 0.0) / studentas.namu_darbai.size();
            studentas.galutinisBalas = 0.4 * vidurkis + 0.6 * studentas.egzamino_rezultatas;

            studentaiL.push_back(studentas);
        }
        F.close();
    }
    catch (const exception& e) {
        cerr << "Nepavyksta nuskaityti failo" << e.what() << endl;
    }
}

void rusiavimas_list(list<StudentasL>& studentaiL) {
    studentaiL.sort([](const StudentasL& a, const StudentasL &b) {
        return a.pavarde < b.pavarde;
        });
};


void rusiavimas_pagal_balus_list(const list<StudentasL>& studentaiL, list<StudentasL>& vargsiukai, list<StudentasL>& kietiakai)
{
    kietiakai.clear();
    vargsiukai.clear();
    for (const StudentasL &studentas : studentaiL) {
        float galutinis = studentas.galutinisBalas;

        if (galutinis < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else if (galutinis >= 5 && galutinis <= 10) {
            kietiakai.push_back(studentas);
        }
    }
}

    void isvedimas_vargsiukai_list(const string & failas_vargsiukai, const list<StudentasL>&vargsiukai) {
        list<StudentasL> sortedVargsiukai = vargsiukai;
        sortedVargsiukai.sort([](const StudentasL& a, const StudentasL& b) {
            int aSkaicius = stoi(a.vardas.substr(6));
            int bSkaicius = stoi(b.vardas.substr(6));

            if (aSkaicius != bSkaicius) {
                return aSkaicius < bSkaicius;
            }
            return a.pavarde < b.pavarde;
            });

        saugojimas_list(failas_vargsiukai, sortedVargsiukai);
    }


void isvedimas_kietiakai_list(const string& failas_kietiakai, const list<StudentasL>& kietiakai)
{
    list<StudentasL> sortedKietiakai = kietiakai;
    sortedKietiakai.sort([](const StudentasL& a, const StudentasL& b) {
        int aSkaicius = stoi(a.vardas.substr(6));
        int bSkaicius = stoi(b.vardas.substr(6));

        if (aSkaicius != bSkaicius) {
            return aSkaicius < bSkaicius;
        }
        return a.pavarde < b.pavarde;
        });

    saugojimas_list(failas_kietiakai, sortedKietiakai);
}

void generavimo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas) {
    auto start = std::chrono::high_resolution_clock::now();
    generavimas_list(studentaiL, skaicius, failas);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << skaicius << " irasu failo generavimas uztruko: " << duration.count() << endl;
}

void skaitymo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas) {
    auto start = std::chrono::high_resolution_clock::now();
    skaitymas_list(studentaiL, failas);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void rusiavimo_laikas_list(list<StudentasL>& studentaiL, int skaicius, list<StudentasL>& vargsiukai, list<StudentasL>& kietiakai) {
    auto start = std::chrono::high_resolution_clock::now();
    rusiavimas_pagal_balus_list(studentaiL, vargsiukai, kietiakai);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_vargsiukai_laikas_list(const string& failas_vargsiukai, int skaicius, const list<StudentasL>& vargsiukai) {
    auto start = std::chrono::high_resolution_clock::now();
    isvedimas_vargsiukai_list(failas_vargsiukai, vargsiukai);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_kietiakai_laikas_list(const string& failas_kietiakai, int skaicius, const list<StudentasL>& kietiakai) {
    auto start = std::chrono::high_resolution_clock::now();
    isvedimas_kietiakai_list(failas_kietiakai, kietiakai);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}

