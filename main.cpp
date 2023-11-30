#include <iostream>
#include <iomanip>
#include <string>
#include "studentas.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>

using namespace std;



int main()
{
    vector <Studentas> studentai;
    int pasirinkimas;
    cout << "Pasirinkite ar norite generuoti failus (spauskite 1), ar atlikti testavima su failais (spauskite 2) " << endl;
    while (!(cin >> pasirinkimas) || pasirinkimas < 0 || pasirinkimas>3)
    {
        cout << "Pasirinkite 1 arba 2 ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (pasirinkimas == 1)
    {
        generavimo_laikas(studentai, 1000, "studentai_1000.txt");
        generavimo_laikas(studentai, 10000, "studentai_10000.txt");
        generavimo_laikas(studentai, 100000, "studentai_100000.txt");
        generavimo_laikas(studentai, 1000000, "studentai_1000000.txt");
        generavimo_laikas(studentai, 10000000, "studentai_10000000.txt");

        cout << "-----------------------------------------------------" << endl;

        testavimas("studentai_1000.txt", 1000, "kietiakai_1000.txt", "vargsiukai_1000.txt");
        testavimas("studentai_10000.txt", 10000, "kietiakai_10000.txt", "vargsiukai_10000.txt");
        testavimas("studentai_100000.txt", 100000, "kietiakai_100000.txt", "vargsiukai_100000.txt");
        testavimas("studentai_1000000.txt", 1000000, "kietiakai_1000000.txt", "vargsiukai_1000000.txt");
        testavimas("studentai_10000000.txt", 10000000, "kietiakai_10000000.txt", "vargsiukai_10000000.txt");
    }
    else if (pasirinkimas == 2)
    {
        testavimas("studentai_1000.txt", 1000, "kietiakai_1000.txt", "vargsiukai_1000.txt");
        testavimas("studentai_10000.txt", 10000, "kietiakai_10000.txt", "vargsiukai_10000.txt");
        testavimas("studentai_100000.txt", 100000, "kietiakai_100000.txt", "vargsiukai_100000.txt");
        testavimas("studentai_1000000.txt", 1000000, "kietiakai_1000000.txt", "vargsiukai_1000000.txt");
        testavimas("studentai_10000000.txt", 10000000, "kietiakai_10000000.txt", "vargsiukai_10000000.txt");
    }
    return 0;
}
