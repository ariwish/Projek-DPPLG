/*
 * TO FIX:
 * sign up dengan username admin (no warning/apapun)
 *
 */


#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define RESET       "\033[0m"
#define TEBAL       "\033[1m"
#define MERAH       "\033[91m"
#define HIJAU       "\033[92m"
#define KUNING      "\033[93m"
#define CYAN        "\033[96m"
#define PUTIH       "\033[97m"
#define UNGU        "\033[95m"
#define PINK        "\033[38;5;206m"
#define ORANGE      "\033[38;5;214m"
#define BIRU        "\033[94m"
#define CLEAR       "\033[2J\033[3J\033[H"

string currentUser;
map<string, string> akun = {
    {"Pak Dipta",   "admin123"},
    {"Pak Ngurah",  "jingkrakJingkrik"},
    {"Pak Dhanan",  "PipInstallMinecraft"},
    {"Pak Mahesa",  "liverpool"},
    {"Pak Arga",    "RRQ#7"},
    {"Pak Okan",    "akuCintaEvernight"}
};

void garis()       { cout << CYAN "=======================================================================" RESET "\n"; }
void garis_tabel() { cout << CYAN "+-------------+---------------------+-----------+--------------------+" RESET "\n"; }

void clearScreen(){
    cout << CLEAR;
}

string lowercase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int menuAkhir(bool adaUlang) {
    int pilih;
    while (true) {
        garis();
        cout << KUNING "Program selesai. Pilih aksi berikutnya:\n" RESET;
        if (adaUlang) {
            cout << "1. " UNGU "Home\n" RESET
                 << "2. " PINK "Ulang\n" RESET
                 << "3. " MERAH "Exit\n" RESET;
        } else {
            cout << "1. " UNGU "Home\n" RESET
                 << "2. " MERAH "Exit\n" RESET;
        }
        garis();
        cout << ORANGE "Pilih: " RESET;
        cin >> pilih;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MERAH "Input harus angka!\n" RESET;
            continue;
        }
        cin.ignore();

        if (adaUlang && pilih >= 1 && pilih <= 3) {
            return pilih;
        }
        if (!adaUlang && (pilih == 1 || pilih == 2)) {
            return pilih;
        }

        cout << MERAH "Pilihan tidak valid!\n" RESET;
    }
}

// Login
bool login() {
    clearScreen();
    int attempt = 0;
    while (attempt < 3) {
        cout << "\n";
        garis();
        cout << PUTIH TEBAL "\t\t\t       LOGIN\n" RESET;
        garis();

        string username, password;

        cout << "Username : ";
        getline(cin, username);
        cout <<  "Password : " ;
        getline(cin, password);

        if (username.empty() || password.empty()) {
            cout << MERAH "\n!X! Username atau Password tidak boleh kosong!\n" RESET;
            attempt++;
            continue;
        }
        if (akun.count(username) && akun[username] == password) {
            currentUser = username;
            cout << HIJAU "\n!V! Login berhasil! Selamat datang, " << currentUser << "\n";
            return true;
        }
        attempt++;
        cout << MERAH "\n!X! Login gagal! Percobaan ke-" << attempt << RESET "\n";
    }
    cout << MERAH "\n!X! Anda sudah mencoba 3 kali.\n" RESET;
    return false;
}

// Sign Up
void signup() {
    clearScreen();
    cout << endl;
    garis();
    cout << PUTIH TEBAL "\t\t\t       SIGN UP\n" RESET;
    garis();

    string usernameIn, passwordIn;
    cout << "Buat Username : ";
    getline(cin, usernameIn);
    cout << "Buat Password : ";
    getline(cin, passwordIn);

    if (usernameIn.empty() || passwordIn.empty()) {
        cout << MERAH "\n!X! Tidak boleh kosong!\n" RESET;
        return;
    }
    if (akun.count(usernameIn)) {
        cout << MERAH "\n!X! Username sudah digunakan!\n" RESET;
        return;
    }
    akun[usernameIn] = passwordIn;
    cout << HIJAU "\n!V! Akun berhasil dibuat!\n" RESET;
}

