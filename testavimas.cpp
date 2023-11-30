#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include "studentas.h"
#include <fstream>

using namespace std;

void testavimas(const string& failoPav, int skaicius, const string& kietiakaiF, const string& vargsiukaiF) {
    vector<Studentas> studentai;
    vector<Studentas> vargsiukai;
    vector<Studentas> kietiakai;
    vector<double> skaitymoLaikai;
    vector<double> rusiavimoLaikai;
    vector<double> isvedimoVLaikai;
    vector<double> isvedimoKLaikai;

    int kartai = 3;
    for (int i = 0; i < kartai; i++) {
        auto start_nuskaitymo_laikas = std::chrono::high_resolution_clock::now();
        skaitymo_laikas(studentai, skaicius, failoPav);
        auto end_nuskaitymas = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_nuskaitymas = end_nuskaitymas - start_nuskaitymo_laikas;
        skaitymoLaikai.push_back(duration_nuskaitymas.count());

        rusiavimas(studentai);

        auto start_rusiavimo_laikas = std::chrono::high_resolution_clock::now();
        rusiavimo_laikas(studentai, skaicius, vargsiukai, kietiakai);
        auto end_rusiavimas = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_rusiavimas = end_rusiavimas - start_rusiavimo_laikas;
        rusiavimoLaikai.push_back(duration_rusiavimas.count());

        auto start_vargsiuku_laikas = std::chrono::high_resolution_clock::now();
        isvedimo_vargsiukai_laikas(vargsiukaiF, skaicius, vargsiukai);
        auto end_vargsiukai = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_vargsiukai = end_vargsiukai - start_vargsiuku_laikas;
        isvedimoVLaikai.push_back(duration_vargsiukai.count());

        auto start_kietiaku_laikas = std::chrono::high_resolution_clock::now();
        isvedimo_kietiakai_laikas(kietiakaiF, skaicius, kietiakai);
        auto end_kietiakai = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_kietiakai = end_kietiakai - start_kietiaku_laikas;
        isvedimoKLaikai.push_back(duration_kietiakai.count());
        studentai.clear();
    }

    double vidutinis_nuskaitymo_laikas = std::accumulate(skaitymoLaikai.begin(), skaitymoLaikai.end(), 0.0) / skaitymoLaikai.size();
    double vidutinis_rusiavimo_laikas = std::accumulate(rusiavimoLaikai.begin(), rusiavimoLaikai.end(), 0.0) / rusiavimoLaikai.size();
    double vidutinis_vargsiuku_laikas = std::accumulate(isvedimoVLaikai.begin(), isvedimoVLaikai.end(), 0.0) / isvedimoVLaikai.size();
    double vidutinis_kietiaku_laikas = std::accumulate(isvedimoKLaikai.begin(), isvedimoKLaikai.end(), 0.0) / isvedimoKLaikai.size();

    cout << skaicius << " irasu skaitymo laikas: " << vidutinis_nuskaitymo_laikas << endl;
    cout << skaicius << " irasu rusiavimo laikas: " << vidutinis_rusiavimo_laikas << endl;
    cout << skaicius << " irasu vargsiuku isvedimo laikas: " << vidutinis_vargsiuku_laikas << endl;
    cout << skaicius << " irasu kietiaku isvedimo laikas: " << vidutinis_kietiaku_laikas << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
}
