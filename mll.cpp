#include "MLL.H"

void createStructure(AdministrativeStructure &S, string namaNegara) {
    S.nama = namaNegara;
    S.tipe = "Negara";
    S.left = nullptr;
}

adrProvinsi searchProvinsiRekursif(adrProvinsi P, string nama) {
    if (P == nullptr) return nullptr;
    if (P->info.nama == nama) return P;
    return searchProvinsiRekursif(P->right, nama);
}

adrKabupaten searchKabupatenRekursif(adrKabupaten Q, string nama) {
    if (Q == nullptr) return nullptr;
    if (Q->info.nama == nama) return Q;
    return searchKabupatenRekursif(Q->right, nama);
}

bool addProvinsi(AdministrativeStructure &S, string namaProvinsi) {
    adrProvinsi P = new ElementProvinsi;
    P->info.nama = namaProvinsi;
    P->info.tipe = "Provinsi";
    P->left = nullptr;
    P->right = nullptr;

    if (S.left == nullptr) {
        S.left = P;
    } else {
        adrProvinsi last = S.left;
        while (last->right != nullptr) last = last->right;
        last->right = P;
    }
    cout << "Provinsi '" << namaProvinsi << "' berhasil ditambahkan di bawah " << S.nama << "." << endl;
    return true;
}

bool addKabupaten(AdministrativeStructure &S, string namaProvinsi, string namaKabupaten) {
    adrProvinsi P = searchProvinsiRekursif(S.left, namaProvinsi);
    if (P == nullptr) return false;

    adrKabupaten Q = new ElementKabupaten;
    Q->info.nama = namaKabupaten;
    Q->info.tipe = "Kabupaten/Kota";
    Q->right = nullptr;
    Q->left = nullptr;

    if (P->left == nullptr) {
        P->left = Q;
    } else {
        adrKabupaten last = P->left;
        while (last->right != nullptr) last = last->right;
        last->right = Q;
    }
    cout << "Kabupaten '" << namaKabupaten << "' berhasil ditambahkan di bawah " << namaProvinsi << "." << endl;
    return true;
}

bool deleteProvinsi(AdministrativeStructure &S, string namaProvinsi) {
    adrProvinsi P = searchProvinsiRekursif(S.left, namaProvinsi);
    if (P == nullptr) return false;

    if (S.left == P) {
        S.left = P->right;
    } else {
        adrProvinsi prev = S.left;
        while (prev->right != P) prev = prev->right;
        prev->right = P->right;
    }
    delete P;
    return true;
}

bool deleteKabupaten(AdministrativeStructure &S, string namaProvinsi, string namaKabupaten) {
    adrProvinsi P = searchProvinsiRekursif(S.left, namaProvinsi);
    if (P == nullptr || P->left == nullptr) return false;

    adrKabupaten Q = searchKabupatenRekursif(P->left, namaKabupaten);
    if (Q == nullptr) return false;

    if (P->left == Q) {
        P->left = Q->right;
    } else {
        adrKabupaten prev = P->left;
        while (prev->right != Q) prev = prev->right;
        prev->right = Q->right;
    }
    delete Q;
    return true;
}

void printKabupatenRekursif(adrKabupaten Q) {
    if (Q == nullptr) return;
    cout << "  |   |-- Kabupaten: " << Q->info.nama << endl;
    printKabupatenRekursif(Q->right);
}

void displayList(AdministrativeStructure S) {
    cout << "\n=== STRUKTUR HIERARKI ADMINISTRASI ===" << endl;
    cout << S.nama << " (Root Negara)" << endl;

    adrProvinsi P = S.left;
    if (P == nullptr) {
        cout << "  [Belum ada data provinsi]" << endl;
        return;
    }

    while (P != nullptr) {
        cout << "  |-- Provinsi: " << P->info.nama << endl;
        if (P->left == nullptr) {
            cout << "  |   |-- (Belum ada kabupaten)" << endl;
        } else {
            printKabupatenRekursif(P->left);
        }
        P = P->right;
    }
    cout << "=======================================" << endl;
}

void preOrderRekursif(adrProvinsi P) {
    if (P == nullptr) return;
    cout << P->info.nama << " (Provinsi) -> ";
    adrKabupaten Q = P->left;
    while (Q != nullptr) {
        cout << Q->info.nama << " (Kab/Kota) -> ";
        Q = Q->right;
    }
    preOrderRekursif(P->right);
}

void inOrderRekursif(adrProvinsi P) {
    if (P == nullptr) return;
    adrKabupaten Q = P->left;
    while (Q != nullptr) {
        cout << Q->info.nama << " (Kab/Kota) -> ";
        Q = Q->right;
    }
    cout << P->info.nama << " (Provinsi) -> ";
    inOrderRekursif(P->right);
}

void postOrderRekursif(adrProvinsi P) {
    if (P == nullptr) return;
    postOrderRekursif(P->right);
    adrKabupaten Q = P->left;
    while (Q != nullptr) {
        cout << Q->info.nama << " (Kab/Kota) -> ";
        Q = Q->right;
    }
    cout << P->info.nama << " (Provinsi) -> ";
}