// Search Jadwal
void searchMP(vector<string>& hari, vector<vector<string>>& mapel,
              vector<vector<string>>& guru,  vector<vector<string>>& jam,
              vector<vector<string>>& note) {
    clearScreen();
    int pilih;
    while (true) {
        garis();
        cout << TEBAL CYAN "\t\t\t SEARCH JADWAL\n" RESET;
        garis();
        cout << "1. " UNGU "Home\n" RESET
             << "2. " HIJAU "Lanjut\n" RESET;
        cout <<  "Pilih: ";
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MERAH "Input harus angka!\n" RESET;
            continue;
        }
        cin.ignore();
        if (pilih == 1){
            return;
        }
        if (pilih == 2){
            break;
        }
        cout << MERAH "Pilihan tidak valid!\n" RESET;
    }

    string lagi;
    do {
        string input;
        cout << ORANGE "\nMata Pelajaran apa yang ingin kamu cari? " RESET;
        getline(cin, input);
        string cariMp = lowercase(input);
        garis();
        bool ketemu = false;

        for (int i = 0; i < (int)mapel.size(); i++)
            for (int j = 0; j < (int)mapel[i].size(); j++) {
                string cur = lowercase(mapel[i][j]);
                if (cur == cariMp || cur.find(cariMp) != string::npos) {
                    cout << HIJAU "\n[Ditemukan pada hari " << KUNING << hari[i] << HIJAU "]\n" RESET;
                    cout << BIRU "Mata Pelajaran : " RESET << KUNING << mapel[i][j] << RESET "\n";
                    cout << BIRU "Guru           : " RESET << (j < (int)guru[i].size() ? guru[i][j] : "-") << "\n";
                    cout << BIRU "Jam            : " RESET << (j < (int)jam[i].size()  ? jam[i][j]  : "-") << "\n";
                    cout << BIRU "Catatan        : " RESET << (j < (int)note[i].size() ? note[i][j] : "-") << "\n";
                    ketemu = true;
                }
            }

        if (!ketemu)
            cout << MERAH "Mata pelajaran tidak ditemukan.\n" RESET;
        garis();

        do {
            cout << KUNING "Apakah anda ingin mencari Mata Pelajaran lain? (y/n): " RESET;
            cin >> lagi;
            cin.ignore();
            if (lowercase(lagi) != "y" && lowercase(lagi) != "n")
                cout << MERAH "Pilih opsi y atau n!\n" RESET;
        } while (lowercase(lagi) != "y" && lowercase(lagi) != "n");

    } while (lowercase(lagi) == "y");

    int aksi = menuAkhir(true);
    if (aksi == 2){
        searchMP(hari, mapel, guru, jam, note);
    } else if (aksi == 3){
        exit(0);
    }
}

// Tambah Jadwal
void tambahMP(vector<string>& hari, vector<vector<string>>& mapel,
              vector<vector<string>>& guru,  vector<vector<string>>& jam,
              vector<vector<string>>& note) {
    clearScreen();
    int pilih;
    while (true) {
        garis();
        cout << TEBAL CYAN "\t\t\t TAMBAH JADWAL\n" RESET;
        garis();
        cout << "1. " UNGU "Home\n" RESET
             << "2. " HIJAU "Lanjut\n" RESET;
        cout << ORANGE "Pilih: " RESET;
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MERAH "Input harus angka!\n" RESET;
            continue;
        }
        cin.ignore();
        if (pilih == 1){
            return;
        }
        if (pilih == 2){
            break;
        }
        cout << MERAH "Pilihan tidak valid!\n" RESET;
    }

    string lagi;
    do {
        int h;
        cout << "\n";
        while (true) {
            for (int i = 0; i < (int)hari.size(); i++)
                cout << i + 1 << ". " UNGU << hari[i] << RESET "\n";
            cout << ORANGE "Pilih hari: " RESET;
            cin >> h;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << MERAH "Input harus angka!\n" RESET;
                continue;
            }

            if (h < 1 || h > (int)hari.size()) {
                cout << MERAH "Tidak valid!\n" RESET;
                continue;
            }

            cin.ignore();
            break;
        }

        int i = h - 1;
        string m, g, j, n;
        cout << ORANGE "\nNama Mapel         : " RESET; getline(cin, m);
        cout << ORANGE "Guru (Pak Baz)       : " RESET; getline(cin, g);
        cout << ORANGE "Jam (contoh: 1-2)    : " RESET; getline(cin, j);
        cout << ORANGE "Note                 : " RESET; getline(cin, n);

        mapel[i].push_back(m);
        guru[i].push_back(g);
        jam[i].push_back(j);
        note[i].push_back(n);

        cout << HIJAU "Berhasil ditambahkan!\n" RESET;
        garis();

        do {
            cout << KUNING "Apakah anda ingin menambah Mata Pelajaran lain? (y/n): " RESET;
            cin >> lagi;
            cin.ignore();
            if (lowercase(lagi) != "y" && lowercase(lagi) != "n"){
                cout << MERAH "Pilih opsi y atau n!\n" RESET;
            }
        } while (lowercase(lagi) != "y" && lowercase(lagi) != "n");

    } while (lowercase(lagi) == "y");

    int aksi = menuAkhir(true);
    if (aksi == 2) {
        tambahMP(hari, mapel, guru, jam, note);
    } else if (aksi == 3) {
        exit(0);
    }
}

