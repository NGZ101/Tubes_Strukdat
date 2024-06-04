#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 10;
int harga_game[MAX_SIZE] = {275000, 270000, 150000, 90000, 67000, 79000, 100000, 50000, 120000, 200000};
string nama_game[MAX_SIZE] = {"Gta V", "Resident Evil 4", "PUBG", "VALORANT", "Genshin Impact", "Honkai Star Rail", "Wuthering Waves", "Mobile Legends", "Blue Archive", "Arknight"};
time_t var_detik = time(0);
string var_waktu = ctime(&var_detik);

// Fungsi hash sederhana untuk menghasilkan indeks dari kunci (harga)
int hash_func(int key) {
    return key % MAX_SIZE;
}

// Struktur data untuk menyimpan informasi game
struct Game {
    string nama;
    int harga;
    Game* next;
    Game(string nama, int harga) : nama(nama), harga(harga), next(nullptr) {}
};

// Pointer array untuk tabel hash
Game* table[MAX_SIZE];

// Fungsi untuk inisialisasi tabel hash
void initializeTable() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        table[i] = nullptr;
    }

    // Tambahkan data game yang sudah tersedia tanpa mencetak pesan
    for (int i = 0; i < MAX_SIZE; ++i) {
        Game* game = new Game(nama_game[i], harga_game[i]);
        int index = hash_func(harga_game[i]);
        game->next = table[index];
        table[index] = game;
    }
}

