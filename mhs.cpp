#include <iostream>
#include <cstring>

// node nilai
struct Nilai
{
    // menyimpan data nilai
    int data;
    // link ke node selanjutnya
    Nilai *next;
};

// class queue
class Queue
{
    // front = node nilai pertama diinput; rear = node nilai terakhir diinput
    Nilai *front, *rear;

public:
    // pertama kali dibuat, tidak ada node nilai di dalam queue
    Queue()
    {
        front = rear = NULL;
    }
    // mengecek apakah queue kosong
    bool isempty()
    {
        return front == NULL;
    }
    // memasukkan nilai
    void enqueue(int nilai)
    {
        // node baru
        Nilai *temp = new Nilai();
        temp->data = nilai;
        temp->next = NULL;

        // apabila queue masih kosong
        if (isempty())
        {
            // front dan rear akan menunjuk pada node nilai saat ini, selesai
            front = rear = temp;
            return;
        }

        // link rear akan menunjuk pada node nilai saat ini
        rear->next = temp;
        // node nilai saat ini menduduki posisi rear
        rear = temp;
    }
    // mengambil nilai
    int dequeue()
    {
        int nilai = front->data;

        // apabila queue kosong, maka return 0
        if (isempty())
            return 0;

        // node selanjutnya menduduki posisi front
        Nilai *temp = front;
        front = front->next;

        // apabila setelah itu queue kosong, maka posisi rear adalah NULL
        if (isempty())
            rear = NULL;

        delete temp;

        return nilai;
    }
};

// class mahasiswa
class Mahasiswa
{
    std::string nama;
    std::string nim;
    float ipk;

public:
    void calcipk(Queue data)
    {
        float total = 0;
        while (!data.isempty())
        {
            total += data.dequeue();
        }
        this->ipk = (total / (8 * 100)) * 4;
    }
    void setnama(std::string nama)
    {
        this->nama = nama;
    }
    void setnim(std::string nim)
    {
        this->nim = nim;
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
void showfirstrank(Mahasiswa *);
void findmhs(Mahasiswa *, const char *, int);

// main program
int main()
{
    // deklarasi variabel lokal
    std::string matkul[] = {"Lingkungan Bisnis", "Komunikasi Data",
                            "Struktur Data", "Bahasa Inggris",
                            "Sistem Operasi", "Pemrograman",
                            "Komputer Grafis", "Hardware/Software"};

    std::string nama = "\0";
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

    // mengeluarkan mahasiswa ipk tertinggi
    std::cout << "PERINGKAT 1\n " << std::endl;
    showfirstrank(mahasiswa);

    // menemukan rangking mahasiswa
    std::cout << "Masukkan nama yang dicari: ";
    std::cin.ignore();
    getline(std::cin, nama);
    findmhs(mahasiswa, nama.c_str(), numof_mhs);

    // bebaskan blok memori mahasiswa
    delete[] mahasiswa;

    return 0;
}

void setdatas(int size_a, int size_b, std::string *arr, Mahasiswa *obj)
{
    Queue nilai;
    std::string nama;
    std::string nim;
    int nilai_temp;

    for (int i = 0; i < size_a; i++)
    {
        std::cout << "Mahasiswa ke-" << (i + 1) << std::endl;
        // input nama
        std::cout << "Masukkan nama mahasiswa: ";
        std::cin.ignore();
        getline(std::cin, nama);
        (obj + i)->setnama(nama);
        // input nim
        std::cout << "Masukkan nim mahasiswa : ";
        std::cin >> nim;
        (obj + i)->setnim(nim);
        std::cout << std::endl;

        // input nilai matkul mahasiswa
        for (int j = 0; j < size_b; j++)
        {
            std::cout << "Masukkan nilai matkul " << *(arr + j) << " : ";
            std::cin >> nilai_temp;
            nilai.enqueue(nilai_temp);
        }

        // menghitung ipk mahasiswa
        (obj + i)->calcipk(nilai);

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

void showfirstrank(Mahasiswa *obj)
{
    std::cout << "Nama : " << (obj + 0)->getnama() << std::endl;
    std::cout << "NIM  : " << (obj + 0)->getnim() << std::endl;
    std::cout << "IPK  : " << (obj + 0)->getipk() << std::endl;
    std::cout << std::endl;
}

void findmhs(Mahasiswa *obj, const char *target, int it)
{
    bool finded = false;
    for (int i = 0; i < it; i++)
    {
        if ((obj + i)->getnama() == target)
        {
            std::cout << "Hasil:" << std::endl;
            printf("%s ada di peringkat ke-%d", target, i + 1);
            finded = true;
            break;
        }
    }
    if (!finded)
    {
        std::cout << "Nama tidak ditemukan" << std::endl;
    }
}