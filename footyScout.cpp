#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Library tambahan untuk merapikan spasi tabel (setw)

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

// ==========================================
// BAB 2: FILE I/O (Database Handler)
// ==========================================
// [SUDAH SELESAI] Fungsi dari Milestone 1 kalian
int loadDataDariFile(Pemain db[], string namaFile) {
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

// TODO (Untuk Anggota 1): Buat fungsi untuk menyimpan kembali data dari Array ke File .txt     ME
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
// BAB 3: ARRAY & TAMPILAN
// ==========================================
// Tampilan sudah diperbarui dengan iomanip agar berbentuk tabel rapi
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
}

// TODO (Untuk Anggota 1): Fungsi untuk input data pemain baru      
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

    cout << "Masukkan Posisi (GK/DF/MF/FW): ";
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
}
}

// ==========================================
// BAB 4 & 5: SEARCHING & SORTING
// ==========================================
// TODO (Untuk Anggota 2): Implementasi Searching      
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

        cout << "Masukkan posisi pemain (GK/DF/MF/FW): ";
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
}

// TODO (Untuk Anggota 2): Implementasi Sorting     
void urutkanPemain(Pemain db[], int totalPemain) {
    // 1. Gunakan algoritma Bubble Sort atau Selection Sort
    // 2. Tukar posisi struct pemain di dalam array berdasarkan atribut 'overall' tertinggi (Descending)
    // 3. Panggil fungsi tampilkanSemuaPemain() setelah selesai disortir
	if (totalPemain == 0){
		cout << "[ERROR] Belum ada data pemain yang dapat diurutkan! " << endl;
		return;
	}

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
		cout << "Data sudah diurutkan! " << endl;
		tampilkanSemuaPemain(db, totalPemain);
    
    
}

// ==========================================
// BAB 6: POINTER (Bandingkan 2 Pemain)
// ==========================================
// TODO (Untuk Anggota 3): Pass-by-reference dengan pointer   
void bandingkanPemain(Pemain *p1, Pemain *p2) {
    // Fungsi ini menerima ALAMAT memori dari dua pemain (bukan copy data)
    // 1. Tampilkan nama p1 dan p2
    // 2. Bandingkan siapa OVR yang lebih tinggi
    cout << ">> [Sistem]: Fitur Bandingkan Pemain (Pointer) belum diimplementasikan.\n";
}

// ==========================================
// BAB 7: FUNGSI REKURSIF (Prediksi Potensi)
// ==========================================
// TODO (Untuk Anggota 2/3): Fungsi memanggil dirinya sendiri       
double prediksiPotensi(double ratingSaatIni, int umurSaatIni, int sisaTahun) {
    // 1. Buat Base Case (kondisi berhenti saat sisaTahun == 0)
    // 2. Buat aturan tier pertumbuhan (umur < 22 tambah 3, umur > 30 kurang 1)
    // 3. Return pemanggilan fungsi ini kembali (Recursive Step)
    return ratingSaatIni; // Ini nilai sementara agar tidak error
}

// ==========================================
// FUNGSI UTAMA (MAIN PROGRAM)
// ==========================================
int main() {
    Pemain databasePemain[MAKS_PEMAIN];
    
    
    // Tahap 1: Load Data
    int totalData = loadDataDariFile(databasePemain, namaFile);
    if (totalData == 0) return 1; // Keluar jika gagal load

    int pilihan;
    // Tahap 2: Menu Interaktif
    do {
        cout << "\n===================================";
        cout << "\n       FOOTYSCOUT PRO SYSTEM       ";
        cout << "\n===================================\n";
        cout << "1. Lihat Semua Pemain\n";
        cout << "2. Tambah Pemain Baru\n";
        cout << "3. Cari Pemain (Searching)\n";
        cout << "4. Leaderboard OVR (Sorting)\n";
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
                tambahPemain(databasePemain, totalData);
                break;
            case 3:
                cariPemain(databasePemain, totalData);
                break;
            case 4:
                urutkanPemain(databasePemain, totalData);
                break;
            case 5:
                // Contoh hardcode pemanggilan pointer (nantinya minta input ID dari user)
                // &databasePemain[0] artinya kita mengirim alamat memori dari index ke-0
                bandingkanPemain(&databasePemain[0], &databasePemain[1]);
                break;
            case 6:
                // Contoh pemanggilan rekursif (nantinya terapkan ke pemain yang dipilih)
                cout << "\n>> [Sistem]: Fitur Simulasi Potensi belum diimplementasikan.\n";
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
