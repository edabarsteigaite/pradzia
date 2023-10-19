#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm> 
#include "studentas.h"

using namespace std;
int generuotiAtsitiktiniBalai(int min, int max);


int main() {
    vector<Studentas> studentai;

    srand(time(0));

    char pasirinkimas;
    cout << "Pasirinkite balu ivedimo buda (r - ranka, a - atsitiktinai, f - nuskaityti is failo): ";
    cin >> pasirinkimas;

    if (pasirinkimas == 'r') {
        char testi;
        do {
            Studentas naujasStudentas;

            cout << "Iveskite studento varda: ";
            cin >> naujasStudentas.vardas;

            cout << "Iveskite studento pavarde: ";
            cin >> naujasStudentas.pavarde;

            cout << "Iveskite namu darbu rezultatus (iveskite -1, jei norite baigti): ";

            int namuDarbuRezultatas;

            do {

                while (true) {
                    if (!(cin >> namuDarbuRezultatas)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Netinkama ivestis. Iveskite balus nuo 1 iki 10: ";
                    }
                    else if (namuDarbuRezultatas == -1) {
                        break;
                    }
                    else if (namuDarbuRezultatas < 1 || namuDarbuRezultatas > 10) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Klaida: Netinkamas balas. Iveskite balus nuo 1 iki 10: ";
                    }
                    else {
                        naujasStudentas.namu_darbai.push_back(namuDarbuRezultatas);
                        break; 
                    }
                }
            } while (namuDarbuRezultatas != -1); 



            cout << "Iveskite egzamino rezultata: ";
            cin >> naujasStudentas.egzamino_rezultatas;

            studentai.push_back(naujasStudentas);

            cout << "Ar norite ivesti dar viena studenta? (t/n): ";
            cin >> testi;
        } while (testi == 't' || testi == 'T');
    }
    else if (pasirinkimas == 'a') {
        char testi;
        do {
            Studentas naujasStudentas;

            cout << "Iveskite studento varda: ";
            cin >> naujasStudentas.vardas;

            cout << "Iveskite studento pavarde: ";
            cin >> naujasStudentas.pavarde;

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

            studentai.push_back(naujasStudentas);

            cout << "Ar norite ivesti dar viena studenta? (t/n): ";
            cin >> testi;
        } while (testi == 't' || testi == 'T');
    }
    else if (pasirinkimas == 'f') {
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failoPavadinimas;

        skaitytiDuomenisIsFailo(failoPavadinimas, studentai);
    }

    sort(studentai.begin(), studentai.end(), lyginimasPagalVardus);

    cout << "\nGalutiniai rezultatai:\n";
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(70, '-') << endl;

    for (const Studentas& studentas : studentai) {
        double galutinisVidurkiu = skaiciuotiGalutiniVidurki(studentas.namu_darbai, studentas.egzamino_rezultatas);
        double galutinisMediana = skaiciuotiGalutiniMediana(studentas.namu_darbai, studentas.egzamino_rezultatas);

        cout << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << fixed << setprecision(2)
            << setw(20) << galutinisVidurkiu << setw(20) << galutinisMediana << endl;
    }

    return 0;
}
