#include <iostream>
#include <fstream> // Library krusial untuk membaca/menulis file
#include <string>

using namespace std;

// 1. Mendefinisikan blueprint data pemain (Struct)
struct Pemain {
    int id;
    string nama;
    int usia;
    string posisi;
    int stats[6]; // Array 1D di dalam struct untuk menyimpan 6 atribut teknis
    int overall;
};

// Konstanta untuk batas maksimal database (bisa disesuaikan)
const int MAKS_PEMAIN = 100; 

// 2. Fungsi Load Data: Membaca file dan memasukkannya ke Array of Struct
int loadDataDariFile(Pemain db[], string namaFile) {
    ifstream file(namaFile); // Membuka file untuk dibaca (Input File Stream)
    int jumlah = 0;

    // Pengecekan apakah file berhasil dibuka (handling error)
    if (!file.is_open()) {
        cout << "ERROR: File '" << namaFile << "' tidak ditemukan!\n";
        cout << "Pastikan file .txt berada di folder yang sama dengan file .cpp kalian.\n";
        return 0; // Mengembalikan 0 karena tidak ada data yang dimuat
    }

    // Membaca file kata per kata secara otomatis karena formatnya sudah rapi (dipisah spasi)
    while (file >> db[jumlah].id >> db[jumlah].nama >> db[jumlah].usia >> db[jumlah].posisi 
                >> db[jumlah].stats[0] >> db[jumlah].stats[1] >> db[jumlah].stats[2] 
                >> db[jumlah].stats[3] >> db[jumlah].stats[4] >> db[jumlah].stats[5] 
                >> db[jumlah].overall) {
        
        jumlah++; // Tambah counter jumlah pemain

        // Proteksi agar tidak error jika isi file melebihi kapasitas array
        if (jumlah >= MAKS_PEMAIN) {
            cout << "Peringatan: Kapasitas maksimal array tercapai!\n";
            break;
        }
    }

    file.close(); // Jangan lupa menutup file setelah selesai membaca
    return jumlah; // Mengembalikan total pemain yang berhasil dibaca
}

// 3. Fungsi sederhana untuk mengetes apakah data sudah masuk ke memori
void tampilkanSemuaPemain(Pemain db[], int totalPemain) {
    cout << "\n=== DATABASE SCOUTING PEMAIN ===\n";
    cout << "Total Pemain Dimuat: " << totalPemain << "\n\n";
    
    for (int i = 0; i < totalPemain; i++) {
        cout << "ID: " << db[i].id << " | Nama: " << db[i].nama 
             << " | Umur: " << db[i].usia << " | Posisi: " << db[i].posisi 
             << " | OVR: " << db[i].overall << "\n";
    }
    cout << "================================\n";
}

// 4. Program Utama
int main() {
    // Membuat array of struct yang akan menjadi "database sementara" di memori
    Pemain databasePemain[MAKS_PEMAIN];
    
    // Memanggil fungsi load data dan menyimpan jumlah pemain yang dimuat
    // Pastikan nama file sesuai dengan file txt yang kalian buat
    int totalData = loadDataDariFile(databasePemain, "database_pemain.txt");

    // Jika data berhasil dimuat, tampilkan ke layar
    if (totalData > 0) {
        tampilkanSemuaPemain(databasePemain, totalData);
    }

    return 0;
}