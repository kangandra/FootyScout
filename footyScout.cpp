#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 

using namespace std;

struct Pemain {
    int id;
    string nama;
    int usia;
    string posisi;
    int stats[6]; 
    int overall;
};

const int MAKS_PEMAIN = 100;
const string namaFile = "database_pemain.txt";

int loadDataDariFile(Pemain db[]) {
    ifstream file(namaFile);
    int jumlah = 0;
    if (!file.is_open()) return 0;

    while (file >> db[jumlah].id >> db[jumlah].nama >> db[jumlah].usia >> db[jumlah].posisi 
                >> db[jumlah].stats[0] >> db[jumlah].stats[1] >> db[jumlah].stats[2] 
                >> db[jumlah].stats[3] >> db[jumlah].stats[4] >> db[jumlah].stats[5] 
                >> db[jumlah].overall) {
        jumlah++;
        if (jumlah >= MAKS_PEMAIN) break;
    }
    file.close();
    return jumlah;
}

// fungsi untuk menyimpan kembali data dari Array ke File .txt
void simpanDataKeFile(Pemain db[], int totalPemain) {
    ofstream file(namaFile, ios::trunc);
    
    if (!file.is_open())
    {
        cout << "Sistem Error]: Gagal membuka file untuk menyimpan data!\n";
        return;
    }   
    for(int i = 0; i < totalPemain; i++){
        file << db[i].id << " " << db[i].nama << " " << db[i].usia << " " << db[i].posisi << " " << db[i].stats[0] << " " << db[i].stats[1] << " " << db[i].stats[2] << " " << db[i].stats[3] << " " << db[i].stats[4] << " " << db[i].stats[5] << " " << db[i].overall << endl;
    }
    file.close();
}

// ==========================================
// ARRAY & TAMPILAN
// ==========================================
void tampilkanSemuaPemain(Pemain db[], int totalPemain) {
    cout << "\n=== DATABASE SCOUTING PEMAIN (" << totalPemain << " Pemain) ===\n";
    cout << left << setw(5) << "ID" << setw(20) << "NAMA" << setw(6) << "UMUR" 
         << setw(8) << "POSISI" << setw(5) << "OVR" << "\n";
    cout << "--------------------------------------------------\n";
    
    for (int i = 0; i < totalPemain; i++) {
        cout << left << setw(5) << db[i].id 
             << setw(20) << db[i].nama 
             << setw(6) << db[i].usia 
             << setw(8) << db[i].posisi 
             << setw(5) << db[i].overall << "\n";
    }
    cout << "==================================================\n";
    system("pause");
}

//Fungsi untuk input data pemain baru      
void tambahPemain(Pemain db[], int &totalPemain) {
    if (totalPemain >= MAKS_PEMAIN) {
        cout << "[ERROR] Database pemain penuh!" << endl;
        return;
    }

    cout << "\n=== TAMBAH PEMAIN BARU ===" << endl;

    cout << "Masukkan ID Pemain      : ";
    cin >> db[totalPemain].id;

    cin.ignore();

    cout << "Masukkan Nama Pemain    : ";
    getline(cin, db[totalPemain].nama);

    cout << "Masukkan Usia Pemain    : ";
    cin >> db[totalPemain].usia;

    cout << "Masukkan Posisi : ";
    cin >> db[totalPemain].posisi;

    cout << "\nMasukkan Statistik Pemain" << endl;

    cout << "Pace      : ";
    cin >> db[totalPemain].stats[0];

    cout << "Shooting  : ";
    cin >> db[totalPemain].stats[1];

    cout << "Passing   : ";
    cin >> db[totalPemain].stats[2];

    cout << "Dribbling : ";
    cin >> db[totalPemain].stats[3];

    cout << "Defending : ";
    cin >> db[totalPemain].stats[4];

    cout << "Physical  : ";
    cin >> db[totalPemain].stats[5];

    db[totalPemain].overall =
        (db[totalPemain].stats[0] +
         db[totalPemain].stats[1] +
         db[totalPemain].stats[2] +
         db[totalPemain].stats[3] +
         db[totalPemain].stats[4] +
         db[totalPemain].stats[5]) / 6;

    totalPemain++;

    simpanDataKeFile(db, totalPemain);

    cout << "\n[SUKSES] Data pemain berhasil ditambahkan!" << endl;
    system("pause");
}

// ==========================================
// EDIT & HAPUS DATA PEMAIN (CRUD)
// ==========================================


