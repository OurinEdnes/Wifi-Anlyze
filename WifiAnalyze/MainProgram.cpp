#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <direct.h>
#include <string>

using namespace std;
//=================Untuk Mudahin Loop===============
#define fori(a, b) for(int i = (a); i < (b); i++)
#define forj(a, b) for(int j = (a); j < (b); j++)
#define forz(a, b) for(int z = (a); z < (b); z++)

#define forLantai(a, b) for(int i = (a); i < (b); i++)
#define forAP(a, b) for(int j = (a); j < (b); j++)
#define forUserPerAP(a, b) for(int k = (a); k < (b); k++)
#define forUserPerKegiatan(a, b) for(int l = (a); l < (b); l++)


//======Penginnisialisasi Warna MEnggunakan Define Untuk Teks======
#define WARNA_HITAM   0
#define WARNA_BIRU    1
#define WARNA_HIJAU   2
#define WARNA_CYAN    3
#define WARNA_MERAH   4
#define WARNA_UNGU    5
#define WARNA_KUNING  6
#define WARNA_PUTIH   7
#define WARNA_ORANGE   14

#define WARNA_HEADER  WARNA_CYAN
#define WARNA_ERROR   WARNA_MERAH
#define WARNA_INPUT   WARNA_KUNING
#define WARNA_LOADING WARNA_HIJAU
#define WARNA_LABEL   WARNA_UNGU
#define WARNA_NORMAL  WARNA_PUTIH

#define hijau(TEXT) setWarna(2); cout << (TEXT); setWarna(7)

//======UserandPass=====
string UserName;
string Password;
bool Pass = false;

bool Attemp = true;
int maxTry = 4;

string path;
bool PunyaDatabase = true;
//======================
//====Variabel-Global===
    const int MaxUser = 100;
    const int MaxLantai = 15;
    const int MaxAp_Per_lantai = 10;
    int Lantai, APMax = 0;
    string pathFile1User, pathFile2User, pathFile3User;
//=======================

//======Function da prosedur=====
void Navbar();
void InterfaceAwal();
void Login();
void SignUp();
bool LoginProtection();
bool SignProtect();
void DirectP();

void SimpanDataWifiUser();
void SimpanDataKecepatanAP();
void SimpaDataUserPerAP();

void pauseScreen();


int stringToIntManual(const string& s);
double convertToGbpsANDMbps(const string& teks);

///====Untuk Cloning Data Jadi Yang Diotakatik Buat Sort dan Search dari Sini====
void CloningData();

//=======Page========
void PageAwal();
void PageLoading();
void PageUtama();
void NewPenggunna();
void NewInputUnntukPenggunnaBaru();
void cetakKategori();

void cetakKonfigurasWifiUser();
void ManuPagefirst(char &c, char &v);
void CetakKecepatan(const char& type, const char &typeSort); void cetakKatalog();

void TampilkanKecepatanNormal();
void TampilkanKecepatanSortPerAP(const char &c);
void TampilkanKecepatanSortPerLantai(const char &c);

void TampilkanNama(); void tampilNormal(); void TampilUrut(); void UrutSesuaiKatalog(int Katlog[]);

void gantiAtauTambah(); void ChangeConnfigure(); void AddUser(); void RemoveUser(); void RemoveUserperLantai();
void Searching(); void CariNama(); void cariBerdasarkanKegiatan();
//===================

//======Folder-PerUser=====
void dataUser();
void cekbase();
void CekDatabaseUser();
void WifikonfigurasiList();
void KegiatanData();
void CekSSemuaDataUser();


///=====DataBase Ke Array=====
void WifiConnfigureIN();
void PenggunaIN();
void APSpeedIN();
void DataBaseUserIN();
void KegiatanIN();

//====Array-Save-Data-Buat-User====
int DataBaseUser[MaxLantai];
string Pengguna[MaxLantai][MaxAp_Per_lantai][MaxUser][2]; //2 Buat Nama Pengguna dan Kegiatan yang dilakukan
string APSpeed[MaxLantai][MaxAp_Per_lantai][2];
string WifiConnfigur[MaxLantai][5]; //4 buat deklarasi Nama wifi, kecepatann wwifi, sama total penngguna
string Kegiatan[5][2];
string WifiCategoryList[10][5];

// === Clone Arrays ===
string ClonePengguna[MaxLantai][MaxAp_Per_lantai][MaxUser][2];
string CloneAPSpeed[MaxLantai][MaxAp_Per_lantai][2];
string CloneWifiConnfigur[MaxLantai][5];
string CloneKegiatan[5][2];

//=========Array-Searching======
string findAP[MaxLantai][MaxAp_Per_lantai];

///====================================================================================
void WifiConnfigureIN() {
    string pathfile = path + "/WifiConfigure.txt";
    fstream file(pathfile, ios::in);
    string line;

    int indexLantai = 0;
    int currentLantai = 0;
    int jumlahAP = 0;
    while (getline(file, line)) {
        //=== PARSING JUMLAH LANTAI ===
        if (line.find("Jumlah Lantai =") != string::npos) {
            int result = 0;
            bool out = true;
            string s = line.substr(line.find('=') + 2);

            fori(0, s.length()) {
                switch (s[i]) {
                    case '0': result = result * 10 + 0; break;
                    case '1': result = result * 10 + 1; break;
                    case '2': result = result * 10 + 2; break;
                    case '3': result = result * 10 + 3; break;
                    case '4': result = result * 10 + 4; break;
                    case '5': result = result * 10 + 5; break;
                    case '6': result = result * 10 + 6; break;
                    case '7': result = result * 10 + 7; break;
                    case '8': result = result * 10 + 8; break;
                    case '9': result = result * 10 + 9; break;
                    default: out = false; break;
                }
                if (!out) break;
            }
            if (out) {
                Lantai = result;
            }
        }

        //=== PARSING JUMLAH AP PER LANTAI ===
        else if (line.find("> Lantai") != string::npos) {
            bool out = true;
            string s = line.substr(line.find('=') + 2);
            jumlahAP = 0;
            fori(0, s.length()) {
                switch (s[i]) {
                    case '0': jumlahAP = jumlahAP * 10 + 0; break;
                    case '1': jumlahAP = jumlahAP * 10 + 1; break;
                    case '2': jumlahAP = jumlahAP * 10 + 2; break;
                    case '3': jumlahAP = jumlahAP * 10 + 3; break;
                    case '4': jumlahAP = jumlahAP * 10 + 4; break;
                    case '5': jumlahAP = jumlahAP * 10 + 5; break;
                    case '6': jumlahAP = jumlahAP * 10 + 6; break;
                    case '7': jumlahAP = jumlahAP * 10 + 7; break;
                    case '8': jumlahAP = jumlahAP * 10 + 8; break;
                    case '9': jumlahAP = jumlahAP * 10 + 9; break;
                    default: out = false; break;
                }
                if (!out) break;
            }
            out = true;
            if (out) {
                DataBaseUser[indexLantai] = jumlahAP;
                if (APMax < jumlahAP) APMax = jumlahAP;
                indexLantai++;
            }
        }

        //=== PARSING ISI WIFI SETIAP LANTAI ===
        else if (line.find("MerekWiFi") != string::npos && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][0] = line.substr(line.find(':') + 2);
        }
        else if (line.find("AccessPoint") != string::npos && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][1] = line.substr(line.find(':') + 2);
        }
        else if (line.find("KecepatanWiFi") != string::npos && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][2] = line.substr(line.find(':') + 2);
        }
        else if (line.find("KecepatanAP") != string::npos && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][3] = line.substr(line.find(':') + 2);
        }
        else if (line.find("MaxUser      :") != string::npos && currentLantai < MaxLantai) {
            WifiConnfigur[currentLantai][4] = line.substr(line.find(':') + 2);
            currentLantai++;
        }

        if (currentLantai >= MaxLantai) break;
    }
    file.close();
}

