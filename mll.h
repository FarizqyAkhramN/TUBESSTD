#ifndef MLL_H_
#define MLL_H_

#include <iostream>
#include <string>

using namespace std;

typedef struct elemenProvinsi *adrProvinsi;
typedef struct elemenKabupaten *adrKabupaten;

typedef struct {
    string nama;
    string tipe;
} Info;

typedef struct elemenKabupaten {
    Info info;
    adrKabupaten right;
    adrKabupaten left;
} ElementKabupaten;

typedef struct elemenProvinsi {
    Info info;
    adrProvinsi right;
    adrKabupaten left;
} ElementProvinsi;

typedef struct {
    string nama;
    string tipe;
    adrProvinsi left;
} AdministrativeStructure;

void createStructure(AdministrativeStructure &S, string namaNegara);
bool addProvinsi(AdministrativeStructure &S, string namaProvinsi);
bool addKabupaten(AdministrativeStructure &S, string namaProvinsi, string namaKabupaten);
bool deleteProvinsi(AdministrativeStructure &S, string namaProvinsi);
bool deleteKabupaten(AdministrativeStructure &S, string namaProvinsi, string namaKabupaten);

adrProvinsi searchProvinsiRekursif(adrProvinsi P, string nama);
adrKabupaten searchKabupatenRekursif(adrKabupaten Q, string nama);

void preOrderRekursif(adrProvinsi P);
void inOrderRekursif(adrProvinsi P);
void postOrderRekursif(adrProvinsi P);

void displayList(AdministrativeStructure S);

#endif
