#include "MLL.H"
#include <iostream>
#include <string>

using namespace std;

adrProvinsi createElementProvinsi(string nama) {
    adrProvinsi P = new ElementProvinsi;
    P->info.nama = nama;
    P->info.tipe = "Provinsi";
    P->next = nullptr;
    P->prev = nullptr;
    P->firstKabupaten = nullptr;
    return P;
}

adrKabupaten createElementKabupaten(string nama) {
    adrKabupaten Q = new ElementKabupaten;
    Q->info.nama = nama;
    Q->info.tipe = "Kabupaten/Kota";
    Q->next = nullptr;
    Q->prev = nullptr;
    return Q;
}

void createStructure(AdministrativeStructure &S, const string& namaNegara) {
    S.nama = namaNegara;
    S.tipe = "Negara";
    S.firstProvinsi = nullptr;
}

bool addProvinsi(AdministrativeStructure &S, const string& namaProvinsi) {
    adrProvinsi P = createElementProvinsi(namaProvinsi);
    adrProvinsi &firstProv = S.firstProvinsi;

    if (firstProv == nullptr) {
        firstProv = P;
    } else {
        adrProvinsi current = firstProv;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = P;
        P->prev = current;
    }
    cout << P->info.tipe << " '" << P->info.nama << "' berhasil ditambahkan di bawah " << S.nama << "." << endl;
    return true;
}

bool addKabupaten(AdministrativeStructure &S, const string& namaProvinsi, const string& namaKabupaten) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) {
        cout << "ERROR: Provinsi induk '" << namaProvinsi << "' tidak ditemukan." << endl;
        return false;
    }

    adrKabupaten Q = createElementKabupaten(namaKabupaten);
    adrKabupaten &firstKab = P->firstKabupaten;

    if (firstKab == nullptr) {
        firstKab = Q;
    } else {
        adrKabupaten current = firstKab;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = Q;
        Q->prev = current;
    }
    cout << Q->info.tipe << " '" << Q->info.nama << "' berhasil ditambahkan di bawah " << P->info.nama << "." << endl;
    return true;
}

adrProvinsi searchProvinsi(AdministrativeStructure S, string nama) {
    adrProvinsi P = S.firstProvinsi;
    while (P != nullptr) {
        if (P->info.nama == nama) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

adrKabupaten searchKabupaten(AdministrativeStructure S, string namaProvinsi, string namaKabupaten) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) return nullptr;

    adrKabupaten Q = P->firstKabupaten;
    while (Q != nullptr) {
        if (Q->info.nama == namaKabupaten) {
            return Q;
        }
        Q = Q->next;
    }
    return nullptr;
}

bool deleteProvinsi(AdministrativeStructure &S, string namaProvinsi) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) {
        cout << "ERROR: Provinsi '" << namaProvinsi << "' tidak ditemukan." << endl;
        return false;
    }

    adrKabupaten currentKab = P->firstKabupaten;
    while (currentKab != nullptr) {
        adrKabupaten temp = currentKab;
        currentKab = currentKab->next;
        delete temp;
    }

    if (P == S.firstProvinsi) {
        S.firstProvinsi = P->next;
        if (S.firstProvinsi != nullptr) {
            S.firstProvinsi->prev = nullptr;
        }
    } else {
        P->prev->next = P->next;
        if (P->next != nullptr) {
            P->next->prev = P->prev;
        }
    }

    delete P;
    cout << "Provinsi '" << namaProvinsi << "' dan semua Kabupaten/Kota-nya berhasil dihapus." << endl;
    return true;
}

bool deleteKabupaten(AdministrativeStructure &S, string namaProvinsi, string namaKabupaten) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) {
        cout << "ERROR: Provinsi induk tidak ditemukan." << endl;
        return false;
    }

    adrKabupaten target = searchKabupaten(S, namaProvinsi, namaKabupaten);
    if (target == nullptr) {
        cout << "ERROR: Kabupaten/Kota '" << namaKabupaten << "' tidak ditemukan di " << P->info.nama << "." << endl;
        return false;
    }

    if (target == P->firstKabupaten) {
        P->firstKabupaten = target->next;
        if (P->firstKabupaten != nullptr) {
            P->firstKabupaten->prev = nullptr;
        }
    } else {
        target->prev->next = target->next;
        if (target->next != nullptr) {
            target->next->prev = target->prev;
        }
    }
    delete target;
    cout << "Kabupaten/Kota '" << namaKabupaten << "' di Provinsi " << P->info.nama << " berhasil dihapus." << endl;
    return true;
}

void displayList(AdministrativeStructure S) {
    adrProvinsi P = S.firstProvinsi;
    cout << "\n--- STRUKTUR MLL HIERARKI: " << endl;
    if (P == nullptr) {
        cout << "  -> List Provinsi Kosong." << endl;
        return;
    }

    while (P != nullptr) {
        cout << "-> Negara: " << S.nama << endl;
        cout << "  -> " << P->info.tipe << ": " << P->info.nama << endl;
        adrKabupaten Q = P->firstKabupaten;
        cout << "     -> Kabupaten/Kota: ";
        if (Q == nullptr) {
            cout << " (Kosong)";
        } else {
            while (Q != nullptr) {
                cout << Q->info.nama;
                if (Q->next != nullptr) { cout << ", "; }
                Q = Q->next;
            }
        }
        cout << endl;
        P = P->next;
    }
    cout << "--------------------------------------------------------\n" << endl;
}

void preOrderTraversal(AdministrativeStructure S) {
    adrProvinsi P = S.firstProvinsi;
    cout << S.nama << " (" << S.tipe << ") -> ";

    while (P != nullptr) {
        cout << P->info.nama << " (Provinsi) -> ";
        adrKabupaten Q = P->firstKabupaten;
        while (Q != nullptr) {
            cout << Q->info.nama << " (Kab/Kota) -> ";
            Q = Q->next;
        }
        P = P->next;
    }
    cout << "END" << endl;
}

void inOrderTraversal(AdministrativeStructure S) {
    adrProvinsi P = S.firstProvinsi;
    while (P != nullptr) {
        adrKabupaten Q = P->firstKabupaten;
        while (Q != nullptr) {
            cout << Q->info.nama << " (Kab/Kota) -> ";
            Q = Q->next;
        }
        cout << P->info.nama << " (Provinsi) -> ";
        P = P->next;
    }
    cout << S.nama << " (Negara) -> END" << endl;
}

void postOrderTraversal(AdministrativeStructure S) {
    adrProvinsi P = S.firstProvinsi;

    while (P != nullptr) {
        adrKabupaten Q = P->firstKabupaten;
        while (Q != nullptr) {
            cout << Q->info.nama << " (Kab/Kota) -> ";
            Q = Q->next;
        }
        cout << P->info.nama << " (Provinsi) -> ";
        P = P->next;
    }
    cout << S.nama << " (Negara) -> END" << endl;
}