void APSpeedIN() {
    fstream file(pathFile3User, ios::in);
    string line;

    int indexLantai = -1, indexAP = 0;
    while (getline(file, line)) {
        if (line.find(">> Lantai") != string::npos) {
            indexLantai++;
            indexAP = 0;
        }
        else if (line.find("AccessPoint") != string::npos && line.find("=") != string::npos) {
            size_t eqPos = line.find('=');
            size_t delimiterPos = line.find("||");

            string apSpeed = line.substr(eqPos + 2, delimiterPos - (eqPos + 2));
            APSpeed[indexLantai][indexAP][0] = apSpeed;

            size_t userSpeedPos = line.find("Kecepatan User =");
            if (userSpeedPos != string::npos) {
                string userSpeed = line.substr(userSpeedPos + 17);
                APSpeed[indexLantai][indexAP][1] = userSpeed;
            }

            indexAP++;
        }
    }
    file.close();
}

void PenggunaIN() {
    fstream file(pathFile2User, ios::in);
    string line;

    int indexLantai = -1;
    int indexAP = 0;
    int indexUser = 0;

    while (getline(file, line)) {
        // Cek Lantai
        if (line.find(">> Lantai") != string::npos) {
            indexLantai++;
            indexAP = 0;
            continue;
        }

        // Cek Access Point
        else if (line.find("AccessPoint") != string::npos) {
            indexUser = 0;
            indexAP++; // <-- Ini cukup di sini aja
            continue;
        }

        // Cek jika baris ada Nama dan Kegiatan
        else if (line.find("Nama =") != string::npos && line.find("Kegiatan =") != string::npos) {
            size_t namaPos = line.find("Nama =") + 7;
            size_t kegiatanPos = line.find("Kegiatan =");

            string nama = line.substr(namaPos, kegiatanPos - namaPos - 4); // -4 untuk ' || '
            string kegiatan = line.substr(kegiatanPos + 11);

            Pengguna[indexLantai][indexAP - 1][indexUser][0] = nama;
            Pengguna[indexLantai][indexAP - 1][indexUser][1] = kegiatan;

            indexUser++;
        }

        else if (line.find("[None]") != string::npos) {
            Pengguna[indexLantai][indexAP - 1][indexUser][0] = "-";
            Pengguna[indexLantai][indexAP - 1][indexUser][1] = "-";
            indexUser++;
        }
    }

    file.close();
}


void KegiatanIN(){
    fstream file("DaftarKegiatan.txt", ios::in);
    string line;

    int indexX = 0;
    while(getline(file, line)){
        if(line.find("Nama       =") != string::npos){
            Kegiatan[indexX][0] = line.substr(line.find('=') + 2);
            CloneKegiatan[indexX][0] = line.substr(line.find('=') + 2);
        } else if(line.find("Kecepatan  =") != string::npos){
            Kegiatan[indexX][1] = line.substr(line.find('=') + 2);
            CloneKegiatan[indexX][1] = line.substr(line.find('=') + 2);
        } else if(line.find("================================") != string::npos){
            indexX++;
        }
    }
    file.close();
}
///=======================================================================================

//====Set-Warnna====
void setWarna(int kodeWarna) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kodeWarna);
}

void warnaText(const string& text, int i) {
    setWarna(i);
    cout << text;
    setWarna(WARNA_PUTIH);
}

///========Cover dari strig ke int atau double======
double stringToDoubleManual(const string& s) {
    double result = 0.0;
    double desimal = 0.0;
    bool adaTitik = false;
    double pembagiDesimal = 10.0;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            if (!adaTitik) {
                result = result * 10 + (c - '0');
            } else {
                desimal += (c - '0') / pembagiDesimal;
                pembagiDesimal *= 10;
            }
        } else if ((c == '.' || c == ',') && !adaTitik) {
            adaTitik = true;
        }
    }

    return result + desimal;
}

int stringToIntManual(const string& s) {
    int result = 0;
    bool negatif = false;
    int i = 0;

    // Cek tanda negatif di awal
    if (s[0] == '-') {
        negatif = true;
        i = 1; // mulai dari karakter berikutnya
    }

    for (; i < s.length(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        } else {
            break; // hentikan jika ada karakter non-digit
        }
    }

    return negatif ? -result : result;
}


double convertToGbpsANDMbps(const string& teks, char typeConvert) {
    double angka = stringToDoubleManual(teks);

    string satuan = teks;
    transform(satuan.begin(), satuan.end(), satuan.begin(), ::tolower);

    // Normalize typeConvert (misalnya 'm' -> 'M')
    typeConvert = toupper(typeConvert);

    if (typeConvert == 'M') {  // Ke Mbps
        if (satuan.find("gbps") != string::npos) {
            return angka * 1000.0;
        } else if (satuan.find("mbps") != string::npos) {
            return angka;
        } else if (satuan.find("kbps") != string::npos) {
            return angka / 1000.0;
        }
    }
    else if (typeConvert == 'G') {  // Ke Gbps
        if (satuan.find("gbps") != string::npos) {
            return angka;
        } else if (satuan.find("mbps") != string::npos) {
            return angka / 1000.0;
        } else if (satuan.find("kbps") != string::npos) {
            return angka / 1000000.0;
        }
    }

    // Kalau satuan tidak dikenali
    return angka;
}



//====Cek-Database-User====
void reconDatabase(){
    fstream DataBase("User-DataBase.txt", ios::in);
    if(!DataBase){
        ofstream make("User-DataBase.txt");
        make.close();
    }
    DataBase.close();
}
//=========================

void Navbar(){
    system("cls");
    cout << "============================\n";
    cout << "|---"; setWarna(WARNA_HEADER); cout << "Wifi Analyze Company"; setWarna(WARNA_NORMAL); cout<< "---|\n";
    cout << "============================\n\n";
}
///===============================================================================
//====Page Awal====
void PageAwal(){
    system("cls");
    Navbar();
    InterfaceAwal();
}

void InterfaceAwal(){
    cout << "Selamat Datang... \nHarap Masuk terlebih Dahulu!\n\n";
    cout << "Menu Pilihan: \n";
    cout << "1. Login. \n";
    cout << "2. SignUp. \n";
    cout << "Pilih Menu: ";
    int req; cin >> req;

    if (req == 1){
        Login();
    } else if (req == 2){
        SignUp();
    } else {
        setWarna(WARNA_ERROR);
        cout << "Menu Belum Tersedia Harap Pilih Lagi! \n";
        setWarna(WARNA_NORMAL);
        Sleep(1000);
        PageAwal();
    }
}

