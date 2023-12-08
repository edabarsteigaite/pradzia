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

void generavimas_vector(vector<StudentasV>& studentaiV, int count, const string& failas) {
    studentaiV.clear();
    srand(time(nullptr));

    for (int i = 1; i <= count; i++) {
        StudentasV studentas;
        studentas.vardas = "Vardas" + to_string(i);
        studentas.pavarde = "Pavarde" + to_string(i);
        for (int j = 0; j < 10; j++) {
            studentas.namu_darbai.push_back(rand() % 10 + 1);
        }
        studentas.egzamino_rezultatas = rand() % 10 + 1;
        studentaiV.push_back(studentas);
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

    for (const StudentasV& studentas : studentaiV) {
        F << setw(15) << studentas.vardas << " " << setw(15) << studentas.pavarde;
        for (int pazymys : studentas.namu_darbai) {
            F << setw(4) << pazymys;
        }
        F << setw(8) << studentas.egzamino_rezultatas << endl;
    }

    F.close();
}

void saugojimas_vector(const string& failas, const vector<StudentasV>& studentai)
{
    ofstream F(failas);
    if (!F) {
        cerr << "Nepavyko atidaryti failo " << failas << endl;
        return;
    }

    F << left << setw(15) << "Vardas" << setw(15) << " Pavarde" << setw(15) << "Galutinis " << setw(15) << endl;
    for (const StudentasV& studentas : studentai) {
        F << setw(15) << studentas.vardas << " " << setw(15) << studentas.pavarde;
        F << " " << fixed << setprecision(2) << setw(16) << studentas.galutinisBalas << " " << fixed << setprecision(2) << "\n";
    }
    F.close();
}

void skaitymas_vector(vector<StudentasV>& studentai, const string& pav) {
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
            StudentasV studentas;
            iss >> studentas.vardas >> studentas.pavarde;
            for (int i = 0; i < 10; i++) {
                int pazymys;
                iss >> pazymys;
                studentas.namu_darbai.push_back(pazymys);
            }
            iss >> studentas.egzamino_rezultatas;

            float vidurkis = accumulate(studentas.namu_darbai.begin(), studentas.namu_darbai.end(), 0.0) / studentas.namu_darbai.size();
            studentas.galutinisBalas = 0.4 * vidurkis + 0.6 * studentas.egzamino_rezultatas;

            studentai.push_back(studentas);
        }
        F.close();
    }
    catch (const exception& e) {
        cerr << "Nepavyksta perskaityti" << e.what() << endl;
    }
};

float galutinisBalasVector(const StudentasV& studentas) {
    float vidurkis = accumulate(studentas.namu_darbai.begin(), studentas.namu_darbai.end(), 0.0) / studentas.namu_darbai.size();
    return 0.4 * vidurkis + 0.6 * studentas.egzamino_rezultatas;
}

void rusiavimas_vector(vector<StudentasV>& studentai) {
    std::sort(studentai.begin(), studentai.end(), [](const StudentasV& a, const StudentasV& b) {
        return a.pavarde < b.pavarde;
        });
};

void rusiavimas_pagal_balus_vector(const vector<StudentasV>& studentai, vector<StudentasV>& vargsiukai, vector<StudentasV>& kietiakai)
{
    kietiakai.clear();
    vargsiukai.clear();
    for (const StudentasV& studentas : studentai) {
        float galutinis_balas = galutinisBalasVector(studentas);

        if (galutinis_balas < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else if (galutinis_balas >= 5.0 && galutinis_balas <= 10.0) {
            kietiakai.push_back(studentas);
        }
    }
}

void isvedimas_vargsiukai_vector(const string& failas_vargsiukai, const vector<StudentasV>& vargsiukai)
{
    vector<StudentasV> sortedVargsiukai = vargsiukai;
    sort(sortedVargsiukai.begin(), sortedVargsiukai.end(), [](const StudentasV& a, const StudentasV& b) {
        int aSkaicius = stoi(a.vardas.substr(6));
        int bSkaicius = stoi(b.vardas.substr(6));

        if (aSkaicius != bSkaicius) {
            return aSkaicius < bSkaicius;
        }
        return a.pavarde < b.pavarde;
        });

    saugojimas_vector(failas_vargsiukai, sortedVargsiukai);
}

void isvedimas_kietiakai_vector(const string& failas_kietiakai, const vector<StudentasV>& kietiakai)
{
    vector<StudentasV> sortedKietiakai = kietiakai;
    sort(sortedKietiakai.begin(), sortedKietiakai.end(), [](const StudentasV& a, const StudentasV& b) {
        int aSkaicius = stoi(a.vardas.substr(6));
        int bSkaicius = stoi(b.vardas.substr(6));

        if (aSkaicius != bSkaicius) {
            return aSkaicius < bSkaicius;
        }

        return a.pavarde < b.pavarde;
        });

    saugojimas_vector(failas_kietiakai, sortedKietiakai);
}

void generavimo_laikas_vector(vector<StudentasV>& studentai, int skaicius, const string& failas) {
    auto start = std::chrono::high_resolution_clock::now();
    generavimas_vector(studentai, skaicius, failas);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << skaicius << " irasu generavimo laikas: " << duration.count() << endl;
}

void skaitymo_laikas_vector(vector<StudentasV>& studentai, int skaicius, const string& failas) {
    auto start = std::chrono::high_resolution_clock::now();
    skaitymas_vector(studentai, failas);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void rusiavimo_laikas_vector(vector<StudentasV>& studentai, int skaicius, vector<StudentasV>& vargsiukai, vector<StudentasV>& kietiakai) {
    auto start = std::chrono::high_resolution_clock::now();
    rusiavimas_pagal_balus_vector(studentai, vargsiukai, kietiakai);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_vargsiukai_laikas_vector(const string& failas_vargsiukai, int skaicius, const vector<StudentasV>& vargsiukai) {
    auto start = std::chrono::high_resolution_clock::now();
    isvedimas_vargsiukai_vector(failas_vargsiukai, vargsiukai);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_kietiakai_laikas_vector(const string& failas_kietiakai, int skaicius, const vector<StudentasV>& kietiakai) {
    auto start = std::chrono::high_resolution_clock::now();
    isvedimas_kietiakai_vector(failas_kietiakai, kietiakai);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
}
