#include "MLL.H"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void cleanInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "\n=========================================" << endl;
    cout << "  SISTEM MLL WILAYAH INDONESIA" << endl;
    cout << "=========================================" << endl;
    cout << "1. Tambah Provinsi" << endl;
    cout << "2. Tambah Kabupaten/Kota" << endl;
    cout << "3. Cari Provinsi / Kabupaten" << endl;
    cout << "4. Hapus Provinsi (beserta Kabupaten)" << endl;
    cout << "5. Hapus Kabupaten/Kota" << endl;
    cout << "6. Tampilkan Seluruh List" << endl;
    cout << "7. Keluar" << endl;
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

        cout << endl;

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
                cout << "Masukkan Nama yang dicari (Provinsi/Kabupaten): ";
                getline(cin, namaTarget);

                adrProvinsi foundProv = searchProvinsi(S, namaTarget);

                if (foundProv) {
                    cout << "DITEMUKAN: Provinsi '" << foundProv->info.nama << "'." << endl;
                    break;
                }

                adrProvinsi P = S.firstProvinsi;
                bool found = false;

                while (P != nullptr) {
                    adrKabupaten foundKab = searchKabupaten(S, P->info.nama, namaTarget);
                    if (foundKab) {
                        cout << "DITEMUKAN: Kabupaten/Kota '" << foundKab->info.nama << "' di Provinsi " << P->info.nama << "." << endl;
                        found = true;
                        break;
                    }
                    P = P->next;
                }

                if (!found) {
                    cout << "TIDAK DITEMUKAN: Elemen '" << namaTarget << "' tidak ada." << endl;
                }
                break;
            }

            case 4:
                cout << "Masukkan Nama Provinsi yang akan dihapus: ";
                getline(cin, namaProvinsi);
                deleteProvinsi(S, namaProvinsi);
                break;

            case 5:
                cout << "Masukkan Nama Provinsi Induk: ";
                getline(cin, namaProvinsi);
                cout << "Masukkan Nama Kabupaten/Kota yang akan dihapus: ";
                getline(cin, namaKabupaten);
                deleteKabupaten(S, namaProvinsi, namaKabupaten);
                break;

            case 6:
                displayList(S);
                break;


            case 7:
                cout << "Program selesai." << endl;
                break;

            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }

    } while (choice != 7);

    return 0;
}