void Login(){
    do{
    system("cls");
    Navbar();
    cout << "Login-Section\n\n";

    if(!Attemp){
        setWarna(4);
        cout << "Username / Password salah harap ulangi! (" << maxTry <<" Kali percobaan Lagi) \n\n";
        setWarna(7);
    }
    cout << "Username: ";
    setWarna(WARNA_HIJAU);
    cin >> UserName;
    setWarna(WARNA_NORMAL);
    cout << "Password: ";
    setWarna(WARNA_HIJAU);
    cin >> Password;
    setWarna(WARNA_NORMAL);
    if(LoginProtection()){
        CekSSemuaDataUser();
        Attemp = true;
        maxTry = 4;
        PageLoading();
        PageUtama();
    }
    else{maxTry--; Attemp = false;}
    } while(!Attemp && maxTry > 0);

    if(!Attemp){
        Attemp = true; maxTry = 4;
        setWarna(4);
        cout << "Anda Sudah Mencoba lebih dari 3 kali!\n";
        setWarna(7);
        Sleep(1000);
        PageAwal();
    }
}

bool LoginProtection(){
    fstream data("User-DataBase.txt", ios::in);
    string base;

    int sameboth = 0;
    bool same = false;
    while(getline(data, base)){

        if(base.find("username ##") != string::npos){
            string usernameBase = base.substr(base.find("##") + 3);
            if(UserName == usernameBase){
                sameboth++;
            }
        } else if(base.find("password ##") != string::npos){
            string PasswordBase = base.substr(base.find("##") + 3);
            if(PasswordBase == Password){
                sameboth++;
            }
        } else if(base.find("==============") != string::npos){
            sameboth = 0;
        }

        if(sameboth == 2){
            same = true;
            break;
        }
    }
    data.close();

    return (same == false ? false : true);
}

void SignUp(){
    system("cls");
    Navbar();
    cout << "SignUp-Section\n\n";
    cout << "username: ";
    cin >> UserName;
    cout << "Password: ";
    cin >> Password;
    if(SignProtect()){
        setWarna(3);
        cout <<"\nAkun Berhasil Dibuat!\n";
        setWarna(7);
        cout <<"Harap Login Lagi Terlebih Dahulu";
        Sleep(1000);
        Login();
    } else{
        setWarna(4);
        cout << "UserName sudah Terpakai, Harap Buat Ulang!\n";
        setWarna(7);
        Sleep(1000);
        SignUp();
    }
}

bool SignProtect(){
    fstream data("User-DataBase.txt", ios::app|ios::in);
    string base;

    while(getline(data, base)){
        if(base.find("username ##") != string::npos){
            string usernameBase = base.substr(base.find("##") + 3);
            if(UserName == usernameBase){
                return false;
            }
        }
    }

    data.close();

    fstream Input("User-DataBase.txt", ios::app);
    Input << endl << endl;
    Input << "============================" << endl;
    Input << "username ## " << UserName << endl;
    Input << "password ## " << Password << endl;

    Input.close();
    return true;
}

//==========Katagero=========
void cetakKatalog(){
    cout << endl;
    fori(0, 5){
        cout << "Kegiatan " << i+1 << ": " << endl;
        cout << "Jenis: " << setw(10) <<Kegiatan[i][0] << " || Kecepata yang dipakai: " << Kegiatan[i][1] <<endl<< endl;
    }
    cout << endl;
}

//=======Page Loadig=======
void PageLoading() {
    system("cls");
    cout << "\nMemuat sistem WifiAnalyze...\n\n";
    setWarna(WARNA_LOADING);

    string loadingBar = "===================="; // 20 karakter total
    cout << "[                    ]"; // Bar kosong
    cout.flush();

    cout << "\r["; // Balik kursor ke depan
    fori(0, 20) {
        cout << loadingBar[i];
        cout.flush();
        Sleep(200); // Kecepatan pengisian bar
    }

    cout << "] Selesai!\n";
    setWarna(WARNA_NORMAL);
    Sleep(700); // jeda sedikit sebelum lanjut
}

void PageLoading2() {
    system("cls");
    cout << "\nMemuat Data WifiAnalyze...\n\n";
    setWarna(WARNA_LOADING);

    string spinner = "|/-\\";
    for (int i = 0; i < 20; i++) {
        cout << "\rLoading ";
        setWarna(WARNA_BIRU); cout << spinner[i % 4] << " ";
        cout.flush();
        Sleep(150);
    }

    setWarna(WARNA_NORMAL);
    cout << "\nSelesai!\n";
    Sleep(800);
}

//========CekDataUser=========
// => Nama Folder ("UserData(#username)")
void dataUser(){
    path = "UserData("+UserName+")";
    const char * folder = (path).c_str();
    mkdir(folder);
}

//========CekFile===========
void cekbase(){
    fori(0, 3){
        string construct;
        switch(i){
        case 0:
            construct = "/WifiConfigure.txt";
            break;
        case 1:
            construct = "/Wifi-User.txt";
            break;
        case 2:
            construct = "/Wifi-Ap-Speed.txt";
            break;
        default:
            construct = "/Eror.txt";
            break;
        }

        string pathFile = path + construct;
        fstream FileData(pathFile, ios::in);
        if(!FileData){
            ofstream create(pathFile);
            if(i == 0){
                create << "A7K9-X2ZQ";
            }
            create.close();
            }
        FileData.close();
    }
    pathFile1User = path + "/WifiConfigure.txt";
    pathFile2User = path + "/Wifi-User.txt";
    pathFile3User = path + "/Wifi-Ap-Speed.txt";
}

void KegiatanData(){ //-> Ke Array Kategori Kegiatan
    fstream file("DaftarKegiatan.txt", ios::in);
    string base;
    int i = 0;
    while(getline(file, base)){
        if(base.find("Nama       =") != string::npos){
            Kegiatan[i][0] = base.substr(base.find("=") + 2);
        } else if(base.find("Kecepatan  =") != string::npos){
            Kegiatan[i][1] = base.substr(base.find('=') + 2);
        } else if(base.find("================================") != string::npos){
            i++;
        }
    }
}

void WifikonfigurasiList(){ //->Ke Array Kategori Wifi
    fstream file("WifiCategory.txt", ios::in);
    string base;
    int i = 0;
    while(getline(file, base)){
        if(base.find("MerekWiFi    :") != string::npos){
            WifiCategoryList[i][0] = base.substr(base.find(':') + 2);
        } else if(base.find("AccessPoint  :") != string::npos){
            WifiCategoryList[i][1] = base.substr(base.find(':') + 2);
        } else if(base.find("KecepatanWiFi:") != string::npos){
            WifiCategoryList[i][2] = base.substr(base.find(':') + 2);
        } else if(base.find("KecepatanAP  :") != string::npos){
            WifiCategoryList[i][3] = base.substr(base.find(':') + 2);
        } else if(base.find("MaxUser      :") != string::npos){
            WifiCategoryList[i][4] = base.substr(base.find(':') + 2);
        } else if(base.find("===================================") != string::npos){
            i++;
        }
    }
}

void CekDatabaseUser(){
    string connstruct = path + "/WifiConfigure.txt";
    fstream Data(connstruct, ios::in);
    string line;

    while(getline(Data, line)){
        if(line.find("A7K9-X2ZQ") != string::npos){
            PunyaDatabase = false;
            break;
        } else{
            PunyaDatabase = true;
        }
    }

}