void hapusPemain(Pemain db[], int &totalPemain) {
    if (totalPemain == 0) {
        cout << "[ERROR] Database pemain masih kosong!" << endl;
        return;
    }

    int idHapus;
    cout << "\n=== HAPUS DATA PEMAIN ===" << endl;
    cout << "Masukkan ID Pemain yang ingin dihapus: ";
    cin >> idHapus;

    int index = -1;
    for (int i = 0; i < totalPemain; i++) {
        if (db[i].id == idHapus) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        string namaTerhapus = db[index].nama;

        // Logika Array Shifting: Menggeser sisa data ke kiri untuk menimpa data yang dihapus
        for (int i = index; i < totalPemain - 1; i++) {
            db[i] = db[i + 1];
        }
        
        totalPemain--; 

        simpanDataKeFile(db, totalPemain);
        cout << "\n[SUKSES] Data pemain " << namaTerhapus << " berhasil dihapus permanen!" << endl;
    } else {
        cout << "[ERROR] Pemain dengan ID " << idHapus << " tidak ditemukan!" << endl;
    }
}

// ==========================================
// Implementasi Searching
// ==========================================   
void tampilDataCari(Pemain p) {
    cout << "\n=== DATA PEMAIN ===" << endl;
    cout << "ID       : " << p.id << endl;
    cout << "Nama     : " << p.nama << endl;
    cout << "Usia     : " << p.usia << endl;
    cout << "Posisi   : " << p.posisi << endl;
    cout << "Pace     : " << p.stats[0] << endl;
    cout << "Shooting : " << p.stats[1] << endl;
    cout << "Passing  : " << p.stats[2] << endl;
    cout << "Dribbling: " << p.stats[3] << endl;
    cout << "Defending: " << p.stats[4] << endl;
    cout << "Physical : " << p.stats[5] << endl;
    cout << "Overall  : " << p.overall << endl;
}

void urutID(Pemain db[], int totalPemain) {
    for (int i = 0; i < totalPemain - 1; i++) {
        for (int j = 0; j < totalPemain - i - 1; j++) {
            if (db[j].id > db[j + 1].id) {
                Pemain temp = db[j];
                db[j] = db[j + 1];
                db[j + 1] = temp;
            }
        }
    }
}

int cariID(Pemain db[], int totalPemain, int idCari) {
    int kiri = 0;
    int kanan = totalPemain - 1;

    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;

        if (db[tengah].id == idCari) {
            return tengah;
        } else if (idCari < db[tengah].id) {
            kanan = tengah - 1;
        } else {
            kiri = tengah + 1;
        }
    }

    return -1;
}

void cariPemain(Pemain db[], int totalPemain) {
    int pilih;

    if (totalPemain == 0) {
        cout << "[ERROR] Data pemain masih kosong!" << endl;
        return;
    }

    cout << "\n=== CARI PEMAIN ===" << endl;
    cout << "1. Cari berdasarkan ID" << endl;
    cout << "2. Cari berdasarkan nama" << endl;
    cout << "3. Cari berdasarkan posisi" << endl;
    cout << "4. Cari Pace minimal" << endl;
    cout << "Pilih: ";
    cin >> pilih;

    if (pilih == 1) {
        int idCari;

        urutID(db, totalPemain);

        cout << "Masukkan ID pemain: ";
        cin >> idCari;

        int hasil = cariID(db, totalPemain, idCari);

        if (hasil != -1) {
            tampilDataCari(db[hasil]);
        } else {
            cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
        }

    } else if (pilih == 2) {
        string namaCari;
        bool ketemu = false;

        cout << "Masukkan nama pemain: ";
        cin.ignore();
        getline(cin, namaCari);

        for (int i = 0; i < totalPemain; i++) {
            if (db[i].nama == namaCari) {
                tampilDataCari(db[i]);
                ketemu = true;
            }
        }

        if (!ketemu) {
            cout << "Pemain dengan nama tersebut tidak ditemukan." << endl;
        }

    } else if (pilih == 3) {
        string posisiCari;
        bool ketemu = false;

        cout << "Masukkan posisi pemain : ";
        cin >> posisiCari;

        cout << "\n=== HASIL PENCARIAN POSISI " << posisiCari << " ===" << endl;

        for (int i = 0; i < totalPemain; i++) {
            if (db[i].posisi == posisiCari) {
                cout << db[i].id << " - " << db[i].nama
                     << " | Posisi: " << db[i].posisi
                     << " | Overall: " << db[i].overall << endl;
                ketemu = true;
            }
        }

        if (!ketemu) {
            cout << "Tidak ada pemain dengan posisi tersebut." << endl;
        }

    } else if (pilih == 4) {
        int batasPace;
        bool ketemu = false;

        cout << "Masukkan minimal Pace: ";
        cin >> batasPace;

        cout << "\n=== HASIL PENCARIAN PACE >= " << batasPace << " ===" << endl;

        for (int i = 0; i < totalPemain; i++) {
            if (db[i].stats[0] >= batasPace) {
                cout << db[i].id << " - " << db[i].nama
                     << " | Posisi: " << db[i].posisi
                     << " | Pace: " << db[i].stats[0]
                     << " | Overall: " << db[i].overall << endl;
                ketemu = true;
            }
        }

        if (!ketemu) {
            cout << "Tidak ada pemain yang sesuai kriteria." << endl;
        }

    } else {
        cout << "Pilihan tidak valid." << endl;
    }
    system("pause");
}