// Hapus Jadwal
void hapusMP(vector<string>& hari, vector<vector<string>>& mapel,
             vector<vector<string>>& guru,  vector<vector<string>>& jam,
             vector<vector<string>>& note) {
    clearScreen();
    int pilih;
    while (true) {
        garis();
        cout << TEBAL CYAN "\t\t\t HAPUS JADWAL\n" RESET;
        garis();
        cout << "1. " UNGU "Home\n" RESET
             << "2. " MERAH "Lanjut\n" RESET;
        cout << ORANGE "Pilih: " RESET;
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MERAH "Input harus angka!\n" RESET;
            continue;
        }
        cin.ignore();
        if (pilih == 1){
            return;
        } else if (pilih == 2){
            break;
        }

        cout << MERAH "Pilihan tidak valid!\n" RESET;
    }

    char lagi;
    do {
        int h;
        while (true) {
            cout << KUNING "Pilih hari:\n" RESET;
            for (int i = 0; i < (int)hari.size(); i++)
                cout << i + 1 << ". " UNGU << hari[i] << RESET "\n";
            cout << ORANGE "Masukkan hari: " RESET;
            cin >> h;
            garis();
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << MERAH "Input harus angka!\n" RESET;
                continue;
            }
            if (h < 1 || h > (int)hari.size()) {
                cout << MERAH "Hari tidak valid!\n" RESET;
                continue;
            }
            cin.ignore();
            break;
        }

        int i = h - 1;
        string nama;
        cout << ORANGE "Masukkan nama mapel yang ingin dihapus: " RESET;
        getline(cin, nama);

        if (mapel[i].empty()) {
            cout << MERAH "Tidak ada mata pelajaran di hari ini!\n" RESET;
        } else {
            string cari = lowercase(nama);
            bool ketemu = false;

            for (int j = 0; j < (int)mapel[i].size(); j++) {
                if (lowercase(mapel[i][j]) == cari) {
                    char konfirmasi;
                    cout << KUNING "Yakin ingin menghapus \"" << mapel[i][j] << "\"? (y/n): " RESET;
                    cin >> konfirmasi;
                    cin.ignore();

                    if (tolower(konfirmasi) == 'y') {
                        mapel[i].erase(mapel[i].begin() + j);
                        guru[i].erase(guru[i].begin() + j);
                        jam[i].erase(jam[i].begin() + j);
                        note[i].erase(note[i].begin() + j);
                        cout << HIJAU "Berhasil dihapus!\n" RESET;
                    } else {
                        cout << KUNING "Penghapusan dibatalkan.\n" RESET;
                    }
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu)
                cout << MERAH "Mapel tidak ditemukan!\n" RESET;
        }

        garis();
        do {
            cout << KUNING "Apakah ingin menghapus lagi? (y/n): " RESET;
            cin >> lagi;
            cin.ignore();
            garis();
            if (tolower(lagi) != 'y' && tolower(lagi) != 'n')
                cout << MERAH "Input tidak valid, pilih y/n!\n" RESET;
        } while (tolower(lagi) != 'y' && tolower(lagi) != 'n');

    } while (tolower(lagi) == 'y');

    int aksi = menuAkhir(true);
    if (aksi == 2){
        hapusMP(hari, mapel, guru, jam, note);
    } else if (aksi == 3) {
        exit(0);
    }
}

