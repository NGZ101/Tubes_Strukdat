// Irfan Thoriq Habibi - 2311102131
// Naufal Geraldo Putra Pramudianartono - 2311102154

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;
//Jumlah array
const int MAX_SIZE = 10;
//data array yang tersimpan didalam program
int harga_game[MAX_SIZE] = {275000, 270000, 150000, 90000, 67000, 79000, 100000, 50000, 120000, 200000};
string nama_game[MAX_SIZE] = {"Gta V", "Resident Evil 4", "PUBG", "VALORANT", "Genshin Impact", "Honkai Star Rail", "Wuthering Waves", "Mobile Legends", "Blue Archive", "Arknight"};
//berfungsi untuk menampilkan waktu secara real time
time_t var_detik = time(0);
string var_waktu = ctime(&var_detik);

// Struktur data untuk menyimpan informasi game
struct Game {//tipe data kompleks yang berfungsi untuk menyimpan data game
    string nama;//tipe data primitif untuk menyimpan nama
    int harga;//tipe data primitif untuk menyimpan harga
    Game* next;
    Game(string nama, int harga) : nama(nama), harga(harga), next(nullptr) {}
};

// Pointer untuk linked list
Game* head = nullptr;

// Fungsi untuk inisialisasi linked list
void initializeList() {
    for (int i = 0; i < MAX_SIZE; ++i) {//looping pada array
        Game* game = new Game(nama_game[i], harga_game[i]);//mencetak node baru
        game->next = head;//mengatur pointer next menuju head
        head = game;//memperbarui head
    }
}

// Fungsi untuk membebaskan memori yang dialokasikan
void clearList() {
    Game* current = head;//pointer current diinisialisasi ke head
    while (current != nullptr) {//looping node
        Game* temp = current;
        current = current->next;
        delete temp;//hapus node yang diminta
    }
    head = nullptr;//mengatur head agar dapat kembali ke nullptr
}

// Fungsi untuk menambahkan data game ke linked list
void JualGame(string nama, int harga) {
    Game* current = head;//pointer current diinisialisasi ke node pertama (head)
    while (current != nullptr) {//memeriksa duplikasi
        if (current->harga == harga && current->nama == nama) {
            cout << "Game dengan nama " << nama << " dan harga " << harga << " sudah ada." << endl;
            return;
        }
        current = current->next;//pindah ke node berikutnya
    }
    Game* game = new Game(nama, harga);//menambahkan game baru
    game->next = head;
    head = game;
    cout << "Game " << nama << " dengan harga Rp." << harga << " berhasil ditambahkan." << endl;
}
// Fungsi untuk membeli game berdasarkan nama dan mencetak struk pembayaran
void BeliGame(string nama, string orang, int bayar) {
    Game* current = head;//inisialisasi pointer current menuju head
    while (current != nullptr) {//pencarian game
        if (current->nama == nama) {//struk pembelian
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
            cout << "=     Terima Kasih Telah Membeli Game Di GAME CENTER IN!     =" << endl;
            cout << "==============================================================" << endl;
            return;
        }
        current = current->next;//pindah ke node berikutnya
    }
    //pesan yang akan muncul jika game yang ingin dibeli tidak tersedia
    cout << "Game dengan nama " << nama << " tidak tersedia!" << endl;
}

// Fungsi untuk menghapus data game berdasarkan nama
void HapusGame(string nama) {
    Game* current = head;//inisialisasi pointer current menuju head
    Game* prev = nullptr;//inisialisasi pointer prev menuju nullptr (simpan node sebelumnya)
    while (current != nullptr) {//memastikan kondisi current tetapi looping selama tidak menuju nullptr
        if (current->nama == nama) {//memeriksa nama game
            if (prev == nullptr) {//menghapus node/game
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Game dengan nama " << nama << " telah dihapus!" << endl;
            return;
        }
        prev = current;//pindah ke node selanjutnya
        current = current->next;
    }//pesan yang akan muncul jika game yang ingin dihapus tidak tersedia
    cout << "Game dengan nama " << nama << " tidak tersedia!" << endl;
}
// Fungsi untuk mencari game berdasarkan nama
void CariGame(string nama) {
    Game* current = head;//pointer current diinisialisasi menuju head
    while (current != nullptr) {//memastikan kondisi current tetapi looping selama tidak menuju nullptr
        if (current->nama == nama) {//memeriksa nama game
            cout << "Game ditemukan!" << endl;
            cout << "Nama Game : " << current->nama << endl;
            cout << "Harga     : Rp." << current->harga << endl;
            return;
        }
        current = current->next;//next node
    }//pesan yang akan muncul jika game yang ingin dicari tidak tersedia
    cout << "Game dengan nama " << nama << " tidak tersedia!" << endl;
}
// Fungsi untuk menampilkan seluruh data game dalam linked list
void TampilkanSemuaGame() {
    cout << "==============================================================" << endl;
    cout << "=                         SEMUA GAME                         =" << endl;
    cout << "==============================================================" << endl;
    cout << setw(25) << left << "Nama Game" << setw(15) << left << "Harga" << endl;
    cout << "==============================================================" << endl;
    Game* current = head;//inisialisasi pointer current menuju head
    while (current != nullptr) {//memastikan kondisi current tetapi looping selama tidak menuju nullptr
        cout << setw(25) << left << current->nama << "Rp." << current->harga << endl;
        current = current->next;// next node
    }
    cout << "==============================================================" << endl;
}

// Fungsi utama
int main() {
    initializeList();

    cout << "==============================================================" << endl;
    cout << "=                       GAME CENTER IN                       =" << endl;
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
                JualGame(nama, harga);
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
                HapusGame(nama);
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
                cin.ignore();
                getline(cin, nama);
                BeliGame(nama, orang, bayar);
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
                CariGame(nama);
                break;
            }
            case 5: {
                TampilkanSemuaGame();
                break;
            }
            case 6:
                cout << "==============================================================" << endl;
                cout << "=         Terima Kasih Telah Menggunakan Program Ini         =" << endl;
                cout << "==============================================================" << endl;
                clearList();
                return 0;
            default:
                cout << "==============================================================" << endl;
                cout << "=    Input tidak valid. Mohon masukkan angka 1 hingga 6.     =" << endl;
                cout << "==============================================================" << endl;
        }
    }
}