// ==========================================
//                  SORTING
// ==========================================
void urutkanPemain(Pemain db[], int totalPemain) {
	if (totalPemain == 0){
		cout << "[ERROR] Belum ada data pemain yang dapat diurutkan! " << endl;
		return;
	}

    int subPilihan;
    cout << "\n--- MENU SORTING DATA ---\n";
    cout << "1. Urutkan berdasarkan Overall (OVR) - Tertinggi ke Terendah\n";
    cout << "2. Urutkan berdasarkan ID Pemain - Terkecil ke Terbesar\n";
    cout << "3. Batal / Kembali ke Menu Utama\n";
    cout << "Pilih opsi (1-3): ";
    cin >> subPilihan;

    if (subPilihan == 1){
        for (int i = 0; i < totalPemain - 1; i++){
		    for (int j = 0; j < totalPemain - i - 1; j++){

			if(db[j].overall > db[j + 1].overall){
				Pemain temp = db[j];
				db[j] = db[j + 1];
				db[j + 1] = temp;
				}
			}
		}
		simpanDataKeFile(db, totalPemain);
		cout << "Data sudah diurutkan berdasarkan OVR! " << endl;
		tampilkanSemuaPemain(db, totalPemain);
    }else if (subPilihan == 2) {
        // Sorting ID (Ascending) dengan memanggil fungsi urutID yang sudah ada
        urutID(db, totalPemain);
        simpanDataKeFile(db, totalPemain);
        cout << "\n[SUKSES] Data sudah diurutkan berdasarkan ID Pemain!\n";
        tampilkanSemuaPemain(db, totalPemain);

    } else if (subPilihan == 3) {
        cout << ">> Membatalkan tindakan, kembali ke menu utama...\n";

    } else {
        cout << ">> [ERROR] Pilihan sub-menu tidak valid!\n";
    }
}
    
    

// ==========================================
// BAB 6: POINTER (Bandingkan 2 Pemain)
// ==========================================
// TODO (Untuk Anggota 3): Pass-by-reference dengan pointer   
void bandingkanPemain(Pemain *p1, Pemain *p2) {
    cout << "\n==================================================\n";
    cout << "     PERBANDINGAN PEMAIN (ANALISIS POINTER)       \n";
    cout << "==================================================\n";
    
    cout << left << setw(18) << "Atribut" 
         << setw(16) << p1->nama 
         << setw(16) << p2->nama << "\n";
    cout << "--------------------------------------------------\n";
    cout << left << setw(18) << "Usia" 
         << setw(16) << p1->usia 
         << setw(16) << p2->usia << "\n";
    cout << left << setw(18) << "Posisi" 
         << setw(16) << p1->posisi 
         << setw(16) << p2->posisi << "\n";
    cout << left << setw(18) << "Overall (OVR)" 
         << setw(16) << p1->overall 
         << setw(16) << p2->overall << "\n";
    cout << "--------------------------------------------------\n";
}

// ==========================================
// FUNGSI REKURSIF (Prediksi Potensi)
// ==========================================    
double prediksiPotensi(double ratingSaatIni, int umurSaatIni, int sisaTahun) {
    if (sisaTahun == 0) {
        return ratingSaatIni;
    }

    if (umurSaatIni < 22) {
        ratingSaatIni += 3;
    }
    else if (umurSaatIni <= 30) {
        ratingSaatIni += 1;
    }
    else {
        ratingSaatIni -= 1;
    }

    return prediksiPotensi(
        ratingSaatIni,
        umurSaatIni + 1,
        sisaTahun - 1
    );

}