///========Page Utama==========
void PageUtama(){
    NewPenggunna();
    CekSSemuaDataUser();
    system("cls");

    Navbar();
    cin.ignore();
    cout << "Pilihan Menu Yang Tersedia: \n";
    cout << "1. Cek Kecepatan Accses Point di setiap Lantai. \n";
    cout << "2. Cek Konfigurasi Wifi Di Setiap lantai. \n";
    cout << "3. Cek Nama Pengguna. \n";
    cout << "4. Tambah Atau Ganti Kondisi (User dan Wifi). \n";
    cout << "5. Search (Cari). \n";
    cout << "6. Logout. \n";
    cout << "Menu yang Dipilih: "; char pilih; cin >> pilih;

    switch(pilih){
    case '1':
        char key, sortType;
        ManuPagefirst(key, sortType);

        break;
    case '2':
        cetakKonfigurasWifiUser();
        break;
    case '3':
        TampilkanNama();
        break;
    case '4':
        gantiAtauTambah();
        break;
    case '5':
        Searching();
        break;
    case '6':
        cout << endl;
        UserName = "";
        Password = "";
        Sleep(800);
        cout << "Anda Telah Logout!";
        Sleep(700);
        PageAwal();
        break;
    default:
        cout << "Menu Belum Tersedia! Harap pilih denngan Benar!\n";
        Sleep(900); PageUtama();
        break;
    }

    PageUtama();
}

//===============Menu 1=================
void ManuPagefirst(char &c, char &v){
    Navbar();
    cin.ignore();
    cout << "Menu Pilihan Tambahan: \n";
    cout << "1. Cek Kecepatan normal. \n";
    cout << "2. Cek Sesuai Urutam kecepatan per-Lantai. \n";
    cout << "3. Cek Sesuai Urutan Kecepatan Per-ruangan. \n";
    cout << "Pilih: "; char pilih; cin >> pilih;
    switch(pilih){
        case '1':
        c = '1';
        CetakKecepatan(c, v);
        break;

        case '2':
        c = '2';
        setWarna(WARNA_CYAN);
        cout << endl;
        cout << "Urutkan Secara Asceding atau Descending (A/D): "; cin >> pilih; v = pilih;
        CetakKecepatan(c, v);
        setWarna(WARNA_NORMAL);
        break;

        case '3':
        c = '3';
        setWarna(WARNA_CYAN);
        cout << endl;
        cout << "Urutkan Secara Asceding atau Descending (A/D): "; cin >> pilih; v = pilih;
        CetakKecepatan(c, v);
        setWarna(WARNA_NORMAL);
        break;

        default:
            cout << "Pilihan Tidak Tersedia harap pilih kembali! \n";
            Sleep(600);
            ManuPagefirst(c, v);
        break;
    }
    return;
}

void CetakKecepatan(const char& type, const char &typeSort){

    if (!PunyaDatabase) {
        setWarna(WARNA_ERROR);
        cout << "Oops! Database belum diatur atau dimuat!\n";
        cout << "Silakan atur konfigurasi awal di menu 'Tambah Kondisi' terlebih dahulu.\n";
        setWarna(WARNA_NORMAL);
        pauseScreen();
        return;
    }

    switch(type){
        case '1':
            TampilkanKecepatanNormal();
            pauseScreen();
            break;
        case '2':
            TampilkanKecepatanSortPerAP(typeSort);
            pauseScreen();
            break;
        case '3':
            TampilkanKecepatanSortPerLantai(typeSort);
            pauseScreen();
            break;
        default:
            pauseScreen();
            break;
        }

}

void TampilkanKecepatanNormal() {
    setWarna(WARNA_HEADER);
    cout << "===== KECEPATAN ACCESS POINT (NORMAL) =====" << endl;
    setWarna(WARNA_NORMAL);
    forLantai(0, Lantai){
        cout << "Lantai " << i+1 << endl;
        forAP(0, DataBaseUser[i]){
            double APS = convertToGbpsANDMbps(APSpeed[i][j][0], 'M'); //Accsees Point Speed
            double SAU = convertToGbpsANDMbps(APSpeed[i][j][1], 'M'); //Speed Akumulasi User

            if(APS - SAU >= 500) setWarna(WARNA_HIJAU);
            if(APS - SAU < 500) setWarna(WARNA_ORANGE);
            if(APS - SAU < 200) setWarna(WARNA_MERAH);
            cout << "Kecepata AP ke-"<< j+1 << ": " << APSpeed[i][j][0] << " || Kecepata Totol User : " << APSpeed[i][j][1] << endl;


            setWarna(WARNA_NORMAL);
        }
        cout << "===========================\n";
    }

    cout << endl;
    cout << "Keteragan Warna: \n";
    cout << "1. Hijau -> Kecepatann AP Bagus! \n";
    cout << "2. Kuning / Orange -> Kecepatan AP Tidak Bagus \n";
    cout << "3. Merah -> Kecepatan AP Buruk (Harap Kurangi Penggunaann) \n";
    cout << endl;

}

void TampilkanKecepatanSortPerAP(const char &c){
    setWarna(WARNA_HEADER);
    cout << "===== KECEPATAN ACCESS POINT (PerAP) =====" << endl;
    setWarna(WARNA_NORMAL);

    forLantai(0, Lantai) {
        forAP(0, DataBaseUser[i]) {
            forz(0, DataBaseUser[i] - j - 1) {
                double APsatu = convertToGbpsANDMbps(CloneAPSpeed[i][z][0], 'M') - convertToGbpsANDMbps(CloneAPSpeed[i][z][1], 'M');
                double APdua  = convertToGbpsANDMbps(CloneAPSpeed[i][z+1][0], 'M') - convertToGbpsANDMbps(CloneAPSpeed[i][z+1][1], 'M');
                if (((APsatu > APdua) && (c == 'D')) || ((APsatu < APdua) && (c == 'A'))) {
                    for (int d = 0; d < 2; d++) {
                        string temp = CloneAPSpeed[i][z][d];
                        CloneAPSpeed[i][z][d] = CloneAPSpeed[i][z+1][d];
                        CloneAPSpeed[i][z+1][d] = temp;
                    }
                }
            }
        }
    }

    Sleep(600);
    forLantai(0, Lantai){
        cout << "Lantai " << i+1 << endl;
        forAP(0, DataBaseUser[i]){
            double APS = convertToGbpsANDMbps(CloneAPSpeed[i][j][0], 'M'); //Accsees Point Speed
            double SAU = convertToGbpsANDMbps(CloneAPSpeed[i][j][1], 'M'); //Speed Akumulasi User

            if(APS - SAU >= 500) setWarna(WARNA_HIJAU);
            if(APS - SAU < 500) setWarna(WARNA_ORANGE);
            if(APS - SAU < 200) setWarna(WARNA_MERAH);
            cout << "Kecepata AP ke-"<< j+1 << ": " << CloneAPSpeed[i][j][0] << " || Kecepata Totol User : " << CloneAPSpeed[i][j][1] << endl;


            setWarna(WARNA_NORMAL);
        }
        cout << "===========================\n";
    }

    cout << endl;
    cout << "Keteragan Warna: \n";
    cout << "1. Hijau -> Kecepatann AP Bagus! \n";
    cout << "2. Kuning / Orange -> Kecepatan AP Tidak Bagus \n";
    cout << "3. Merah -> Kecepatan AP Buruk (Harap Kurangi Penggunaann) \n";
    cout << endl;
}

