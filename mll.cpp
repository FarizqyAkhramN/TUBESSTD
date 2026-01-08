#include "MLL.H"

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

adrProvinsi searchProvinsi(AdministrativeStructure S, string nama) {
    adrProvinsi P = S.firstProvinsi;
    while (P != nullptr) {
        if (P->info.nama == nama) return P;
        P = P->next;
    }
    return nullptr;
}

adrKabupaten searchKabupaten(AdministrativeStructure S, string namaProvinsi, string namaKabupaten) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) return nullptr;
    adrKabupaten Q = P->firstKabupaten;
    while (Q != nullptr) {
        if (Q->info.nama == namaKabupaten) return Q;
        Q = Q->next;
    }
    return nullptr;
}

bool addProvinsi(AdministrativeStructure &S, const string& namaProvinsi) {
    adrProvinsi P = createElementProvinsi(namaProvinsi);
    if (S.firstProvinsi == nullptr) {
        S.firstProvinsi = P;
    } else {
        adrProvinsi current = S.firstProvinsi;
        while (current->next != nullptr) current = current->next;
        current->next = P;
        P->prev = current;
    }
    cout << P->info.tipe << " '" << P->info.nama << "' berhasil ditambahkan di bawah " << S.nama << "." << endl;
    return true;
}

bool addKabupaten(AdministrativeStructure &S, const string& namaProvinsi, const string& namaKabupaten) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) return false;
    adrKabupaten Q = createElementKabupaten(namaKabupaten);
    if (P->firstKabupaten == nullptr) {
        P->firstKabupaten = Q;
    } else {
        adrKabupaten current = P->firstKabupaten;
        while (current->next != nullptr) current = current->next;
        current->next = Q;
        Q->prev = current;
    }
    cout << Q->info.tipe << " '" << Q->info.nama << "' berhasil ditambahkan di bawah " << P->info.nama << "." << endl;
    return true;
}

bool deleteProvinsi(AdministrativeStructure &S, string namaProvinsi) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) return false;
    adrKabupaten currentKab = P->firstKabupaten;
    while (currentKab != nullptr) {
        adrKabupaten temp = currentKab;
        currentKab = currentKab->next;
        delete temp;
    }
    if (P == S.firstProvinsi) {
        S.firstProvinsi = P->next;
        if (S.firstProvinsi != nullptr) S.firstProvinsi->prev = nullptr;
    } else {
        P->prev->next = P->next;
        if (P->next != nullptr) P->next->prev = P->prev;
    }
    delete P;
    return true;
}

bool deleteKabupaten(AdministrativeStructure &S, string namaProvinsi, string namaKabupaten) {
    adrProvinsi P = searchProvinsi(S, namaProvinsi);
    if (P == nullptr) return false;
    adrKabupaten target = searchKabupaten(S, namaProvinsi, namaKabupaten);
    if (target == nullptr) return false;
    if (target == P->firstKabupaten) {
        P->firstKabupaten = target->next;
        if (P->firstKabupaten != nullptr) P->firstKabupaten->prev = nullptr;
    } else {
        target->prev->next = target->next;
        if (target->next != nullptr) target->next->prev = target->prev;
    }
    delete target;
    return true;
}

void displayList(AdministrativeStructure S) {
    adrProvinsi P = S.firstProvinsi;
    cout << "\n--- STRUKTUR WILAYAH ---" << endl;
    cout << "NEGARA: " << S.nama << endl;

    if (P == nullptr) {
        cout << "  -> (Belum ada data provinsi)" << endl;
        return;
    }
    while (P != nullptr) {
        cout << "  |-- PROVINSI: " << P->info.nama << endl;

        adrKabupaten Q = P->firstKabupaten;
        if (Q == nullptr) {
            cout << "  |   |-- (Belum ada kabupaten/kota)" << endl;
        } else {
            while (Q != nullptr) {
                cout << "  |   |-- KABUPATEN/KOTA: " << Q->info.nama << endl;
                Q = Q->next;
            }
        }
        P = P->next;
    }
}

