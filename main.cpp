#include "MLL.H"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void cleanInputBuffer() {
    cin.ignore();
}

void displayMenu() {
    cout << "\n=========================================" << endl;
    cout << "   SISTEM MLL ADMINISTRASI: INDONESIA" << endl;
    cout << "=========================================" << endl;
    cout << "1. Tambah Provinsi" << endl;
    cout << "2. Tambah Kabupaten/Kota" << endl;
    cout << "3. Cari Provinsi / Kabupaten" << endl;
    cout << "4. Hapus Provinsi (beserta Kabupaten)" << endl;
    cout << "5. Hapus Kabupaten/Kota" << endl;
    cout << "6. Tampilkan Seluruh List (View)" << endl;
    cout << "7. Traversal Pre-Order" << endl;
    cout << "8. Traversal In-Order" << endl;
    cout << "9. Traversal Post-Order" << endl;
    cout << "10. Keluar" << endl;
    cout << "Pilihan Anda: ";
}

int main() {
    AdministrativeStructure S;
    int choice;
    string namaProvinsi, namaKabupaten, namaTarget;

    createStructure(S, "Indonesia");
    cout << "Root Administrasi Dibuat: " << S.nama << " (" << S.tipe << ")" << endl;

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cout << "\nInput tidak valid. Harap masukkan angka." << endl;
            cin.clear();
            cleanInputBuffer();
            choice = 0;
            continue;
        }
        cleanInputBuffer();

        switch (choice) {
            case 1:
                cout << "Masukkan Nama Provinsi Baru: ";
                getline(cin, namaProvinsi);
                addProvinsi(S, namaProvinsi);
                break;
            case 2:
                cout << "Masukkan Nama Provinsi Induk: ";
                getline(cin, namaProvinsi);
                cout << "Masukkan Nama Kabupaten/Kota Baru: ";
                getline(cin, namaKabupaten);
                addKabupaten(S, namaProvinsi, namaKabupaten);
                break;
            case 3: {
                cout << "Masukkan Nama yang dicari: ";
                getline(cin, namaTarget);
                adrProvinsi fP = searchProvinsiRekursif(S.left, namaTarget);
                if (fP) {
                    cout << "\nHasil Pencarian:\n" << S.nama << " (Root) > " << fP->info.nama << " (Provinsi)" << endl;
                } else {
                    bool found = false;
                    adrProvinsi currP = S.left;
                    while (currP != nullptr) {
                        adrKabupaten fQ = searchKabupatenRekursif(currP->left, namaTarget);
                        if (fQ) {
                            cout << "\nHasil Pencarian:\n" << S.nama << " (Root) > " << currP->info.nama << " (Provinsi) > " << fQ->info.nama << " (Kabupaten)" << endl;
                            found = true;
                            break;
                        }
                        currP = currP->right;
                    }
                    if (!found) cout << "Data '" << namaTarget << "' tidak ditemukan." << endl;
                }
                break;
            }
            case 4:
                cout << "Masukkan Nama Provinsi yang akan dihapus: ";
                getline(cin, namaProvinsi);
                if (deleteProvinsi(S, namaProvinsi)) {
                    cout << "Provinsi '" << namaProvinsi << "' berhasil dihapus." << endl;
                } else {
                    cout << "Gagal: Provinsi tidak ditemukan." << endl;
                }
                break;

            case 5:
                cout << "Masukkan Nama Provinsi Induk: ";
                getline(cin, namaProvinsi);
                cout << "Masukkan Nama Kabupaten/Kota yang akan dihapus: ";
                getline(cin, namaKabupaten);
                if (deleteKabupaten(S, namaProvinsi, namaKabupaten)) {
                    cout << "Kabupaten '" << namaKabupaten << "' berhasil dihapus." << endl;
                } else {
                    cout << "Gagal: Data tidak ditemukan." << endl;
                }
                break;
            case 6: displayList(S); break;
            case 7:
                cout << "\nPre-Order: " << S.nama << " (Negara) -> ";
                preOrderRekursif(S.left);
                cout << "END" << endl;
                break;
            case 8:
                cout << "\nIn-Order: ";
                inOrderRekursif(S.left);
                cout << S.nama << " (Negara) -> END" << endl;
                break;
            case 9:
                cout << "\nPost-Order: ";
                postOrderRekursif(S.left);
                cout << S.nama << " (Negara) -> END" << endl;
                break;
        }
    } while (choice != 10);

    return 0;
}
