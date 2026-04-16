#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <chrono>

using namespace std;

// WARNA
#define RESET   "\033[0m"
#define TEBAL   "\033[1m"
#define MERAH   "\033[91m"
#define HIJAU   "\033[92m"
#define KUNING  "\033[93m"
#define CYAN    "\033[96m"
#define PUTIH   "\033[97m"
#define UNGU    "\033[95m"
#define PINK    "\033[38;5;206m"
#define ORANGE  "\033[38;5;214m"
#define BIRU    "\033[94m"
#define CLEAR   "\033[2J\033[3J\033[H"

string currentUser;

map<string, string> akun = {
    {"Pak Dipta",   "admin123"},
    {"Pak Ngurah",  "WEBSITEILOVEPDF"},
    {"Pak Dhanan",  "npminstallhell"},
    {"Pak Mahesa",  "KinkMadrid"},
    {"Pak Arga",    "#RRQBUTUHSKYLAR"},
    {"Pak Okan",    "akunKeduaAyanokoji"}
};

bool tidakValid(string text) {

    if (text.length() < 3 || text.length() > 15) {
        return true;
    }

    bool spasi = true;
    for (char c : text) {
        if (c != ' ') {
            spasi = false;
            break;
        }
    }

    if (spasi) {
        return true;
    }

    return false;
}

void garis()       { cout << CYAN "=======================================================================" RESET "\n"; }
void garis_tabel() { cout << CYAN "+-------------+---------------------+-----------+--------------------+" RESET "\n"; }

void clearScreen() {
    cout << CLEAR;
    cout.flush();
}

string asteriskPass() {
    string password;
    char ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch == 127 || ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b" << flush;
            }
        } else {
            password += ch;
            cout << '*' << flush;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << endl;
    return password;
}

void write(string text, int delay = 50) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    this_thread::sleep_for(chrono::milliseconds(600)); // kasi waktu buat baca pesan error
}

bool inputFail() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        write(MERAH "Input harus berupa angka!\n" RESET);
        return true;
    }
    cin.ignore(1000, '\n');
    return false;
}

string lowercase(string str) { // lebih gampang + no liblary tambahan
    for (int i = 0; i < str.length(); i++) {
        str[i] = towlower(str[i]);
    }
    return str;
}

int menuAkhir(bool adaUlang) {
    int pilih;
    while (true) {
        garis();
        cout << KUNING "Program selesai. Pilih aksi berikutnya:\n" RESET;
        if (adaUlang) {
            cout << "1. " UNGU  "Home\n"  RESET
                 << "2. " PINK  "Ulang\n" RESET
                 << "3. " MERAH "Exit\n"  RESET;
        } else {
            cout << "1. " UNGU  "Home\n"  RESET
                 << "2. " MERAH "Exit\n"  RESET;
        }
        cout << ORANGE "Pilih: " RESET;
        cin >> pilih;

        if (inputFail()) continue;

        if (adaUlang && pilih >= 1 && pilih <= 3) return pilih;
        if (!adaUlang && (pilih == 1 || pilih == 2))  return pilih;
        cout << MERAH "Pilihan tidak valid!\n" RESET;
    }
}

// Login
bool login() {
    int attempt = 0;
    while (attempt < 3) {
        cout << "\n";
        garis();
        cout << PUTIH TEBAL "\t\t\t       LOGIN\n" RESET;
        garis();

        string username, password;

        cout << "Username : ";
        getline(cin, username);
        cout << "Password : ";
        password = asteriskPass();

        if (tidakValid(username) || tidakValid(password)) {
            cout << MERAH "Input terlalu singkat! Minimal 3 karakter, Maximal 15 karakter!\n" RESET;
            attempt++;
            write(MERAH "\n!X! Login gagal! Percobaan ke-" + to_string(attempt) + "\n" RESET);
            clearScreen();
            continue;
        }

        if (akun.count(username) && akun[username] == password) {
            currentUser = username;
            write(HIJAU "\n!V! Login berhasil! Selamat datang, " + currentUser + "\n" RESET);
            return true;
        }

        attempt++;
        write(MERAH "\n!X! Login gagal! Percobaan ke-" + to_string(attempt) + "\n" RESET);
    }
    write(MERAH "\n!X! Anda sudah mencoba 3 kali.\n" RESET);
    return false;
}

