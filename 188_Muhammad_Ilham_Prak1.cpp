#include <iostream>
using namespace std;

struct DataSupir
{
  string nama;
  int id;
  struct date
  {
    int day, month, year;
  } tgllahir;
  char kelamin;
  string alamat;
  DataSupir *next;
  DataSupir *prev;
};

DataSupir *head = nullptr, *tail = nullptr, *current = nullptr, *newNode = nullptr, *cur = nullptr;

void tambahSupir(const DataSupir &driver)
{
  DataSupir *newNode = new DataSupir;
  *newNode = driver;
  newNode->next = nullptr;

  if (!head)
  {
    head = newNode;
    tail = newNode;
  }
  else
  {
    tail->next = newNode;
    tail = newNode;
  }
}

void tampilkanInfoSupir(const DataSupir &driver)
{
  cout << "=================================" << endl;
  cout << "           Data Supir            "<< endl;
  cout << "=================================" << endl;
  cout << "|Nama      : " << driver.nama << "     |"<<endl;
  cout << "|Id        : " << driver.id << "               |" << endl;
  cout << "|Tgl Lahir : " << driver.tgllahir.day << "-" << driver.tgllahir.month << "-" << driver.tgllahir.year << "          |" << endl;
  cout << "|Kelamin   : " << driver.kelamin << "                  |" << endl;
  cout << "|Alamat    : " << driver.alamat << "           |" << endl;
  cout << "=================================" << endl;
}

