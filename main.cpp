#include <iostream>
#include <string>
#include <cstring> // library manipulasi char buat c
using namespace std;

#define FILE_NAME "daftar.dat"
#define ARRAY_SIZE 100
#define STRING_SIZE 255

typedef struct
{
    string judul;
    string penyanyi;
    string genre;
    int tahun;
} lagu;

void quicksort(string *array, int awal, int akhir)
{
    int low = awal, high = akhir;
    string pivot = array[(awal + akhir) / 2];
    int temp;
    do
    {
        while (array[low] < pivot)
            low++;
        while (array[high] > pivot)
            high--;
        if (low <= high)
        {
            swap(array[low], array[high]);
            low++;
            high--;
        }
    } while (low <= high);
    if (awal < high)
        quicksort(array, awal, high);
    if (low < akhir)
        quicksort(array, low, akhir);
}

int binary_search(string *arrayPlaylist, string pencarian, int index_akhir)
{
    int index_awal = 0;
    bool search = false;
    while (search == false && index_awal <= index_akhir)
    {
        int mid = (index_awal + index_akhir) / 2;
        if (arrayPlaylist[mid] == pencarian)
        {
            return mid;
        }
        else
        {
            if (pencarian < arrayPlaylist[mid])
            {
                index_akhir = mid - 1;
            }
            else
            {
                index_awal = mid + 1;
            }
        }
    }
    return -1;
}

void initfile()
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file)
    {
        file = fopen(FILE_NAME, "wb");
        char empty[STRING_SIZE] = {0};
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            fwrite(empty, sizeof(char), STRING_SIZE, file);
        }
        fclose(file);
    }
    else
    {
        fclose(file);
    }
}

void bukaList(string array[ARRAY_SIZE])
{
    FILE *fptr = fopen(FILE_NAME, "rb");
    if (!fptr)
    {
        perror("Gagal membukaList file untuk membaca");
        return;
    }

    char buffer[STRING_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        fread(buffer, sizeof(char), STRING_SIZE, fptr);
        buffer[STRING_SIZE - 1] = '\0';
        array[i] = string(buffer);
    }

    fclose(fptr);
}

void shift_down_1(string *arr)
{
    for (int i = 0; i < ARRAY_SIZE - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[ARRAY_SIZE - 1] = "";
}

void simpenList(string array[ARRAY_SIZE])
{
    FILE *fptr = fopen(FILE_NAME, "wb");
    if (!fptr)
    {
        perror("Gagal membukaList file untuk menulis");
        return;
    }
    char buffer[STRING_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        strncpy(buffer, array[i].c_str(), STRING_SIZE - 1);
        buffer[STRING_SIZE - 1] = '\0';
        fwrite(buffer, sizeof(char), STRING_SIZE, fptr);
    }

    fclose(fptr);
}

void tambah(int opsional_index = -1)
{
    string judul, penyanyi, genre;
    int tahun;

    cout << "	masukan judul		: ";
    cin.ignore();
    getline(cin, judul);
    cout << "	masukan penyanyi	: ";
    // cin.ignore();
    getline(cin, penyanyi);
    cout << "	masukan genre		: ";
    // cin.ignore();
    getline(cin, genre);
    cout << "	masukan tahun		: ";
    cin >> tahun;

    lagu tmp = {judul, penyanyi, genre, tahun};
    FILE *fptr_lagu;

    string add_ext = "lagu/" + judul + ".dat";
    const char *cstr = add_ext.c_str(); // shortcut yang tidak diajari karna tidak ada cara lain

    fptr_lagu = fopen(cstr, "w+");
    fwrite(&tmp, sizeof(lagu), 1, fptr_lagu);
    fclose(fptr_lagu);

    // list array
    string array[ARRAY_SIZE];
    bukaList(array);

    int index_terbesar = -1;
    for (int i = -1; i < ARRAY_SIZE; i++)
    {
        if (array[i] == "")
            break;
        index_terbesar = i;
    }
    if (opsional_index < 0)
    {
        array[index_terbesar + 1] = judul;
    }
    else
    {
        array[opsional_index] = judul;
    }

    quicksort(array, 0, index_terbesar + 1);
    shift_down_1(array);
    simpenList(array);

    cout << "berhasil tambah ke file" << endl;
}

void edit()
{
    string judul_lagu;
    cout << "masukan judul lagu : ";
    cin.ignore();
    getline(cin, judul_lagu);

    string array[ARRAY_SIZE];
    bukaList(array);

    int index_terbesar = -1;
    for (int i = -1; i < ARRAY_SIZE; i++)
    {
        if (array[i] == "")
            break;
        index_terbesar = i;
    }

    int index_ketemu = binary_search(array, judul_lagu, index_terbesar);
    if (index_ketemu < -1)
    {
        cout << "Data tidak ditemukan" << endl;
        return;
    }

    string ext_newf = "lagu/" + array[index_ketemu] + ".dat";
    const char *cstr = ext_newf.c_str();

    remove(cstr);
    cout << "file berhasil dihapus" << endl;
    tambah(index_ketemu);
}

void tampil()
{
    string array[ARRAY_SIZE];
    bukaList(array);
    int index_terbesar = -1;
    for (int i = -1; i < ARRAY_SIZE; i++)
    {
        index_terbesar = i;
        if (array[i] == "")
            break;
    }
    cout << endl;
    cout << "      Lagu" << endl;
    cout << "==================" << endl;
    if (index_terbesar < 1)
    {
        cout << "playlist kosong";
        return;
    }

    for (int i = 0; i < index_terbesar; i++)
    {
        cout << i << ". " << array[i] << endl;
    }
}

void cari()
{
    string judul;
    cout << "masukan judul lagu : ";
    getline(cin, judul);

    string array[ARRAY_SIZE];
    bukaList(array);

    int index_terbesar = -1;
    for (int i = -1; i < ARRAY_SIZE; i++)
    {
        if (array[i] == "")
            break;
        index_terbesar = i;
    }

    int index_ketemu = binary_search(array, judul, index_terbesar);
    if (index_ketemu > -1)
    {
        cout << "Data tidak ditemukan" << endl;
        return;
    }

    string ext = "lagu/" + array[index_ketemu] + ".dat";
    const char *cstr = ext.c_str();

    FILE *fptr_lagu;
    lagu data_lagu;

    fptr_lagu = fopen(cstr, "wb");
    fread(&data_lagu, sizeof(lagu), 1, fptr_lagu);
    fclose(fptr_lagu);

    cout << "Data ditemukan!" << endl;
    cout << "	judul		: " << data_lagu.judul << endl;
    cout << "	penyanyi	: " << data_lagu.penyanyi << endl;
    cout << "	genre		: " << data_lagu.genre << endl;
    cout << "	tahun		: " << data_lagu.tahun << endl;
    cout << endl;
}

int main()
{
    initfile();

    int pilihan;
    bool program = true;

    while (program)
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
                break;
            else
                cout << "input salah, ulangi" << endl;
        }

        switch (pilihan)
        {
        case 1:
            tambah();
            break;
        case 2:
            edit();
            break;
        case 3:
            tampil();
            break;
        case 4:
            cari();
            break;
        case 5:
            program = false;
            break;

        default:
            cout << "menu tidak tersedia" << endl;
            break;
        }
    }

    cout << "terimakasih telah memakai";
    return 0;
}