// Sign Up
void signup() {
    cout << endl;
    garis();
    cout << PUTIH TEBAL "\t\t\t       SIGN UP\n" RESET;
    garis();

    string usernameIn, passwordIn;

    cout << "Buat Username : ";
    getline(cin, usernameIn);
    cout << "Buat Password : ";
    passwordIn = asteriskPass();

    if (tidakValid(usernameIn) || tidakValid(passwordIn)) {
        write(MERAH "\n!X! Input Min 3 char, Max 15 char!\n" RESET);
        return;
    }
    if (akun.count(usernameIn)) {
        write(MERAH "\n!X! Username sudah digunakan!\n" RESET);
        return;
    }
    akun[usernameIn] = passwordIn;
    write(HIJAU "\n!V! Akun berhasil dibuat!\n" RESET);
}
 
// Search Jadwal
void searchMP(vector<string> &hari, vector<vector<string>> &mapel,
              vector<vector<string>> &guru, vector<vector<string>> &jam,
              vector<vector<string>> &note) {
    int pilih;
    while (true) {
        garis();
        cout << TEBAL CYAN "\t\t\t SEARCH JADWAL\n" RESET;
        garis();
        cout << "1. " UNGU  "Home\n"  RESET
             << "2. " HIJAU "Lanjut\n" RESET;
        cout << "Pilih: ";
        cin >> pilih;
        if (inputFail()) continue;
        garis();
        if (pilih == 1) return;
        if (pilih == 2) break;
        write(MERAH "Pilihan tidak valid!\n" RESET);
    }

    string lagi;
    do {
        string input;
        cout << ORANGE "\nMata Pelajaran apa yang ingin kamu cari? " RESET;
        getline(cin, input);
        string cariMp = lowercase(input);
        garis();
        bool ketemu = false;

        for (int i = 0; i < (int)mapel.size(); i++) {
            for (int j = 0; j < (int)mapel[i].size(); j++) {
                string mp_sekarang = lowercase(mapel[i][j]);
                if (mp_sekarang.find(cariMp) != string::npos) {
                    cout << HIJAU << "\n[Ditemukan pada hari " << KUNING << hari[i] << HIJAU "]\n" << RESET;
                    cout << BIRU << "Mata Pelajaran : " << RESET << KUNING << mapel[i][j] << RESET << "\n";
                    cout << BIRU << "Guru           : " << RESET << guru[i][j] << "\n";
                    cout << BIRU << "Jam            : " << RESET << jam[i][j] << "\n";
                    cout << BIRU << "Catatan        : " << RESET << note[i][j] << "\n";
                    ketemu = true;
                }
            }
        }

        if (!ketemu)
            cout << MERAH "Mata pelajaran tidak ditemukan.\n" RESET;
        garis();

        do {
            cout << KUNING "Apakah anda ingin mencari Mata Pelajaran lain? (y/n): " RESET;
            cin >> lagi;
            cin.ignore(1000, '\n');
            if (lowercase(lagi) != "y" && lowercase(lagi) != "n")
                cout << MERAH "Pilih opsi y atau n!\n" RESET;
        } while (lowercase(lagi) != "y" && lowercase(lagi) != "n");
    } while (lowercase(lagi) == "y");

    int aksi = menuAkhir(true);
    if (aksi == 2) searchMP(hari, mapel, guru, jam, note);
    else if (aksi == 3) exit(0);
}

// Tambah Jadwal
void tambahMP(vector<string> &hari, vector<vector<string>> &mapel,
              vector<vector<string>> &guru, vector<vector<string>> &jam,
              vector<vector<string>> &note) {
    int pilih;
    while (true) {
        garis();
        cout << TEBAL CYAN "\t\t\t TAMBAH JADWAL\n" RESET;
        garis();
        cout << "1. " UNGU  "Home\n"   RESET
             << "2. " HIJAU "Lanjut\n" RESET;
        cout << ORANGE "Pilih: " RESET;
        cin >> pilih;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << MERAH "Input harus berupa angka!\n" RESET;
            continue;
        }
        cin.ignore(1000, '\n');
        if (pilih == 1) return;
        if (pilih == 2) break;
        write(MERAH "Pilihan tidak valid!\n" RESET);
    }

    string lagi;
    do {
        int h;
        while (true) {
            garis();
            for (int i = 0; i < (int)hari.size(); i++)
                cout << i + 1 << ". " UNGU << hari[i] << RESET "\n";

            cout << ORANGE "Pilih hari: " RESET;
            cin >> h;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                write(MERAH "Input harus berupa angka!\n" RESET);
                continue;
            }
            cin.ignore(1000, '\n');
            if (h < 1 || h > 5) {
                write(MERAH "Tidak valid!\n" RESET);
                continue;
            }
            break;
        }

        int i = h - 1;
        string m, g, j, n;
        while (true) {
            cout << ORANGE "\nNama Mapel            : " RESET; getline(cin, m);
            cout << ORANGE "Guru (cth: Pak Baz)   : " RESET; getline(cin, g);
            cout << ORANGE "Jam (cth: 1-2)        : " RESET; getline(cin, j);
            cout << ORANGE "Note                  : " RESET; getline(cin, n);

            if (tidakValid(m) || tidakValid(g) || tidakValid(j)) {
                cout << MERAH "Input tidak valid! MAX char 15, MIN char 3!\n" RESET;
                cout << KUNING "Silakan ulangi semua input!\n" RESET;
                continue;
            }
            break;
        }

        mapel[i].push_back(m);
        guru[i].push_back(g);
        jam[i].push_back(j);
        note[i].push_back(n);

        write(HIJAU "Berhasil ditambahkan!\n" RESET);
        garis();

        do {
            cout << KUNING "Apakah anda ingin menambah Mata Pelajaran lain? (y/n): " RESET;
            cin >> lagi;
            cin.ignore(1000, '\n');
            if (lowercase(lagi) != "y" && lowercase(lagi) != "n")
                cout << MERAH "Pilih opsi y atau n!\n" RESET;
        } while (lowercase(lagi) != "y" && lowercase(lagi) != "n");

    } while (lowercase(lagi) == "y");

    int aksi = menuAkhir(true);
    if (aksi == 2) tambahMP(hari, mapel, guru, jam, note);
    else if (aksi == 3) exit(0);
}