void TampilkanKecepatanSortPerLantai(const char &c){
    double sisaKecepatan[MaxLantai];
    string CloneLantai[MaxLantai];

    forLantai(0, Lantai){
        double totalAP = 0, totalUser = 0;

        forAP(0, DataBaseUser[i]){
            totalAP += convertToGbpsANDMbps(CloneAPSpeed[i][j][0], 'M');
            totalUser += convertToGbpsANDMbps(CloneAPSpeed[i][j][1], 'M');
        }

        sisaKecepatan[i] = totalAP - totalUser;
        CloneLantai[i] = to_string(i);
    }

    fori(0, Lantai - 1){
        forj(0, Lantai - i - 1){
            bool tukar = false;
            if((c == 'D' && sisaKecepatan[j] > sisaKecepatan[j+1]) ||
               (c == 'A' && sisaKecepatan[j] < sisaKecepatan[j+1])){
                tukar = true;
            }

            if(tukar){
                double tempNilai = sisaKecepatan[j];
                sisaKecepatan[j] = sisaKecepatan[j+1];
                sisaKecepatan[j+1] = tempNilai;

                string tempIndex = CloneLantai[j];
                CloneLantai[j] = CloneLantai[j+1];
                CloneLantai[j+1] = tempIndex;
            }
        }
    }

    // Cetak hasil
    setWarna(WARNA_HEADER);
    cout << "===== KECEPATAN TOTAL PER LANTAI =====" << endl;
    setWarna(WARNA_NORMAL);

    fori(0, Lantai){
        int id = stoi(CloneLantai[i]);
        double totalAP = 0, totalUser = 0;

        forAP(0, DataBaseUser[id]){
            totalAP   += convertToGbpsANDMbps(CloneAPSpeed[id][j][0], 'M');
            totalUser += convertToGbpsANDMbps(CloneAPSpeed[id][j][1], 'M');
        }

        double sisa = totalAP - totalUser;

        if(sisa >= 1000) setWarna(WARNA_HIJAU);
        else if(sisa >= 500) setWarna(WARNA_ORANGE);
        else setWarna(WARNA_MERAH);

        cout << "Lantai " << id+1
             << " || Total Kecepatan AP: " << totalAP
             << " || Total Kecepatan User: " << totalUser
             << " || Sisa: " << sisa << endl;

        setWarna(WARNA_NORMAL);
    }

    cout << endl;
    cout << "Keteragan Warna: \n";
    cout << "1. Hijau -> Kecepatann AP Bagus! \n";
    cout << "2. Kuning / Orange -> Kecepatan AP Tidak Bagus \n";
    cout << "3. Merah -> Kecepatan AP Buruk (Harap Kurangi Penggunaann) \n";
    cout << endl;

}

//===============Mennu 3================
bool Dup(int arr[], int ukuran, int nilai) {
    for (int i = 0; i < ukuran; i++) {
        if (arr[i] == nilai) {
            return true;
        }
    }
    return false;
}

void TampilkanNama(){
    Navbar();
    char pil;
    cout << "Menu Pilihan Tambahan: \n";
    cout << "1. Cek Nama sesuai urutann connect. \n";
    cout << "2. Cek urutan sesuai kegiatan. \n";
    cout << "Pilih: "; char pilih; cin >> pilih;
    switch(pilih){
        case '1':
        tampilNormal();
        break;
        case '2':
        cetakKatalog();
        cout << endl;
        cout << "1. Urut Sesuai Katalog. \n";
        cout << "2. Bikinn Urutan Sendiri. \n";
        cout << "Pilih: "; cin >> pil;
        switch(pil){
        case '1':
            TampilUrut();
            break;
        case '2':{
            int Katlog[5]; int r = sizeof(Katlog) / sizeof(Katlog[0]);
            cout << endl << endl;
            cout << "Masukan Urutan Yang Anda ingin kann (1-5 sesuai Katalog)\n";
            for (int i = 0; i < r; i++) {
                int input;
                    cout << "Masukkan Urutan ke-" << i+1 << ": ";
                    cin >> input;
                    if (input > 5 || input < 1) {
                        cout << "Angka " << input << " tidak valid, masukkan antara 1-5!\n";
                        i--;
                        continue;
                    }

                    if (Dup(Katlog, i, input)) {
                        cout << "Angka " << input << " sudah ada, masukkan yang lain!\n";
                        i--;
                        continue;
                    }

                    Katlog[i] = input;
            }
            UrutSesuaiKatalog(Katlog);
            break;
        }
        default:
            cout << "Pilihan tidak tersedia! \n";
            pauseScreen();
            TampilkanNama();
            break;
        }
        pauseScreen();
        break;

        default:
            cout << "Pilihan Tidak Tersedia harap pilih kembali! \n";
            Sleep(600);
            TampilkanNama();
        break;
    }
    return;
}

void tampilNormal(){
    cout << endl;
    setWarna(WARNA_HEADER);
    cout << "===== Daftar User =====" << endl;
    setWarna(WARNA_NORMAL);

    forLantai(0, Lantai){
        cout << "Lantai ke-" << i+1 << endl;
        forAP(0, DataBaseUser[i]){
            cout << setw(10) << " " <<"AP ke-" << j+1 << endl;
            int range = stringToIntManual(WifiConnfigur[i][4]);
            bool ada = false;
            forUserPerAP(0, range){
                if(Pengguna[i][j][k][0] == "-" ||  Pengguna[i][j][k][0] == "" ||  Pengguna[i][j][k][0] == " "){
                    continue;
                } else{
                cout << setw(15) << " " << "Nama: " << Pengguna[i][j][k][0] << " || " << "Kegiatan : " << Pengguna[i][j][k][1] << endl;
                ada = true;
                }
            }
            if(!ada){
                cout << setw(15) << " " <<"[NONE]\n";
            }
            cout << endl;
        }
        cout << "=====================================\n";
    }

    pauseScreen();
}

void TampilUrut() {
    cout << endl;
    setWarna(WARNA_HEADER);
    cout << "===== Daftar User Berdasarkan Kegiatan =====" << endl;
    setWarna(WARNA_NORMAL);

    forLantai(0, Lantai){
        cout << "Lantai ke-" << i + 1 << endl;
        forAP(0, DataBaseUser[i]){
            cout << setw(10) << " " << "AP ke-" << j + 1 << endl;
            int range = stringToIntManual(WifiConnfigur[i][4]);
            bool ada = false;

            for (int katalog = 0; katalog < 5; katalog++) {
                forUserPerAP(0, range) {
                if(Pengguna[i][j][k][0] == "-" ||  Pengguna[i][j][k][0] == "" ||  Pengguna[i][j][k][0] == " "){
                    continue;
                }else if (Pengguna[i][j][k][1] == Kegiatan[katalog][0]) {
                        cout << setw(15) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                        ada = true;
                    }
                }
            }

            if (!ada) {
                cout << setw(15) << " " << "[NONE]" << endl;
            }

            cout << endl;
        }
        cout << "=====================================\n";
    }
}

