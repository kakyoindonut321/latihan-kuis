#include <iostream>
using namespace std;

void tambah()
{
}

void edit()
{
}

void tampil()
{
}

void cari()
{
}

int main()
{
    int pilihan;
    bool jalan = true;

    while (jalan)
    {
        cout << endl;
        cout << "  Playlist Lagu" << endl;
        cout << "==================" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Edit Lagu" << endl;
        cout << "3. Tampilkan Lagu" << endl;
        cout << "4. Cari Lagu" << endl;
        cout << "5. Keluar" << endl;

        while (true)
        {
            cout << "pilih : ";
            cin >> pilihan;
            if (pilihan > 0 && pilihan < 6)
            {
                break;
            }
            else
            {
                cout << "input salah, ulangi" << endl;
            }
        }

        switch (pilihan)
        {
        case 1:

            break;
        case 2:

            break;
        case 5:
            jalan = false;
            cout << "terimakasih telah memakai";
            break;

        default:
            cout << "menu tidak tersedia" << endl;
            break;
        }
    }
}