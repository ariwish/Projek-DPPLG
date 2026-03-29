#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

string username, password, usernameIn, passwordIn;

void garis() {
  cout << "===================================================================="
          "===\n";
}

void garis_tabel() {
  cout << "+-------------+---------------------+-----------+-------------------"
          "--+\n";
}

string lowercase(string str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

// khusus loop untuk bagian akhir (DIUBAH)
int menuAkhir0(bool adaUlang) {
  int pilih;
  while (true) {
    garis();
    cout << "Program selesai, apa anda ingin mencoba program lain? jika iya, input 1.\n";
    if(adaUlang) {
    cout << "1. Home\n"
         << "2. Ulang\n"
         << "3. Exit\n";
    }else {
      cout << "1. Home\n";
      cout << "2. Exit\n";
    }
    garis();

    cout << "Pilih input dengan benar! : ";
    cin >> pilih;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Input haruslah berupa angka...\n";
      continue;
    }

    cin.ignore();

    if (adaUlang && (pilih >= 1 && pilih <= 3))
      return pilih;

    if (!adaUlang && (pilih == 1 || pilih == 2))
      return pilih;

    cout << "Pilihan tidak valid!\n";
  }
}


bool login(string usernameIn, string passwordIn) {
  int attempt = 0;
  while (attempt < 3) {
    cout << endl;
    garis();
    cout << "           LOGIN\n";
    garis();

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buat usrname ama pass ga numpuk

    cout << "Username : ";
    getline(cin,username);
    cout << "Password : ";
    getline(cin,password);

    if (username.empty() || password.empty()) {
      cout << "\n!X! Username atau Password tidak boleh kosong!\n";
      continue;
    }

    if ((username == "Pakdipta" && password == "admin123") ||
        (username == usernameIn && password == passwordIn)) {
      cout << "\n!V! Login berhasil! Selamat datang.\n";
      return true;
    }
    attempt++;
    cout << "\n!X! Login gagal! Percobaan ke-" << attempt << endl;
    if (attempt < 3)
      cout << "Silakan coba lagi.\n";
  }

  cout << "\n!X! Anda sudah mencoba 3 kali.\nLogin diblokir sementara.\n";
  return false;
}

void signup(string &usernameIn, string &passwordIn) {
  cout << endl;
  garis();
  cout << "           SIGN UP\n";
  garis();

cin.ignore(numeric_limits<streamsize>::max(), '\n'); // buat usrname ama pass ga numpuk

  cout << "Buat Username : ";
  getline(cin,usernameIn);
  cout << "\nBuat Password : ";
  getline(cin,passwordIn);

  if (usernameIn.empty() || passwordIn.empty()) {
  cout << "\n!X! Tidak boleh kosong! Ulangi.\n\n";}

  cout << "\n!V! Akun berhasil dibuat!\nSilakan login menggunakan akun Anda.\n";
}

// =================Search MP=======================
void searchMP(vector<string> hari,
              vector<vector<string>> mapel,
              vector<vector<string>> guru,
              vector<vector<string>> jam,
              vector<vector<string>> note) {
  string input = "";
  string lagi;

  do {
    cout << "\nMata Pelajaran apa yang ingin kamu cari? ";
    //getline(cin, input); ini masalahnya
    cin >> input;
    string cariMp = lowercase(input);
    bool ketemu = false;

    for (int i = 0; i < mapel.size(); i++) {
      for (int j = 0; j < mapel[i].size(); j++) {
        string currentMapel = lowercase(mapel[i][j]);

        if (currentMapel == cariMp ||
            currentMapel.find(cariMp) != string::npos) {
          cout << "\n[Ditemukan pada hari " << hari[i] << "]" << endl;
          cout << "Mata Pelajaran : " << mapel[i][j] << endl;
          cout << "Guru           : " << (j < guru[i].size() ? guru[i][j] : "-")
               << endl;
          cout << "Jam            : " << (j < jam[i].size() ? jam[i][j] : "-")
               << endl;
          cout << "Catatan        : " << (j < note[i].size() ? note[i][j] : "-")
               << endl;
          ketemu = true;
        }
      }
    }

    if (!ketemu) {
      cout << "Mata pelajaran tidak ditemukan.\n";}
    do {
      cout << "Apakah anda ingin mencari Mata pelajran lain? (y/n): ";
      cin >> lagi;
      cin.ignore();
      if(lowercase(lagi) != "y" && lowercase(lagi) != "n"){
              cout << "Pilih opsi y atau n!\n";}
    }while (lowercase(lagi) != "y" && lowercase(lagi) != "n");
  } while (lowercase(lagi) == "y");
//(DIUBAH)
    int aksi = menuAkhir0(true);
  if (aksi == 1)
    return;
  else if(aksi ==2)
    searchMP(hari, mapel, guru, jam, note);
  else if(aksi == 3)
    exit(0);
  else
    cout << "Pilihan tidak Valid!\n";
}