void UrutSesuaiKatalog(int katlog[]){
    cout << endl;
    setWarna(WARNA_HEADER);
    cout << "===== Daftar User Berdasarkan Kegiatan =====" << endl;
    setWarna(WARNA_NORMAL);

    forLantai(0, Lantai){
        cout << "Lantai ke-" << i + 1 << endl;
        forAP(0, DataBaseUser[i]){
            cout << setw(10) << " " << "AP ke-" << j + 1 << endl;
            int range = stringToIntManual(WifiConnfigur[i][4]);
            bool ada = false;

            for (int katalog = 0; katalog < 5; katalog++) {
                forUserPerAP(0, range) {
                    if (Pengguna[i][j][k][0] == "-" || Pengguna[i][j][k][0] == "" || Pengguna[i][j][k][0] == " ") {
                        continue;
                    } else if (Pengguna[i][j][k][1] == Kegiatan[katlog[katalog] - 1][0]) {
                        cout << setw(15) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                        ada = true;
                    }
                }
            }

            if (!ada) {
                cout << setw(15) << " " << "[NONE]" << endl;
            }

            cout << endl;
        }
        cout << "=====================================\n";
    }
}


///==============Searching=============
void Searching(){
    Navbar();
    cout << endl;
    cout << "Kategori Search: \n";
    cout << "1. Cari Nama dan Lokasi User. \n";
    cout << "2. Tampilkan semua yang kegiatannnya sama. \n";
    cout << "Pilih: "; char pil; cin >> pil;

    switch(pil){
        case '1':{
        CariNama();
        break;
        } case '2':{
        cariBerdasarkanKegiatan();
        break;
        }default:{
        setWarna(WARNA_CYAN);
        cout << "\nMi scusi... menu belum tersedia. \n";
        setWarna(WARNA_NORMAL);
        pauseScreen();
        Searching();
        break;
        }
    }

}

void CariNama(){
    setWarna(WARNA_HEADER);
    cout << "===== Searching (PerNama) =====" << endl;
    setWarna(WARNA_NORMAL);

    setWarna(WARNA_UNGU);
    cout << "Masukan Nama "; warnaText("(HARUS SESUAI!)", WARNA_KUNING); cout << " : ";
    string user; cin >> user;
    setWarna(WARNA_NORMAL);
    forLantai(0, Lantai){
        bool lanntaipass = true;
        forAP(0, DataBaseUser[i]){
        int range = stringToIntManual(WifiConnfigur[i][4]);
        bool pass = true;
            forUserPerAP(0, range){
                if(Pengguna[i][j][k][0] == user){
                    if(lanntaipass){
                        cout << "Lantai " << i+1 << ": \n";
                        lanntaipass = false;
                    }
                    if(pass){
                        cout << setw(10) << " " << "AP Ke-" << j+1 << ": \n";
                        pass = false;
                }
                    cout << setw(15) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                }
            }
        }
    }

    cout << endl;
    pauseScreen();
}

void cariBerdasarkanKegiatan(){
    setWarna(WARNA_HEADER);
    cout << "===== Searching (PerKategori Kegiatan) =====" << endl;
    setWarna(WARNA_NORMAL);

    cetakKatalog();
    setWarna(WARNA_UNGU);
    cout << "Masukan Nama "; warnaText("(HARUS SESUAI!)", WARNA_KUNING); cout << " : ";
    string ket; cin >> ket;
    setWarna(WARNA_NORMAL);
    forLantai(0, Lantai){
        bool lanntaipass = true;
        forAP(0, DataBaseUser[i]){
        int range = stringToIntManual(WifiConnfigur[i][4]);
        bool pass = true;
            forUserPerAP(0, range){
                if(Pengguna[i][j][k][0] == ket){
                    if(lanntaipass){
                        cout << "Lantai " << i+1 << ": \n";
                        lanntaipass = false;
                    }
                    if(pass){
                        cout << setw(10) << " " << "AP Ke-" << j+1 << ": \n";
                        pass = false;
                }
                    cout << setw(15) << " " << "Nama: " << Pengguna[i][j][k][0]<< " || Kegiatan: " << Pengguna[i][j][k][1] << endl;
                }
            }
        }
    }

    cout << endl;
    pauseScreen();
}


//===============cetak==================
void cetakKategori(){
    if (WifiCategoryList[0][0].empty()) {
    cout << "Belum ada data kategori WiFi. Tambahkan di WifiCategory.txt\n";
    return;
    }
    cout << "============================================\n";
       fori(0, 10){
            cout << "Wifi Kategory ke-" << i+1 << ": \n";
            cout << "MerekWiFi : " << WifiCategoryList[i][0] << endl;
            cout << "AccessPoint : " << setw(50) << left << WifiCategoryList[i][1] <<endl;
            cout << "KecepatanWiFi : " << setw(50) << left << WifiCategoryList[i][2] << endl;
            cout << "KecepatanAP : " << setw(50) << left << WifiCategoryList[i][3]  << endl;
            cout << "MaxUser : " << setw(50) << left << WifiCategoryList[i][4] << endl;
            cout << "============================================\n";
            cout << endl;
    }
    cout << "============================================\n";
    cout << endl;
}

///==============MENNU 4=====================
void gantiAtauTambah(){
    Navbar();

    cout << "Menu pilihan: \n";
    cout << "1. Ganti Configure Wifi per Lantai. \n";
    cout << "2. Tambah user. \n";
    cout << "3. Hapus User. \n";
    cout << "4. Kosongkan pengunaan Wifi di AP yang ditentukan ("; setWarna(WARNA_MERAH); cout << "RISK!"; setWarna(WARNA_NORMAL); cout <<"). \n";
    cout << "5. Hapus Semua Pengguna Wifi ("; setWarna(WARNA_MERAH); cout << "RISK!"; setWarna(WARNA_NORMAL); cout <<"). \n";
    cout << "Menu yang dipilih: "; char p; cin >> p;

    switch(p){
    case '1':{
        ChangeConnfigure();
        pauseScreen();
        break;
    } case '2':{
        AddUser();
        break;
    } case '3':{
        RemoveUser();
        break;
    } case '4':{
        RemoveUserperLantai();
        break;
    } case '5':{
        char pil;
        cout << "Anda Yakin? Semua user akan "; setWarna(WARNA_MERAH); cout << "DIHAPUS"; setWarna(WARNA_NORMAL); cout <<"\n";
        cout << "(Y/N)"; cin >> pil;

        if(pil == 'y' || pil == 'Y'){
            forLantai(0, Lantai){
                forAP(0, DataBaseUser[i]){
                    int maxUser = stringToIntManual(WifiConnfigur[i][4]);
                    forUserPerAP(0, maxUser){
                        Pengguna[i][j][k][0] = "-";
                        Pengguna[i][j][k][1] = "-";
                    }
                }
            }
        Sleep(1200);
        SimpaDataUserPerAP();
        PageLoading2();
        PageUtama();
        }
        else{
        PageUtama();
        }
        break;
    }default:{
        cout << "Pilihan tidak tersedia!\n";
        pauseScreen();
        gantiAtauTambah();
        break;
    }
    }
}

