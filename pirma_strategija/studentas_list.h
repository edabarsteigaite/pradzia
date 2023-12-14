#ifndef STUDENTAS_LIST_H_INCLUDED
#define STUDENTAS_LIST_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <list>

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
using std::list;


void rusiavimas_vector(vector<StudentasV>& studentaiV);
void generavimas_vector(vector<StudentasV>& studentaiV, int count, const string& failas);
void saugojimas_vector(const string& failas, const vector<StudentasV>& studentaiV);
void skaitymas_vector(vector<StudentasV>& studentaiV, const string& pav);

void rusiavimas_pagal_balus_vector(const vector<StudentasV>& studentaiV, vector<StudentasV>& vargsiukai, vector<StudentasV>& kietiakai);
void isvedimas_vargsiukai_vector(const string& failas_vargsiukai, const vector<StudentasV>& vargsiukai);
void isvedimas_kietiakai_vector(const string& failas_kietiakai, const vector<StudentasV>& kietiakai);

void generavimo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, const string& failas);
void skaitymo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, const string& failas);
void rusiavimo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, vector<StudentasV>& vargsiukai, vector<StudentasV>& kietiakai);
void isvedimo_vargsiukai_laikas_vector(const string& failas_vargsiukai, int skaicius, const vector<StudentasV>& vargsiukai);
void isvedimo_kietiakai_laikas_vector(const string& failas_kietiakai, int skaicius, const vector<StudentasV>& kietiakai);
void testavimas_vector(const string& failoPav, int skaicius, const string& kietiakaiF, const string& vargsiukaiF);

void rusiavimas_list(list<StudentasL>& studentaiL);
void generavimas_list(list<StudentasL>& studentaiL, int count, const string& failas);
void saugojimas_list(const string& failas, const list<StudentasL>& studentaiL);
void skaitymas_list(list<StudentasL>& studentaiL, const string& pav);

void rusiavimas_pagal_balus_list(const list<StudentasL>& studentaiL, list<StudentasL>& vargsiukai, list<StudentasL>& kietiakai);
void isvedimas_vargsiukai_list(const string& failas_vargsiukai, const list<StudentasL>& vargsiukai);
void isvedimas_kietiakai_list(const string& failas_kietiakai, const list<StudentasL>& kietiakai);

void generavimo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas);
void skaitymo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas);
void rusiavimo_laikas_list(list<StudentasL>& studentaiL , int skaicius, list<StudentasL>& vargsiukai, list<StudentasL>& kietiakai);
void isvedimo_vargsiukai_laikas_list(const string& failas_vargsiukai, int skaicius, const list<StudentasL>& vargsiukai);
void isvedimo_kietiakai_laikas_list(const string& failas_kietiakai, int skaicius, const list<StudentasL>& kietiakai);
void testavimas_list(const string& failoPav, int skaicius, const string& kietiakaiF, const string& vargsiukaiF);
#endif