// Fungsi untuk membebaskan memori yang dialokasikan
void clearTable() {
    for (int i = 0; i < MAX_SIZE; ++i) {
        Game* current = table[i];
        while (current != nullptr) {
            Game* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}

// Fungsi untuk menambahkan data game ke hashtable
void addGame(string nama, int harga) {
    int index = hash_func(harga);
    Game* current = table[index];
    while (current != nullptr) {
        if (current->harga == harga && current->nama == nama) {
            cout << "Game dengan nama " << nama << " dan harga " << harga << " sudah ada." << endl;
            return;
        }
        current = current->next;
    }
    Game* game = new Game(nama, harga);
    game->next = table[index];
    table[index] = game;
    cout << "Game " << nama << " dengan harga Rp." << harga << " berhasil ditambahkan." << endl;
}

// Fungsi untuk menghapus data game berdasarkan nama
void removeGame(string nama) {
    string nama_lower = nama;
    transform(nama_lower.begin(), nama_lower.end(), nama_lower.begin(), ::tolower);

    for (int i = 0; i < MAX_SIZE; ++i) {
        Game* current = table[i];
        Game* prev = nullptr;
        while (current != nullptr) {
            string current_nama_lower = current->nama;
            transform(current_nama_lower.begin(), current_nama_lower.end(), current_nama_lower.begin(), ::tolower);

            if (current_nama_lower == nama_lower) {
                if (prev == nullptr) {
                    table[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Game dengan nama " << nama << " telah dihapus!" << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    cout << "Game dengan nama " << nama << " tidak tersedia!" << endl;
}

// Fungsi untuk membeli game berdasarkan nama dan mencetak struk pembayaran
void beliGame(string nama, string orang, int bayar) {
    string nama_lower = nama;
    transform(nama_lower.begin(), nama_lower.end(), nama_lower.begin(), ::tolower);

    for (int i = 0; i < MAX_SIZE; ++i) {
        Game* current = table[i];
        Game* prev = nullptr;
        while (current != nullptr) {
            string current_nama_lower = current->nama;
            transform(current_nama_lower.begin(), current_nama_lower.end(), current_nama_lower.begin(), ::tolower);

            if (current_nama_lower == nama_lower) {
                if (prev == nullptr) {
                    table[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                cout << "==============================================================" << endl;
                cout << "=                       STRUK PEMBELIAN                      =" << endl;
                cout << "==============================================================" << endl;
                cout << "Nama Pembeli: ";
                cin.ignore();
                getline(cin, orang);
                cout << "Nama Game : " << current->nama << endl;
                cout << "Harga     : Rp." << current->harga << endl;
                cout << "Uang      : Rp."; cin >> bayar;
                int kembalian = bayar - current->harga;
                cout << "Kembalian : Rp." << bayar << " - " << "Rp." << current->harga << " = Rp." << kembalian << endl;
                cout << endl;
                cout << "Purwokerto, " << var_waktu << endl;
                cout << "==============================================================" << endl;
                cout << "      Terima Kasih Telah Membeli Game Di GAME CENTER IN!      " << endl;
                cout << "==============================================================" << endl;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    cout << "Game dengan nama " << nama << " tidak tersedia!" << endl;
}

// Fungsi untuk mencari game berdasarkan nama
void cariGame(string nama) {
    string nama_lower = nama;
    transform(nama_lower.begin(), nama_lower.end(), nama_lower.begin(), ::tolower);

    for (int i = 0; i < MAX_SIZE; ++i) {
        Game* current = table[i];
        while (current != nullptr) {
            string current_nama_lower = current->nama;
            transform(current_nama_lower.begin(), current_nama_lower.end(), current_nama_lower.begin(), ::tolower);

            if (current_nama_lower == nama_lower) {
                cout << "Game ditemukan!" << endl;
                cout << "Nama Game : " << current->nama << endl;
                cout << "Harga     : Rp." << current->harga << endl;
                return;
            }
            current = current->next;
        }
    }
    cout << "Game dengan nama " << nama << " tidak tersedia!" << endl;
}

// Fungsi untuk menampilkan seluruh data game dalam hashtable
void tampilkanSemuaGame() {
    cout << "==============================================================" << endl;
    cout << "=                         SEMUA GAME                         =" << endl;
    cout << "==============================================================" << endl;
    cout << setw(25) << left << "Nama Game" << setw(15) << left << "Harga" << endl;
    cout << "==============================================================" << endl;
    for (int i = 0; i < MAX_SIZE; ++i) {
        Game* current = table[i];
        while (current != nullptr) {
            cout << setw(25) << left << current->nama << "Rp." << current->harga << endl;
            current = current->next;
        }
    }
    cout << "==============================================================" << endl;
}

// Fungsi utama
int main() {
    initializeTable();

    cout << "==============================================================" << endl;
    cout << "=                      GAME CENTER IN                        =" << endl;
    cout << "==============================================================" << endl;
    while (true) {
        cout << "=============================" << endl;
        cout << "=            MENU           =" << endl;
        cout << "=============================" << endl;
        cout << "1. Jual Game" << endl;
        cout << "2. Hapus Game" << endl;
        cout << "3. Beli Game" << endl;
        cout << "4. Cari Game" << endl;
        cout << "5. Tampilkan Semua Game" << endl;
        cout << "6. Keluar" << endl;
        cout << "Masukkan pilihan anda: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "==============================================================" << endl;
                cout << "=                    JUAL GAME BARU                          =" << endl;
                cout << "==============================================================" << endl;
                string nama;
                int harga;
                cout << "Inputkan Nama Game: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Inputkan Harga Game: ";
                cin >> harga;
                addGame(nama, harga);
                break;
            }
            case 2: {
                cout << "===============================================================" << endl;
                cout << "=                        HAPUS GAME                           =" << endl;
                cout << "===============================================================" << endl;
                string nama;
                cout << "Inputkan Nama Game yang akan dihapus: ";
                cin.ignore();
                getline(cin, nama);
                removeGame(nama);
                break;
            }
            case 3: {
                cout << "==============================================================" << endl;
                cout << "=                        BELI GAME                           =" << endl;
                cout << "==============================================================" << endl;
                string nama;
                string orang;
                int bayar;
                cout << "Inputkan Nama Game yang akan dibeli: ";
                cin.ignore(); // Mengabaikan karakter newline yang tersisa
                getline(cin, nama);
                beliGame(nama, orang, bayar);
                break;
            }
            case 4: {
                cout << "==============================================================" << endl;
                cout << "=                        CARI GAME                           =" << endl;
                cout << "==============================================================" << endl;
                string nama;
                cout << "Inputkan Nama Game yang akan dicari: ";
                cin.ignore();
                getline(cin, nama);
                cariGame(nama);
                break;
            }
            case 5: {
                tampilkanSemuaGame();
                break;
            }
            case 6:
                cout << "==============================================================" << endl;
                cout << "=         Terima Kasih Telah Menggunakan Program Ini         =" << endl;
                cout << "==============================================================" << endl;
                clearTable();
                return 0;
            default:
                cout << "==============================================================" << endl;
                cout << "=    Input tidak valid. Mohon masukkan angka 1 hingga 6.     =" << endl;
                cout << "==============================================================" << endl;
        }
    }
}