//================== Tambah Jadwal =============================
void tambahMP(vector<string> &hari,
              vector<vector<string>> &mapel,
              vector<vector<string>> &guru,
              vector<vector<string>> &jam,
              vector<vector<string>> &note) {

  int h;
  string lagi;

  do{
    while (true) {
    cout << "\n=== TAMBAH JADWAL ===\n";
    for (int i = 0; i < hari.size(); i++) {
      cout << i + 1 << ". " << hari[i] << endl;
    }

    cout << "Pilih hari: ";
    cin >> h;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Input harus angka!\n";
      continue;
    }

    if (h < 1 || h > hari.size()) {
      cout << "Tidak valid!\n";
      continue;
    }

    cin.ignore();
    break;
  }

  int i = h - 1;

  string m, g, j, n;

  cout << "Nama Mapel: ";
  getline(cin, m);
  cout << "Guru: ";
  getline(cin, g);
  cout << "Jam: ";
  getline(cin, j);
  cout << "Note: ";
  getline(cin, n);

  mapel[i].push_back(m);
  guru[i].push_back(g);
  jam[i].push_back(j);
  note[i].push_back(n);

  cout << "Berhasil ditambahkan!\n";
  cin.ignore();
  do {
    cout << "Apakah anda ingin mencari Mata pelajran lain? (y/n): ";
    cin >> lagi;
    cin.ignore();
    if(lowercase(lagi) != "y" && lowercase(lagi) != "n"){
            cout << "Pilih opsi y atau n!\n";}
  }while (lowercase(lagi) != "y" && lowercase(lagi) != "n");
}while(lowercase(lagi) == "y");

  int aksi = menuAkhir0(true);
  if (aksi == 1)
    return;
  else if(aksi ==2)
    tambahMP(hari, mapel, guru, jam, note);
  else if (aksi == 3)
    exit(0);
}
//=================== Show Jadwal ==============================
void showjadwal(vector<string> hari,
                vector<vector<string>> mapel,
                vector<vector<string>> guru,
                vector<vector<string>> jam,
                vector<vector<string>> note) {

  garis();
  cout << "\t\t\tJADWAL MINGGU INI\n";
  garis();

  for (int i = 0; i < hari.size(); i++) {
    cout << "\n" << hari[i] << endl;

    garis_tabel();

    // HEADER tabel
    cout << "| " << left << setw(12) << "MP"
         << "| " << setw(20) << "GURU"
         << "| " << setw(10) << "JAM"
         << "| " << setw(20) << "NOTE" << "|\n";

    garis_tabel();

    if (mapel[i].empty()) {
      cout << "| " << setw(49) << "\t\t\t  Belum ada jadwal"
           << "|\n";
      garis_tabel();
    } else {
      for (int j = 0; j < mapel[i].size(); j++) {

        if (j == 2) {
          cout << "| " << setw(10) << "--"
               << "| " << setw(20) << "--"
               << "| " << setw(8) << "--"
               << "| " << setw(20) << "istirahat" << "|\n";
          garis_tabel();
        }

        cout << "| " << setw(10) << mapel[i][j] << "| " << setw(20)
             << guru[i][j] << "| " << setw(8) << jam[i][j] << "| " << setw(20)
             << note[i][j] << "|\n";

        garis_tabel();
      }
    }
  }

  int aksi = menuAkhir0(false);
//(Diubah)
  if (aksi == 1)
    return;
  else if (aksi == 2)
    exit(0);
  else
    cout << "Pilihan tidak Valid!\n";
}

//=============MAIN========================
int main() {
  vector<string> hari = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"};

  vector<vector<string>> mapel(hari.size()); // finlly get it.. lama kali
  vector<vector<string>> guru(hari.size());
  vector<vector<string>> jam(hari.size());
  vector<vector<string>> note(hari.size());


  int choice;
  bool loggedIn = false;
  do {
    cout << endl;
    garis();
    cout << "\t\t  SMK TI BALI GLOBAL JAYA SAMPURNA\n";
    garis();
    cout << "1. Login\n2. Sign Up\n3. Exit\n";
    garis();
    cout << "Pilih menu : ";
    cin >> choice;

    // Validasi input
    if (cin.fail()) {
      cin.clear();            // reset error
      cin.ignore(1000, '\n'); // buang input salah
      cout << "Input harus berupa angka!" << endl;
      continue; // ulangi loop
    }

    switch (choice) {
    case 1:
      if (login(usernameIn, passwordIn))
        loggedIn = true;
      break;
    case 2:
      signup(usernameIn, passwordIn);
      break;
    case 3:
      cout << "\nTerima kasih telah menggunakan program.\n";
      break;
    default:
      cout << "\n!X! Pilihan tidak valid!\n";
    }

  } while (choice != 3 && !loggedIn);

  bool ulang = true;

  while (loggedIn) {
    garis();
    cout << "MENU HOME" << endl;
    garis();
    cout << "1. Cari Mata Pelajaran " << endl;
    cout << "2. Tambah Mata pelajaran " << endl;
    cout << "3. Show Jadwal" << endl;
    cout << "4. Exit" << endl;
    cout << "Masukkan pilihan anda : ";
    cin >> choice;

    // Validasi input
    if (cin.fail()) {
      cin.clear();            // reset error
      cin.ignore(1000, '\n'); // buang input salah
      cout << "Input harus berupa angka!" << endl;
      continue; // ulangi loop
    }

    switch (choice) {
    case 1:
      searchMP(hari, mapel, guru, jam, note);
      break;
    case 2:
      tambahMP(hari, mapel, guru, jam, note);
      break;
    case 3:
      showjadwal(hari, mapel, guru, jam, note);
      break;
    case 4:
      cout << "Program berakhir" << endl;
      loggedIn = false;
      break;
    default:
      cout << "Pilihan tidak valid" << endl;
    }
  }

  return 0;
}