// Hapus Jadwal
void hapusMP(vector<string> &hari, vector<vector<string>> &mapel,
             vector<vector<string>> &guru, vector<vector<string>> &jam,
             vector<vector<string>> &note) {
    int pilih;
    while (true) {
        garis();
        cout << TEBAL CYAN "\t\t\t HAPUS JADWAL\n" RESET;
        garis();
        cout << "1. " UNGU  "Home\n"   RESET
             << "2. " MERAH "Lanjut\n" RESET;
        cout << ORANGE "Pilih: " RESET;
        cin >> pilih;
        if (inputFail()) continue;
        if (pilih == 1) return;
        if (pilih == 2) break;
        garis();
        write(MERAH "Pilihan tidak valid!\n" RESET);
    }

    string lagi;
    do {
        int h;
        while (true) {
            garis();
            cout << KUNING "Pilih hari:\n" RESET;
            for (int i = 0; i < (int)hari.size(); i++)
                cout << i + 1 << ". " UNGU << hari[i] << RESET "\n";
            cout << ORANGE "Masukkan hari: " RESET;
            cin >> h;
            garis();
            if (inputFail()) continue;
            if (h < 1 || h > 5) {
                write(MERAH "Hari tidak valid!\n" RESET);
                continue;
            }
            break;
        }

        int i = h - 1;
        string nama;
        cout << ORANGE "Masukkan nama mapel yang ingin dihapus: " RESET;
        getline(cin, nama);

        if (mapel[i].empty()) {
            write(MERAH "Tidak ada mata pelajaran di hari ini!\n" RESET);
        } else {
            string cari = lowercase(nama);
            bool ketemu = false;

            for (int j = 0; j < (int)mapel[i].size(); j++) {
                if (lowercase(mapel[i][j]) == cari) {
                    char konfirmasi;
                    cout << KUNING "Yakin ingin menghapus \"" << mapel[i][j] << "\"? (y/n): " RESET;
                    cin >> konfirmasi;
                    // FIX 3: consume newline after reading single char
                    cin.ignore(1000, '\n');

                    if (tolower(konfirmasi) == 'y') {
                        mapel[i].erase(mapel[i].begin() + j);
                        guru[i].erase(guru[i].begin()  + j);
                        jam[i].erase(jam[i].begin()    + j);
                        note[i].erase(note[i].begin()  + j);
                        write(HIJAU "Berhasil dihapus!\n" RESET);
                    } else {
                        write(KUNING "Penghapusan dibatalkan.\n" RESET);
                    }
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu)
                write(MERAH "Mapel tidak ditemukan!\n" RESET);
        }
        garis();

        do {
            cout << KUNING "Apakah ingin menghapus Mata pelajaran lain? (y/n): " RESET;
            cin >> lagi;
            cin.ignore(1000, '\n');
            if (lowercase(lagi) != "y" && lowercase(lagi) != "n")
                write(MERAH "Pilih opsi y atau n!\n" RESET);
        } while (lowercase(lagi) != "y" && lowercase(lagi) != "n");

    } while (lowercase(lagi) == "y");

    int aksi = menuAkhir(true);
    if (aksi == 2) hapusMP(hari, mapel, guru, jam, note);
    else if (aksi == 3) exit(0);
}

// Show Jadwal
void showjadwal(vector<string> &hari, vector<vector<string>> &mapel,
                vector<vector<string>> &guru, vector<vector<string>> &jam,
                vector<vector<string>> &note) {
    garis();
    cout << TEBAL PUTIH "\t\t\tJADWAL MINGGU INI\n" RESET;
    garis();

    for (int i = 0; i < (int)hari.size(); i++) {
        cout << "\n" << TEBAL KUNING << hari[i] << RESET "\n";
        garis_tabel();
        cout << CYAN "| " RESET << left
             << BIRU  << setw(12) << "MP"   << CYAN "| " RESET
             << BIRU  << setw(20) << "GURU" << CYAN "| " RESET
             << BIRU  << setw(10) << "JAM"  << CYAN "| " RESET
             << BIRU  << setw(19) << "NOTE" << RESET << CYAN "|\n" RESET;
        garis_tabel();

        if (mapel[i].empty()) {
            cout << CYAN "| " RESET
                 << setw(12) << "" << CYAN "| " RESET
                 << setw(20) << "" << CYAN "| " RESET
                 << setw(10) << "" << CYAN "| " RESET
                 << KUNING << setw(19) << "Belum ada jadwal" << RESET << CYAN "|\n" RESET;
            garis_tabel();
        } else {
            for (int j = 0; j < (int)mapel[i].size(); j++) {
                if (j == 2) {
                    cout << CYAN "| " RESET
                         << setw(12) << "--" << CYAN "| " RESET
                         << setw(20) << "--" << CYAN "| " RESET
                         << setw(10) << "--" << CYAN "| " RESET
                         << ORANGE << setw(19) << "istirahat" << RESET << CYAN "|\n" RESET;
                    garis_tabel();
                }
                cout << CYAN "| " RESET
                     << PUTIH  << setw(12) << mapel[i][j] << RESET << CYAN "| " RESET
                     << HIJAU  << setw(20) << guru[i][j]  << RESET << CYAN "| " RESET
                     << UNGU   << setw(10) << jam[i][j]   << RESET << CYAN "| " RESET
                     << KUNING << setw(19) << note[i][j]  << RESET << CYAN "|\n" RESET;
                garis_tabel();
            }
        }
    }

    int aksi = menuAkhir(false);
    if (aksi == 2) exit(0);
}


int main() {
    vector<string> hari = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"};
    vector<vector<string>> mapel(hari.size()), guru(hari.size()),
                           jam(hari.size()),   note(hari.size());

    int choice;
    bool loggedIn = false;

    do {
        clearScreen();
        cout << "\n";
        garis();
        cout << PUTIH TEBAL "\t\t  SMK TI BALI GLOBAL JAYA SAMPURNA\n" RESET;
        garis();
        cout << "Selamat datang! Pilih opsi:\n"
             << "1. " UNGU  "Login\n"   RESET
             << "2. " HIJAU "Sign Up\n" RESET
             << "3. " MERAH "Exit\n"    RESET;
        garis();
        cout << "Pilih menu : ";
        cin >> choice;

        if (inputFail()) continue;

        switch (choice) {
        case 1:
            clearScreen();
            if (login()) loggedIn = true;
            break;
        case 2:
            clearScreen();
            signup();
            break;
        case 3:
            write(KUNING "\nTerima kasih telah menggunakan program.\n" RESET);
            break;
        default:
            write(MERAH "\n!X! Pilihan tidak valid!\n" RESET);
        }
    } while (choice != 3 && !loggedIn);

    clearScreen();
    while (loggedIn) {
        garis();
        cout << TEBAL "\t\t\t   MENU HOME\n" RESET;
        garis();
        cout << "Selamat datang " << currentUser << ", pilihlah opsi dengan benar!\n";
        cout << "1. " BIRU  "Cari Jadwal\n"   RESET
             << "2. " HIJAU "Tambah Jadwal\n" RESET
             << "3. " MERAH "Hapus Jadwal\n"  RESET
             << "4. " UNGU  "Show Jadwal\n"   RESET
             << "5. " MERAH "Exit\n"           RESET;
        cout << "Masukkan pilihan anda : ";
        cin >> choice;

        // FIX 4: consume newline so inner getline() calls work correctly
        if (inputFail()) continue;

        switch (choice) {
        case 1: clearScreen(); searchMP(hari, mapel, guru, jam, note); break;
        case 2: clearScreen(); tambahMP(hari, mapel, guru, jam, note); break;
        case 3: clearScreen(); hapusMP (hari, mapel, guru, jam, note); break;
        case 4: clearScreen(); showjadwal(hari, mapel, guru, jam, note); break;
        case 5:
            write(KUNING "Terimakasih Telah Menggunakan Program Kami!\n" RESET);
            loggedIn = false;
            break;
        default:
            clearScreen();
            write(MERAH "Pilihan tidak valid!\n" RESET);
        }
    }
    return 0;
}