#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namu_darbai; 
    int egzamino_rezultatas;
};

double skaiciuotiGalutiniBala(const vector<int>& namu_darbai, int egzamino_rezultatas) {
    double namuDarbuVidurkis = 0.0;
    if (!namu_darbai.empty()) {
        for (int rezultatas : namu_darbai) {
            namuDarbuVidurkis += rezultatas;
        }
        namuDarbuVidurkis /= namu_darbai.size();
    }

    return 0.4 * namuDarbuVidurkis + 0.6 * egzamino_rezultatas;
}

int main() {
    vector<Studentas> studentai;
    char testi;

    do {
        Studentas naujasStudentas;

        cout << "Iveskite studento varda: ";
        cin >> naujasStudentas.vardas;

        cout << "Iveskite studento pavarde: ";
        cin >> naujasStudentas.pavarde;

        int namuDarbuRezultatas;
        cout << "Iveskite namu darbu rezultatus (iveskite -1, jei norite baigti): ";
        while (true) {
            cin >> namuDarbuRezultatas;
            if (namuDarbuRezultatas == -1) {
                break;
            }
            naujasStudentas.namu_darbai.push_back(namuDarbuRezultatas);
        }

        cout << "Iveskite egzamino rezultata: ";
        cin >> naujasStudentas.egzamino_rezultatas;

        studentai.push_back(naujasStudentas);

        cout << "Ar norite ivesti dar viena studenta? (t/n): ";
        cin >> testi;
    } while (testi == 't' || testi == 'T');

    cout << "\nGalutiniai rezultatai:\n";
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas" << endl;
    cout << string(45, '-') << endl;

    for (const Studentas& studentas : studentai) {
        double galutinisBalas = skaiciuotiGalutiniBala(studentas.namu_darbai, studentas.egzamino_rezultatas);
        cout << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << fixed << setprecision(2) << setw(15) << galutinisBalas << endl;
    }

    return 0;
}