void bantuPrediksi(Pemain db[], int totalData){
    if (totalData == 0) {
        cout << "[ERROR] Data pemain kosong!\n";
        return;
    }

    int idCari;
    cout << "\n=== SIMULASI POTENSI PEMAIN ===\n";
    cout << "Masukkan ID pemain: ";
    cin >> idCari;

    urutID(db, totalData);

    int index = cariID(db, totalData, idCari);

    if (index == -1) {
        cout << "Pemain tidak ditemukan!\n";
    }
    else {
        int tahun;

        cout << "\nNama Pemain : " << db[index].nama << endl;
        cout << "Usia Saat Ini : " << db[index].usia << endl;
        cout << "OVR Saat Ini  : " << db[index].overall << endl;

        cout << "\nPrediksi berapa tahun ke depan? ";
        cin >> tahun;

        double hasil = prediksiPotensi(
            db[index].overall,
            db[index].usia,
            tahun
        );

        cout << "\n===== HASIL SIMULASI =====\n";
        cout << "Nama Pemain          : "
             << db[index].nama << endl;

        cout << "OVR Saat Ini         : "
             << db[index].overall << endl;

        cout << "Usia Saat Ini        : "
             << db[index].usia << endl;

        cout << "Usia Setelah Simulasi: "
             << db[index].usia + tahun << endl;

        cout << "Prediksi OVR         : "
             << hasil << endl;

        cout << "===========================\n";
    }
    system("pause");
}



int main() {
    Pemain databasePemain[MAKS_PEMAIN];
    
    int totalData = loadDataDariFile(databasePemain);
    if (totalData == 0) return 1; 

    int pilihan;
    do {
		system("cls");
        cout << "\n===================================";
        cout << "\n       FOOTYSCOUT PRO SYSTEM       ";
        cout << "\n===================================\n";
        cout << "1. Lihat Semua Pemain\n";
        cout << "2. Manajemen pemain (hapus/tambah)\n";
        cout << "3. Cari Pemain (Searching)\n";
        cout << "4. Leaderboard OVR/ID (Sorting)\n";
        cout << "5. Bandingkan 2 Pemain (Pointer)\n";
        cout << "6. Simulasi Potensi (Rekursif)\n";
        cout << "7. Save & Exit\n";
        cout << "Pilih menu (1-7): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanSemuaPemain(databasePemain, totalData);
                cin.ignore(); 
				cin.get();    
                break;
            case 2:
                int subPilihan;
                cout << "\n--- MANAJEMEN PEMAIN ---\n";
                cout << "1. Tambah Pemain Baru\n";
                cout << "2. Hapus Data Pemain\n";
                cout << "3. Batal / Kembali ke Menu Utama\n";
                cout << "Pilih opsi (1-3): ";
                cin >> subPilihan;

                if (subPilihan == 1) {
                    tambahPemain(databasePemain, totalData);
                } else if (subPilihan == 2) {
                    hapusPemain(databasePemain, totalData);
                } else if (subPilihan == 3) {
                    cout << ">> Membatalkan tindakan, kembali ke menu utama...\n";
                } else {
                    cout << ">> [Error] Pilihan sub-menu tidak valid!\n";
                }
                break;
            case 3:
                cariPemain(databasePemain, totalData);
                break;
            case 4:
                urutkanPemain(databasePemain, totalData);
                break;
            case 5:{
                int id1, id2;
                cout << "\n--- MENU PERBANDINGAN PEMAIN ---\n";
                cout << "Masukkkan ID pemain pertama : "; cin >> id1;
                cout << "Masukkkan ID pemain kedua : "; cin >> id2;

                Pemain *ptrPemain1 = nullptr;
                Pemain *ptrPemain2 = nullptr;

                for (int i = 0; i < totalData; i++)
                {
                    if (databasePemain[i].id == id1)
                    {
                        ptrPemain1 = &databasePemain[i];
                    }
                    if (databasePemain[i].id == id2)
                    {
                        ptrPemain2 = &databasePemain[i];
                    }
                }
                if (ptrPemain1 != nullptr && ptrPemain2 != nullptr)
                {
                    bandingkanPemain (ptrPemain1, ptrPemain2);
                }else{
                    cout << "\n>> Proses gagal. Pastikan kedua ID pemain terdaftar di database!\n";
                }
                
                cin.ignore(); 
                cin.get();
                break;
            }
            case 6:
                bantuPrediksi(databasePemain, totalData);
                break;
            case 7:
                simpanDataKeFile(databasePemain, totalData);
                cout << "Data tersimpan. Keluar dari program...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 7);

    return 0;
}
