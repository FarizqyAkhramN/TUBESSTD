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
    adrKabupaten next;
    adrKabupaten prev;
} ElementKabupaten;

typedef struct elemenProvinsi {
    Info info;
    adrProvinsi next;
    adrProvinsi prev;
    adrKabupaten firstKabupaten;
} ElementProvinsi;

typedef struct {
    string nama;
    string tipe;
    adrProvinsi firstProvinsi;
} AdministrativeStructure;

void createStructure(AdministrativeStructure &S, const string& namaNegara);
bool addProvinsi(AdministrativeStructure &S, const string& namaProvinsi);
bool addKabupaten(AdministrativeStructure &S, const string& namaProvinsi, const string& namaKabupaten);
adrProvinsi searchProvinsi(AdministrativeStructure S, string nama);
adrKabupaten searchKabupaten(AdministrativeStructure S, string namaProvinsi, string namaKabupaten);
bool deleteProvinsi(AdministrativeStructure &S, string namaProvinsi);
bool deleteKabupaten(AdministrativeStructure &S, string namaProvinsi, string namaKabupaten);

void displayList(AdministrativeStructure S);
void preOrderTraversal(AdministrativeStructure S);
void inOrderTraversal(AdministrativeStructure S);
void postOrderTraversal(AdministrativeStructure S);

#endif // MLL_H_