DataSupir *cariSupir(int id)
{
  DataSupir *temp = head;
  while (temp)
  {
    if (temp->id == id)
    {
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

void hapusDataSupir(int id)
{
  DataSupir *cur = head;
  DataSupir *prev = nullptr;

  while (cur != nullptr)
  {
    if (cur->id == id)
    {
      if (prev == nullptr)
      {
        head = cur->next;
      }
      else
      {
        prev->next = cur->next;
      }
      delete cur;
      cout << "Supir dengan Id " << id << " berhasil dihapus !" << endl;
      return;
    }
    prev = cur;
    cur = cur->next;
  }
  cout << "Tidak ada supir dengan Id " << id << endl;
}

void ubahDataSupir(int id)
{
  DataSupir *foundSupir = cariSupir(id);
  if (foundSupir)
  {
    cout << "- Mengubah supir dengan Id " << id << " -" << endl;
    cout << "1. Ubah Nama" << endl;
    cout << "2. Ubah Kelamin" << endl;
    cout << "3. Ubah Alamat" << endl;
    cout << "4. Ubah Tgl Lahir" << endl;
    cout << "> ";
    int pilihan;
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
    {
      cout << "Masukkan Nama yang baru: ";
      cin.ignore();
      getline(cin, foundSupir->nama);
      break;
    }
    case 2:
    {
      cout << "Masukkan Kelamin (l/p) yang baru: ";
      cin >> foundSupir->kelamin;
      break;
    }
    case 3:
    {
      cout << "Masukkan Alamat yang baru: ";
      cin.ignore();
      getline(cin, foundSupir->alamat);
      break;
    }
    case 4:
    {
      cout << "Masukkan Tgl Lahir yang baru (dd-mm-yyyy): ";
      cin >> foundSupir->tgllahir.day >> foundSupir->tgllahir.month >> foundSupir->tgllahir.year;
      break;
    }
    default:
    {
      cout << "Pilihan tidak valid!" << endl;
    }
    }
    cout << "Data berhasil diubah !" << endl;
  }
  else
  {
    cout << "Tidak ada supir dengan Id " << id << endl;
  }
}

void tampil()
{
  DataSupir *cur = head;
  if (!cur)
  {
    cout << "Tidak ada supir yang terdaftar." << endl;
    return;
  }
  while (cur)
  {
    tampilkanInfoSupir(*cur);
    cur = cur->next;
  }
}

void iterasiBerikutnya()
{
  if (current && current->next)
  {
    current = current->next;
    tampilkanInfoSupir(*current);
  }
  else if (head)
  {
    current = head;
    tampilkanInfoSupir(*current);
  }
  else
  {
    cout << "Tidak ada supir yang terdaftar." << endl;
  }
}

void iterasiSebelumnya()
{
  if (!head)
  {
    cout << "Tidak ada supir yang terdaftar." << endl;
    return;
  }
  DataSupir *temp = head;
  while (temp->next != current)
  {
    temp = temp->next;
  }
  current = temp;
  tampilkanInfoSupir(*current);
}

int buatSupirId(const string &nama, char jenis_kelamin, const DataSupir::date &tanggal_lahir)
{
  int id = abs(nama[0] - nama[nama.length() - 1]);
  id *= 10;
  id += (jenis_kelamin == 'M') ? 1 : 0;
  id *= 10;
  id += tanggal_lahir.day % 10;
  return id;
}

void welcome()
{
  cout << "====================" << endl;
  cout << "   Selamat Datang   " << endl;
  cout << "====================" << endl;
  cout << "1. Masuk Sebagai Admin" << endl;
  cout << "2. Masuk Sebagai User" << endl;
  cout << ">";
}

void adminDashboard()
{
  cout << "=========================" << endl;
  cout << "==== Dashboard Admin ====" << endl;
  cout << "=========================" << endl;
  cout << "1. Tampilkan Daftar Supir" << endl;
  cout << "2. Tambah Supir" << endl;
  cout << "3. Ubah Data Supir" << endl;
  cout << "4. Hapus Data Supir" << endl;
  cout << "0. Exit" << endl;
  cout << "> ";
}

void userDashboard()
{
  cout << "\n=========================" << endl;
  cout << "=======  Menu User ======" << endl;
  cout << "=========================" << endl;
  cout << "1. Tampilkan Data Supir" << endl;
  cout << "2. Data Supir Berikutnya" << endl;
  cout << "3. Data Supir Sebelumnya" << endl;
  cout << "4. Order(coming soon)" << endl;
  cout << "0. Kembali" << endl;
  cout << "> ";
}

int main()
{
  DataSupir supir1 = {"Kim Jatim Park", buatSupirId("Kim Jatim Park", 'M', {12, 2, 2001}), {12, 2, 2001}, 'M', "Surabaya"};
  tambahSupir(supir1);

  int pilihMenuUtama;
  do
  {
    welcome();
    cin >> pilihMenuUtama;
    switch (pilihMenuUtama)
    {
    case 1:
    {
      int menuAdmin;
      do
      {
        adminDashboard();
        cin >> menuAdmin;

        switch (menuAdmin)
        {
        case 1:
          tampil();
          break;
        case 2:
        {
          DataSupir supirBaru;
          cout << "Masukkan Nama: ";
          cin.ignore();
          getline(cin, supirBaru.nama);
          cout << "Masukkan Tgl Lahir (dd mm yyyy): ";
          cin >> supirBaru.tgllahir.day >> supirBaru.tgllahir.month >> supirBaru.tgllahir.year;
          cout << "Masukkan Jenis Kelamin (M/F): ";
          cin >> supirBaru.kelamin;
          cout << "Masukkan Alamat: ";
          cin.ignore();
          getline(cin, supirBaru.alamat);
          supirBaru.id = buatSupirId(supirBaru.nama, supirBaru.kelamin, supirBaru.tgllahir);
          tambahSupir(supirBaru);
          break;
        }
        case 3:
        {
          int id;
          cout << "Masukkan Id Supir yang ingin diubah: ";
          cin >> id;
          ubahDataSupir(id);
          break;
        }
        case 4:
        {
          int id;
          cout << "Masukkan Id Supir yang ingin dihapus: ";
          cin >> id;
          hapusDataSupir(id);
          break;
        }
        case 0:
          break;
        default:
          cout << "Pilihan tidak valid!" << endl;
        }
      } while (menuAdmin != 0);
      break;
    }
    case 2:
    {
      int pilihMenuUser;
      do
      {
        userDashboard();
        cin >> pilihMenuUser;
        
        switch (pilihMenuUser)
        {
        case 1:
          tampil();
          break;
        case 2:
          iterasiBerikutnya();
          break;
        case 3:
          iterasiSebelumnya();
          break;
        case 0:
          break;
        default:
          cout << "Pilihan yang anda masukankan tidak valid!" << endl;
        }
      } while (pilihMenuUser != 0);
      break;
    }

    default:
      cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 0." << endl;
      break;
    }
  } while (pilihMenuUtama != 0);

  return 0;
}