void ChangeConnfigure(){
    int KeyLantai, KeyKatalog, keyAP; char lagi, gantiAP;
    setWarna(WARNA_HEADER);
    cout << "===== Change Configure Wifi Per-Lantai =====" << endl;
    setWarna(WARNA_NORMAL);

    cout << "Katalog Wifi yang tersedia: \n";
    cetakKategori();
    cout << endl;

    cout << "Max Lantai Perusahaan Anda: " ; warnaText(to_string(Lantai), WARNA_HIJAU); cout << endl;
    cout << "Pilih salah satu dari lantai Perusahann Anda. \n";
    do{
    cout << "Lantai yang Dipilih: "; cin >> KeyLantai;
    cout << "Katageori Wifi Yang Dipilih: "; cin >> KeyKatalog;

    WifiConnfigur[KeyLantai-1][0] = WifiCategoryList[KeyKatalog-1][0]; //MerekWifi
    WifiConnfigur[KeyLantai-1][1] = WifiCategoryList[KeyKatalog-1][1]; //MerekAP
    WifiConnfigur[KeyLantai-1][2] = WifiCategoryList[KeyKatalog-1][2]; //KEcepatanWifi
    WifiConnfigur[KeyLantai-1][3] = WifiCategoryList[KeyKatalog-1][3]; //KecepatanAp
    WifiConnfigur[KeyLantai-1][4] = WifiCategoryList[KeyKatalog-1][4]; //MaxUser

    cout << "Ingin Merubah AP dilanntai ini? "; cin >> gantiAP;

    if(gantiAP == 'y' || gantiAP == 'Y'){
        cout << "Total AP dilantai ini: "; warnaText(to_string(DataBaseUser[KeyLantai-1]),WARNA_HIJAU);
        cout << "\nUbah Menjadi: "; cin >> keyAP;
        DataBaseUser[KeyLantai-1] = keyAP;
    }

    cout << "Configure Lantai Lagi? "; cin >> lagi;
    }while(lagi == 'Y' || lagi == 'y');

    Sleep(500);
    SimpanDataWifiUser();
    PageLoading2();
    PageUtama();
}

void AddUser(){
    int keyLantai, keyAP;
    char pilih;
    string user;
    int keyGit;
    bool ulang = true;

    cout << endl;
    TampilUrut();
    cout << endl;

    do {

        do {
            cout << "Lantai Ke Berapa? (1 - " << Lantai << "): ";
            cin >> keyLantai;
            if (keyLantai < 1 || keyLantai > Lantai) {
                cout << "Lantai tidak valid! Coba lagi.\n";
            }
        } while (keyLantai < 1 || keyLantai > Lantai);

        do {
            cout << "AP Ke Berapa? (1 - " << DataBaseUser[keyLantai - 1] << "): ";
            cin >> keyAP;
            if (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]) {
                cout << "AP tidak valid! Coba lagi.\n";
            }
        } while (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]);

        cetakKatalog();
        cout << "Masukan Nama User: ";
        cin >> user;

        do {
            if (!ulang) {
                cout << "Harus Sesuai Dengan Nomor Katalog (1-5)!\n";
            }
            cout << "Masukan Nomor Kegiatannya: ";
            cin >> keyGit;
            ulang = false;
        } while (keyGit < 1 || keyGit > 5);

        int range = stringToIntManual(WifiConnfigur[keyLantai - 1][4]);
        forUserPerAP(0, range) {
            if (Pengguna[keyLantai - 1][keyAP - 1][k][0] == "-" || Pengguna[keyLantai - 1][keyAP - 1][k][0] == "" || Pengguna[keyLantai - 1][keyAP - 1][k][0] == " ") {
                Pengguna[keyLantai - 1][keyAP - 1][k][0] = user;
                Pengguna[keyLantai - 1][keyAP - 1][k][1] = Kegiatan[keyGit - 1][0];
                break;
            }
        }

        cout << "Ada lagi Yang Ingin Ditambah? (Y/N): ";
        cin >> pilih;
        ulang = true;

    } while (pilih == 'y' || pilih == 'Y');

    Sleep(600);
    SimpaDataUserPerAP();
    PageLoading2();
    PageUtama();
}


void RemoveUser(){
    int keyLantai, keyAP;
    char pilih;
    string user;
    int keyGit;
    bool ulang = true;

    cout << endl;
    TampilUrut();
    cout << endl;

    do {

        do {
            cout << "Lantai Ke Berapa? (1 - " << Lantai << "): ";
            cin >> keyLantai;
            if (keyLantai < 1 || keyLantai > Lantai) {
                cout << "Lantai tidak valid! Coba lagi.\n";
            }
        } while (keyLantai < 1 || keyLantai > Lantai);

        do {
            cout << "AP Ke Berapa? (1 - " << DataBaseUser[keyLantai - 1] << "): ";
            cin >> keyAP;
            if (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]) {
                cout << "AP tidak valid! Coba lagi.\n";
            }
        } while (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]);

        cout << "Masukan Nama User "; warnaText("(HARUS SESUAI!)", WARNA_KUNING); cout << ": ";
        cin >> user;

        int range = stringToIntManual(WifiConnfigur[keyLantai - 1][4]);
        forUserPerAP(0, range) {
            if (Pengguna[keyLantai - 1][keyAP - 1][k][0] == user) {
                Pengguna[keyLantai - 1][keyAP - 1][k][0] = "-";
                Pengguna[keyLantai - 1][keyAP - 1][k][1] = "-";
                break;
            }
        }

        cout << "Ada lagi Yang Ingin Ditambah? (Y/N): ";
        cin >> pilih;
        ulang = true;

    } while (pilih == 'y' || pilih == 'Y');

    Sleep(600);
    SimpaDataUserPerAP();
    PageLoading2();
    PageUtama();
}

void RemoveUserperLantai(){
    int keyLantai, keyAP;
    char pilih;
    bool ulang = true;

    cout << endl;
    TampilUrut();
    cout << endl;

    do {

        do {setWarna(WARNA_KUNING);
            cout << "Lantai Ke Berapa? (1 - " << Lantai << "): ";
            cin >> keyLantai;
            if (keyLantai < 1 || keyLantai > Lantai) {
                cout << "Lantai tidak valid! Coba lagi.\n";
            }
        } while (keyLantai < 1 || keyLantai > Lantai);

        do {
            cout << "AP Ke Berapa? (1 - " << DataBaseUser[keyLantai - 1] << "): ";
            cin >> keyAP;
            if (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]) {
                cout << "AP tidak valid! Coba lagi.\n";
            }
        } while (keyAP < 1 || keyAP > DataBaseUser[keyLantai - 1]);


        int range = stringToIntManual(WifiConnfigur[keyLantai - 1][4]);
            forUserPerAP(0, range) {
                    Pengguna[keyLantai - 1][keyAP - 1][k][0] = "-";
                    Pengguna[keyLantai - 1][keyAP - 1][k][1] = "-";
            }
        cout << "Ada lagi Yang Ingin Ditambah? (Y/N): ";
        cin >> pilih;
        ulang = true;

    } while (pilih == 'y' || pilih == 'Y');

    Sleep(600);
    SimpaDataUserPerAP();
    PageLoading2();
    PageUtama();
}

///=========Page-New-User====================
void NewPenggunna(){
    if(!PunyaDatabase){
        system("cls");
        Navbar();
        cout << endl;
        cout << "Selamat Datang Di WIFI Analyze ^^\n";
        cout << "Akun Anda berhasil dibuat!\n";
        cout << "Silakan lanjutkan konfigurasi awal sistem jaringan perusahaan Anda.\n\n";

        cout << "============================================\n";\
        cout << "Setup Awal Jaringan Wifi Perusahaan\n";
        cout << "============================================\n\n";

        cout << "Berapa lantai yang dimiliki oleh perusahaan Anda? ";
        cin >> Lantai;

        cout << endl;

        fori(0, Lantai){
            cout << "> Jumlah AP (Accses Point) Lantai " << i+1 << ": ";
            cin >> DataBaseUser[i];
        }
        cout << endl;
        cout << "Selamat membangun sistem jaringan profesional Anda bersama WifiAnalyze!\n";
        PunyaDatabase = true;
        Sleep(1200);
        NewInputUnntukPenggunnaBaru();
    }
}

