#include <iostream>

// class mahasiswa
class Mahasiswa
{
    std::string nama;
    std::string nim;
    float ipk;

public:
    void setnama()
    {
        std::cout << "Masukkan nama mahasiswa: ";
        std::cin.ignore();
        getline(std::cin, nama);
    }
    void setnim()
    {
        std::cout << "Masukkan nim mahasiswa : ";
        std::cin >> nim;
    }
    void calcipk(float *arr, int it)
    {
        float total = 0;
        for (int i = 0; i < it; i++)
        {
            total += *(arr + i);
        }
        ipk = (total / (it * 100)) * 4;
    }
    std::string getnama()
    {
        return nama;
    }
    std::string getnim()
    {
        return nim;
    }
    float getipk()
    {
        return ipk;
    }
};

void setdatas(int, int, std::string *, Mahasiswa *);
void sortrank(Mahasiswa *, int);
void getdatas(Mahasiswa *, int);

// main program
int main()
{
    // deklarasi variabel lokal
    std::string matkul[] = {"Lingkungan Bisnis", "Komunikasi Data",
                            "Struktur Data", "Bahasa Inggris",
                            "Sistem Operasi", "Pemrograman",
                            "Komputer Grafis", "Hardware/Software"};
    int numof_matkul = (sizeof(matkul) / sizeof(std::string));
    int numof_mhs = 0;

    std::cout << "PROGRAM INPUT MAHASISWA\n " << std::endl;

    // meminta jumlah mahasiswa yang akan diinputkan
    std::cout << "Masukkan jumlah mahasiswa yang akan diinputkan : ";
    std::cin >> numof_mhs;
    std::cout << std::endl;

    // alokasi blok memori mahasiswa
    Mahasiswa *mahasiswa = new Mahasiswa[numof_mhs];

    // input data mahasiswa
    setdatas(numof_mhs, numof_matkul, matkul, mahasiswa);

    // mengurutkan mahasiswa dari ipk terbesar
    sortrank(mahasiswa, numof_mhs);

    // mengeluarkan data mahasiswa
    std::cout << "DATA RANKING MAHASISWA\n " << std::endl;
    getdatas(mahasiswa, numof_mhs);

    // bebaskan blok memori mahasiswa
    delete[] mahasiswa;

    return 0;
}

void setdatas(int size_a, int size_b, std::string *arr, Mahasiswa *obj)
{
    float *nilai = NULL;
    for (int i = 0; i < size_a; i++)
    {
        // alokasi blok memori nilai matkul
        nilai = new float[size_b];

        // input nama dan nim
        std::cout << "Mahasiswa ke-" << (i + 1) << std::endl;
        (obj + i)->setnama();
        (obj + i)->setnim();
        std::cout << std::endl;

        // input nilai matkul mahasiswa
        for (int j = 0; j < size_b; j++)
        {
            std::cout << "Masukkan nilai matkul " << *(arr + j) << " : ";
            std::cin >> *(nilai + j);
        }

        // menghitung ipk mahasiswa
        (obj + i)->calcipk(nilai, size_b);

        // bebaskan blok memori nilai matkul yang dialokasikan
        delete[] nilai;

        std::cout << std::endl;
    }
}

void sortrank(Mahasiswa *obj, int it)
{
    Mahasiswa temp;
    int j = 0, method = 0, maks = 0, loop = 1;

    while (loop)
    {
        std::cout << "\nPilihan metode sorting:" << std::endl;
        std::cout << "1. Bubble sort\n2. Selection sort\n3. Insertion sort\n";
        std::cout << "Masukkan pilihan anda: ";
        std::cin >> method;
        std::cout << std::endl;

        switch (method)
        {
        case 1:
            // bubble sort
            for (int i = 0; i < it; i++)
            {
                for (int j = i + 1; j < it; j++)
                {
                    if ((obj + i)->getipk() < (obj + j)->getipk())
                    {
                        temp = *(obj + i);
                        *(obj + i) = *(obj + j);
                        *(obj + j) = temp;
                    }
                }
            }
            loop = 0;
            break;
        case 2:
            // selection sort
            for (int i = 0; i < it; i++)
            {
                maks = i;
                for (int j = i + 1; j < it; j++)
                {
                    if ((obj + maks)->getipk() < (obj + j)->getipk())
                        maks = j;
                }
                if ((obj + i)->getipk() != (obj + maks)->getipk())
                {
                    temp = *(obj + i);
                    *(obj + i) = *(obj + maks);
                    *(obj + maks) = temp;
                }
            }
            loop = 0;
            break;
        case 3:
            // insertion sort
            for (int i = 0; i < it; i++)
            {
                temp = *(obj + i);
                j = i - 1;
                while ((obj + j)->getipk() < temp.getipk() && j >= 0)
                {
                    *(obj + j + 1) = *(obj + j);
                    j--;
                }
                *(obj + j + 1) = temp;
            }
            loop = 0;
            break;
        default:
            std::cout << "Silahkan pilih menu yang ada...\n " << std::endl;
            break;
        }
    }
}

void getdatas(Mahasiswa *obj, int it)
{
    for (int i = 0; i < it; i++)
    {
        std::cout << "RANKING-" << i + 1 << std::endl;
        std::cout << "Nama : " << (obj + i)->getnama() << std::endl;
        std::cout << "NIM  : " << (obj + i)->getnim() << std::endl;
        std::cout << "IPK  : " << (obj + i)->getipk() << std::endl;
        std::cout << std::endl;
    }
}