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
    // 1. Minta user memasukkan data (cin)
    // 2. Simpan di index db[totalPemain]
    // 3. Jangan lupa tambahkan totalPemain++
    cout << ">> [Sistem]: Fitur Tambah Pemain belum diimplementasikan.\n";
}

// ==========================================
// BAB 4 & 5: SEARCHING & SORTING
// ==========================================
// TODO (Untuk Anggota 2): Implementasi Searching      
void cariPemain(Pemain db[], int totalPemain) {
    // 1. Minta input user (Cari berdasarkan Nama atau ID?)
    // 2. Lakukan Linear Search atau Binary Search
    // 3. Tampilkan data pemain jika ketemu, jika tidak tampilkan error
    cout << ">> [Sistem]: Fitur Cari Pemain belum diimplementasikan.\n";
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