// Show Jadwal
void showjadwal(vector<string>& hari, vector<vector<string>>& mapel,
                vector<vector<string>>& guru,  vector<vector<string>>& jam,
                vector<vector<string>>& note) {
    clearScreen();
    garis();
    cout << TEBAL PUTIH "\t\t\tJADWAL MINGGU INI\n" RESET;
    garis();

    for (int i = 0; i < (int)hari.size(); i++) {
        cout << "\n" << TEBAL KUNING << hari[i] << RESET "\n";
        garis_tabel();
        cout << CYAN "| " RESET << left
             << BIRU << setw(12) << "MP"
             << CYAN "| " RESET << BIRU << setw(20) << "GURU"
             << CYAN "| " RESET << BIRU << setw(10) << "JAM"
             << CYAN "| " RESET << BIRU << setw(20) << "NOTE"
             << RESET << CYAN "|\n" RESET;
        garis_tabel();

        if (mapel[i].empty()) {
            cout << CYAN "| " RESET
                 << setw(12) << "" << CYAN "| " RESET
                 << setw(20) << "" << CYAN "| " RESET
                 << setw(10) << "" << CYAN "| " RESET
                 << KUNING << setw(20) << "Belum ada jadwal" << RESET << CYAN "|\n" RESET;
            garis_tabel();
        } else {
            for (int j = 0; j < (int)mapel[i].size(); j++) {
                if (j == 2) {
                    cout << CYAN "| " RESET
                         << setw(12) << "--" << CYAN "| " RESET
                         << setw(20) << "--" << CYAN "| " RESET
                         << setw(10) << "--" << CYAN "| " RESET
                         << ORANGE << setw(20) << "istirahat" << RESET << CYAN "|\n" RESET;
                    garis_tabel();
                }
                cout << CYAN "| " RESET
                     << PUTIH  << setw(12) << mapel[i][j] << RESET << CYAN "| " RESET
                     << HIJAU  << setw(20) << guru[i][j]  << RESET << CYAN "| " RESET
                     << UNGU   << setw(10) << jam[i][j]   << RESET << CYAN "| " RESET
                     << KUNING << setw(20) << note[i][j]  << RESET << CYAN "|\n" RESET;
                garis_tabel();
            }
        }
    }

    int aksi = menuAkhir(false);
    if (aksi == 2) {
        exit(0);
    }
}

// Main
int main() {
    vector<string> hari = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"};
    vector<vector<string>> mapel(hari.size()), guru(hari.size()),
                           jam(hari.size()), note(hari.size());

    int choice;
    bool loggedIn = false;

    do {
        clearScreen();
        cout << "\n";
        garis();
        cout << PUTIH TEBAL "\t\t  SMK TI BALI GLOBAL JAYA SAMPURNA\n" RESET;
        garis();
        cout << "Selamat datang! Pilih opsi:\n"
             << "1. " UNGU "Login\n" RESET
             << "2. " HIJAU "Sign Up\n" RESET
             << "3. " MERAH "Exit\n" RESET;
        garis();
        cout <<  "Pilih menu : ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MERAH "Input harus berupa angka!\n" RESET;
            continue;
        }
        cin.ignore();

        switch (choice) {
        case 1:
            if (login()) loggedIn = true;
            break;
        case 2:
            signup();
            break;
        case 3:
            cout << KUNING "\nTerima kasih telah menggunakan program.\n" RESET;
            break;
        default:
            cout << MERAH "\n!X! Pilihan tidak valid!\n" RESET;
        }
    } while (choice != 3 && !loggedIn);

    // MENU HOME
    while (loggedIn) {
        clearScreen();
        garis();
        cout << TEBAL "\t\t\t   MENU HOME\n" RESET;
        garis();

        cout << "Selamat datang, " << currentUser << "\n";
        cout << "1. " BIRU  "Cari Jadwal\n" RESET
             << "2. " HIJAU "Tambah Jadwal\n" RESET
             << "3. " MERAH "Hapus Jadwal\n" RESET
             << "4. " UNGU  "Show Jadwal\n" RESET
             << "5. " MERAH "Exit\n" RESET;
        cout << "Masukkan pilihan anda : ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MERAH "Input harus berupa angka!\n" RESET;
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1:
                searchMP(hari, mapel, guru, jam, note);
                break;
            case 2:
                tambahMP(hari, mapel, guru, jam, note);
                break;
            case 3:
                hapusMP(hari, mapel, guru, jam, note);
                break;
            case 4:
                showjadwal(hari, mapel, guru, jam, note);
                break;
            case 5:
                cout << KUNING "Terimakasih Telah Menggunakan Program Kami!\n" RESET;
                loggedIn = false;
                break;
            default:
                cout << MERAH "Pilihan tidak valid!\n" RESET;
        }
    }
    return 0;
}