void NewInputUnntukPenggunnaBaru(){
    int MaxCategori = sizeof(WifiCategoryList) / sizeof(WifiCategoryList[0]);

    system("cls");
    Navbar();
    cout << endl;
    cout << "Selamat Datang Di WIFI Analyze ^^\n";
    cout << "Wifi dan AP Kategori yang Tersedia: \n\n";
    cetakKategori();

    cout << "Masukan Kategory Wifi Setiap Lantai: (Pilih Sesuai Dengan Urutan Wifi Saja)\n";
    fori(0, Lantai){
        int pilih;
        do{
        cout << "Lantai ke-" << i+1 <<": ";
        cin >> pilih; pilih--;

        if(pilih > MaxCategori || pilih < 0){
            cout << "Pilihan Tidak Tersedia! \n";
            Sleep(500);}
        }while (pilih < 0 || pilih >= MaxCategori);

        //Masukinn Ke Array WifiConnfigur
        WifiConnfigur[i][0] = WifiCategoryList[pilih][0]; //MerekWifi
        WifiConnfigur[i][1] = WifiCategoryList[pilih][1]; //MerekAP
        WifiConnfigur[i][2] = WifiCategoryList[pilih][2]; //KEcepatanWifi
        WifiConnfigur[i][3] = WifiCategoryList[pilih][3]; //KecepatanAp
        WifiConnfigur[i][4] = WifiCategoryList[pilih][4]; //MaxUser

        //Masukinn Ke Array ApSpeed
        forAP(0, DataBaseUser[i]){
            APSpeed[i][j][0] = WifiCategoryList[pilih][3];
            APSpeed[i][j][1] = "None";

            forUserPerAP(0, 1){
                Pengguna[i][j][k][0] = "Belum4daIs1nyaMasihK0SONG";
                Pengguna[i][j][k][1] = " ";
            }
        }

    }
    SimpanDataWifiUser();SimpanDataKecepatanAP(); SimpaDataUserPerAP();
    system("Pause");
}

void SimpanDataWifiUser() { //Nulis Ulang makannya nanti bakal ke reset data nya
    ofstream file(pathFile1User);

    file << "################################" << endl;
    file << "Jumlah Lantai = " << Lantai << endl;
    fori(0, Lantai) {
        file << "> Lantai " << i + 1 << " = " << DataBaseUser[i] << endl;
    }
    file << "################################" << endl << endl;

    fori(0, Lantai) {
        file << "================================" << endl;
        file << "Lantai " << i + 1 << ":" << endl;
        file << "MerekWiFi    : " << WifiConnfigur[i][0] << endl;
        file << "AccessPoint  : " << WifiConnfigur[i][1] << endl;
        file << "KecepatanWiFi: " << WifiConnfigur[i][2] << endl;
        file << "KecepatanAP  : " << WifiConnfigur[i][3] << endl;
        file << "MaxUser      : " << WifiConnfigur[i][4] << endl;
        file << "================================" << endl << endl;
    }

    file.close();
}

void SimpanDataKecepatanAP(){
    ofstream file(pathFile3User);

    file << "=================================" << endl;
    file << "Total Lantai = " << Lantai << endl;
    file << "=================================" << endl << endl;

    forLantai(0, Lantai){
        file << ">> Lantai " << i + 1 << " = " << DataBaseUser[i] << endl;
        forAP(0, DataBaseUser[i]){
            file << setw(10) << " " << "AccessPoint = " << APSpeed[i][j][0] << " || " << "Kecepatan User = " << APSpeed[i][j][1] << endl;
        }
        file << endl << endl;
    }
    file << "=================================" << endl << endl;
    file.close();
}

void SimpaDataUserPerAP() {
    ofstream file(pathFile2User);
    file << "=================================" << endl;
    file << "Total Lantai = " << Lantai << endl;
    file << "=================================" << endl << endl;

    forLantai(0, Lantai) {
        file << ">> Lantai " << i + 1 << " = " << DataBaseUser[i] << endl;

        forAP(0, DataBaseUser[i]) {
            int maxUser = stringToIntManual(WifiConnfigur[i][4]); // pakai konversi manual kamu
            file << setw(10) << " " << "AccessPoint = " << j + 1 << endl;

            bool adaUser = false;

            forUserPerAP(0, maxUser) {
                string& nama = Pengguna[i][j][k][0];
                string& kegiatan = Pengguna[i][j][k][1];

                if (nama == "-" || nama == "" || nama == " " || nama == "Belum4daIs1nyaMasihK0SONG") continue;

                adaUser = true;
                file << setw(15) << " " << "Nama = " << nama << " || Kegiatan = " << kegiatan << endl;
            }

            if (!adaUser) {
                file << setw(15) << " " << "[None]" << endl;
            }

            file << endl;
        }

        file << endl << endl;
    }

    file << "=================================" << endl << endl;
    file.close();
}


//=======Page Pilihan Dari Menu Utama========
void cetakKonfigurasWifiUser() {
    system("cls"); // Typo kamu tulis 'sytem'
    Navbar();

    fori(0, Lantai) {
        cout << "===========================\n";
        setWarna(WARNA_LOADING);
        cout << "Konfigurasi WiFi - Lantai " << i + 1 << endl;
        setWarna(WARNA_NORMAL);
        cout << "===========================\n";
        cout << "Merek WiFi     : " << WifiConnfigur[i][0] << endl;
        cout << "Access Point   : " << WifiConnfigur[i][1] << endl;
        cout << "Kecepatan WiFi : " << WifiConnfigur[i][2] << endl;
        cout << "Kecepatan AP   : " << WifiConnfigur[i][3] << endl;
        cout << "MAX User       : " << WifiConnfigur[i][4] << endl;
        cout << endl;
    }

    pauseScreen();
    PageUtama();
}

//==========Page


//==========Tambahan===========
void init() {
    reconDatabase();
    KegiatanData();
    WifikonfigurasiList();
}

void CekSSemuaDataUser(){
    dataUser();
    cekbase();
    CekDatabaseUser();
    KegiatanData();

    //====Buat-Masukin Data Ke array===
    if(PunyaDatabase){
        WifiConnfigureIN();
        PenggunaIN();
        APSpeedIN();
        //DataBaseUserIN();
        KegiatanIN();

        //Cloning Data
        CloningData();
    }

}

void pauseScreen() {
    cout << "Tekan tombol untuk kembali..."; getch();
}

///============Cloing===========
void CloningData(){
    forLantai(0, Lantai){
        int maxUser = stoi(WifiConnfigur[i][4]);
        forAP(0, DataBaseUser[i]){

            //=======UtukKonnfigurasi Wifi setiap lantai=======
            forz(0, 5){CloneWifiConnfigur[i][z] = WifiConnfigur[i][z];}
            forUserPerAP(0, maxUser){
                //===========Utuk speedAP=========
                CloneAPSpeed[i][j][0] = APSpeed[i][j][0];
                CloneAPSpeed[i][j][1] = APSpeed[i][j][1];

                //=========Untuk User yanng terkonnekasi========
                ClonePengguna[i][j][k][0] = Pengguna [i][j][k][0];
                ClonePengguna[i][j][k][1] = Pengguna [i][j][k][1];
            }
        }
    }
}


int main(){
    init();
    PageAwal();
    return 0;
}
