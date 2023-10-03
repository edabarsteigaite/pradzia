#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

int generuotiAtsitiktiniBalai(int min, int max) {
    return rand() % (max - min + 1) + min;
}

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namu_darbai;
    int egzamino_rezultatas;
};

double skaiciuotiGalutiniVidurki(const vector<int>& namu_darbai, int egzamino_rezultatas) {
    double namuDarbuVidurkis = 0.0;
    if (!namu_darbai.empty()) {
        for (int rezultatas : namu_darbai) {
            namuDarbuVidurkis += rezultatas;
        }
        namuDarbuVidurkis /= namu_darbai.size();
    }
    return 0.4 * namuDarbuVidurkis + 0.6 * egzamino_rezultatas;
}

double skaiciuotiGalutiniMediana(const vector<int>& namu_darbai, int egzamino_rezultatas) {
    vector<int> surikiuoti_namu_darbai = namu_darbai;
    sort(surikiuoti_namu_darbai.begin(), surikiuoti_namu_darbai.end());

    if (surikiuoti_namu_darbai.size() % 2 == 0) {
        int vidurinis1 = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2 - 1];
        int vidurinis2 = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2];
        double mediana = (vidurinis1 + vidurinis2) / 2.0;
        return 0.4 * mediana + 0.6 * egzamino_rezultatas;
    } else {
        int vidurinis = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2];
        return 0.4 * vidurinis + 0.6 * egzamino_rezultatas;
    }
}

int main() {
    vector<Studentas> studentai;
    char testi;

    srand(time(0));

    do {
        Studentas naujasStudentas;

        cout << "Iveskite studento varda: ";
        cin >> naujasStudentas.vardas;

        cout << "Iveskite studento pavarde: ";
        cin >> naujasStudentas.pavarde;

        char pasirinkimas;
        cout << "Pasirinkite balu ivedimo buda (r - ranka, a - atsitiktinai): ";
        cin >> pasirinkimas;

        if (pasirinkimas == 'r') {
            cout << "Iveskite namu darbu rezultatus (iveskite -1, jei norite baigti): ";
            int namuDarbuRezultatas;
            while (true) {
                cin >> namuDarbuRezultatas;
                if (namuDarbuRezultatas == -1) {
                    break;
                }
                naujasStudentas.namu_darbai.push_back(namuDarbuRezultatas);
            }

            cout << "Iveskite egzamino rezultata: ";
            cin >> naujasStudentas.egzamino_rezultatas;
        } else if (pasirinkimas == 'a') {
            int namuDarbuSkaicius = generuotiAtsitiktiniBalai(1, 10);
            cout << "Generuoti atsitiktiniai namu darbu rezultatai (" << namuDarbuSkaicius << "): ";
            for (int i = 0; i < namuDarbuSkaicius; i++) {
                int balas = generuotiAtsitiktiniBalai(1, 10);
                naujasStudentas.namu_darbai.push_back(balas);
                cout << balas << " ";
            }
            cout << endl;

            naujasStudentas.egzamino_rezultatas = generuotiAtsitiktiniBalai(1, 10);
            cout << "Generuotas atsitiktinis egzamino rezultatas: " << naujasStudentas.egzamino_rezultatas << endl;
        }

        studentai.push_back(naujasStudentas);

        cout << "Ar norite ivesti dar viena studenta? (t/n): ";
        cin >> testi;
    } while (testi == 't' || testi == 'T');

    char pasirinkimas;
    cout << "\nPasirinkite galutinio balo skaiciavimo metoda (v - vidurkis, m - mediana): ";
    cin >> pasirinkimas;

    cout << "\nGalutiniai rezultatai:\n";
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas" << endl;
    cout << string(45, '-') << endl;

    for (const Studentas& studentas : studentai) {
        double galutinisBalas = (pasirinkimas == 'v') ?
                                skaiciuotiGalutiniVidurki(studentas.namu_darbai, studentas.egzamino_rezultatas) :
                                skaiciuotiGalutiniMediana(studentas.namu_darbai, studentas.egzamino_rezultatas);
        cout << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << fixed << setprecision(2) << setw(15) << galutinisBalas << endl;
    }

    return 0;
}

