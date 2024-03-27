#include <iostream>
using namespace std;

struct Supir
{
  string ID;
  string nama;
  struct Date
  {
    int tglDay, tglMonth, tglYear;
  } date;
  char kelamin;
  string alamat;

  Supir *next;

  Supir *prev;

} dataSupir;

struct Order
{
  string IDorder;
  string nama;
  string supir;
  string platNomor;
  string tujuan;

  Order *next;
} orderan;

struct Mobil
{
  string platNomor;
  string jenisMobil;
  string brandMobil;

  Mobil *next;
  Mobil *prev;
};

Supir *head, *tail, *newNode, *temp, *cur, *del;
Order *head2, *tail2, *newNode2, *cur2, *del2;
Mobil *head3, *tail3, *newNode3, *cur3, *del3;

string generateID(string nama, int tglDay, int tglMonth, int tglYear, char kelamin)
{
  string id;

  // digit 1 & 2
  int digit1 = nama[0] - 'A' + 1;
  int digit2 = nama[nama.length() - 1] - 'A' + 1;
  int duaDigit = abs(digit1 - digit2);

  if (duaDigit < 10)
  {
    string twoDigit = to_string(duaDigit);
    id = "0" + twoDigit;
  }
  else
  {
    id = to_string(duaDigit);
  }

  // digit 3
  string digit3 = (kelamin == 'L') ? "1" : "0";
  id = id + digit3;

  // digit 4
  int digit4 = (tglDay % 10 + tglMonth % 10 + tglYear % 10) % 9;
  id = id + to_string(digit4);

  // digit 5
  if (id.length() < 5)
  {
    id = id + "0";
  }
  return id;
}

string generateIDorder(string platNomer, string nama, string tujuan, Supir supir)
{
  string id;
  // digit 1 & 2
  int digit1 = platNomer[0] - 'A' + 1;

  if (digit1 < 10)
  {
    string strDigit1 = to_string(digit1);
    id = "0" + strDigit1;
  }
  else
  {
    id = to_string(digit1);
  }

  // digit 3,4,5,6,7
  id += supir.ID;

  // //digit 8 & 9
  int digit8 = tujuan[tujuan.length() - 2] - 'a' + 1;
  int digit9 = tujuan[tujuan.length() - 1] - 'a' + 1;
  int sumDigits = digit8 + digit9;
  id += to_string(sumDigits);

  // digit 10
  int result = 0;
  for (int i = 0; i < nama.length(); i++)
  {
    char uppercaseChar = toupper(nama[i]);
    int abjad = uppercaseChar - 'A' + 1;
    result += abjad;
  }
  string digit10 = to_string(result);
  if (digit10.length() < 2)
  {
    id += digit10;
  }
  else
  {
    id += digit10[digit10.length() - 1];
  }
  return id;
}

void addDataSupir(string nama, int tglDay, int tglMonth, int tglYear, char kelamin, string alamat)
{
  newNode = new Supir();
  newNode->ID = generateID(nama, tglDay, tglMonth, tglYear, kelamin);
  newNode->nama = nama;
  newNode->date.tglDay = tglDay;
  newNode->date.tglMonth = tglMonth;
  newNode->date.tglYear = tglYear;
  newNode->kelamin = kelamin;
  newNode->alamat = alamat;

  if (head == NULL)
  {
    head = newNode;
    tail = newNode;
  }
  else
  {
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
    tail = newNode;
  }
}
void buatOrderan(string ID, string platNomor, string nama, string tujuan, string supir)
{
  newNode2 = new Order();
  newNode2->IDorder = ID;
  newNode2->nama = nama;
  newNode2->supir = supir;
  newNode2->tujuan = tujuan;
  newNode2->platNomor = platNomor;
  newNode2->next = nullptr;

  if (head2 == nullptr)
  {
    head2 = newNode2;
    tail2 = newNode2;
  }
  else
  {
    // Jika queue tidak kosong, tambahkan newNode2 ke belakang dan perbarui
    tail2->next = newNode2;
    tail2 = newNode2;
  }
  // hapus stack
  if (head3 == tail3)
  {
    head3->next = NULL;
    tail3->prev = NULL;
    delete head3;
    head3 = NULL;
    tail3 = NULL;
  }
  else
  {
    del3 = tail3;
    tail3 = tail3->prev;
    tail3->next = NULL;
    delete del3;
  }
}

void hapusDataSupir(string ID)
{

  if (head == nullptr)
  {
    cout << "Linked list kosong." << endl;
    return;
  }

  Supir *del = head;
  Supir *prev = nullptr;

  while (del != nullptr && del->ID != ID)
  {
    prev = del;
    del = del->next;
    if (del == head)
    {
      cout << "Tidak ada simpul dengan ID " << ID << " di dalam linked list." << endl;
      return;
    }
  }

  if (del != nullptr && del->ID == ID)
  {
    if (del == head)
    {
      head = head->next;

      // Menghubungkan simpul terakhir dengan simpul baru yang menjadi head
      tail->next = head;
      head->prev = tail;
      if (head == del)
      {
        head = nullptr;
        tail = nullptr;
      }
    }
    else
    {
      prev->next = del->next;
      del->next->prev = prev;
      if (del == tail)
      {
        tail = prev;       // Atur tail ke simpul sebelumnya
        tail->next = head; // Hubungkan simpul terakhir ke head
        head->prev = tail; // Hubungkan head ke simpul terakhir
      }
    }

    delete del; // Menghapus simpul dari memori

    cout << "Simpul dengan ID " << ID << " berhasil dihapus." << endl;
  }
}
int hitungJumlahData()
{
  int jumlah = 0;
  Supir *cur = head;

  while (cur != nullptr)
  {
    jumlah++;        // Tambahkan satu ke jumlah setiap kali Anda menemukan simpul
    cur = cur->next; // Pindah ke simpul berikutnya
    if (cur == head)
    {
      break; // Jika kembali ke simpul pertama, hentikan iterasi
    }
  }
  return jumlah; // Kembalikan jumlah total
}
void ubahDataSupir(string ID)
{
  cur = head;
  if (cur == NULL)
  {
    cout << "Data supir belum ada" << endl;
  }
  else
  {

    while (cur != NULL)
    {
      if (cur->ID == ID)
      {
        int pilih;

        cout << " - Mengubah supir dengan Id" << ID << " - " << endl;
        cout << "1. Ubah Nama" << endl;
        cout << "2. Ubah Kelamin" << endl;
        cout << "3. Ubah Alamat" << endl;
        cout << "4. Ubah Tgl Lahir" << endl;
        cout << ">";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
          cout << "Masukan nama baru : ";
          cin.ignore();
          getline(cin, cur->nama);
          break;
        case 2:
          cout << "Masukan jenis kelamin baru L/P : ";
          cin >> cur->kelamin;
          break;
        case 3:
          cout << "Masukan Alamat baru : ";
          cin >> cur->alamat;
          break;
        case 4:
          cout << "Masukan tanggal lahir baru DD/MM/YYYY : ";
          cin >> cur->date.tglDay >> cur->date.tglMonth >> cur->date.tglYear;

        default:
          cout << "Pilihan tidak valid" << endl;
          break;
        }
        cur->ID = generateID(cur->nama, cur->date.tglDay, cur->date.tglMonth, cur->date.tglYear, cur->kelamin);
        break;
      }
      else
      {
        cout << "ID yang anda masukan tidak valid" << endl;
      }
      cur = cur->next;
    }
  }
}
void tampilkanOrderan()
{
  if (head2 == nullptr)
  {
    cout << "\nTidak ada pesanan!!!" << endl;
    return;
  }
  else
  {
    cout << "\nDaftar pesanan :" << endl;
    cout << "---------------------------" << endl;
    cout << "ID              : " << head2->IDorder << endl;
    cout << "Nama Pelanggan  : " << head2->nama << endl;
    cout << "Supir           : " << head2->supir << endl;
    cout << "Plat nomor      : " << head2->platNomor << endl;
    cout << "Tujuan          : " << head2->tujuan << endl;
    cout << "---------------------------" << endl;
  }
}
void orderSuccess(string ID)
{
  cur2 = head2;
  while (cur2 != nullptr && cur2->IDorder != ID)
  {
    cur2 = cur2->next;
    if (cur2 == head2)
    {
      cout << "Pesanan dengan ID " << ID << " tidak ditemukan" << endl;
      return;
    }
  }
  if (cur2 != nullptr && cur2->IDorder == ID)
  {
    system("cls");
    cout << "\nOrder telah dilakukan !!!" << endl;
    cout << "---------------------------------" << endl;
    cout << "ID orderan      : " << cur2->IDorder << endl;
    cout << "Nama Pelanggan  : " << cur2->nama << endl;
    cout << "Supir           : " << cur2->supir << endl;
    cout << "Tujuan          : " << cur2->tujuan << endl;
    cout << "Plat nomor      : " << cur2->platNomor << endl;
    cout << "---------------------------------" << endl;
  }
  else
  {
    cout << "Pesanan dengan ID " << ID << " tidak ditemukan" << endl;
  }
}
void addUnitMobil()
{
  newNode3 = new Mobil();
  cout << "\nMasukan plat nomor mobil : ";
  cin.ignore();
  getline(cin, newNode3->platNomor);
  cout << "Masukan Jenis mobil : ";
  cin >> newNode3->jenisMobil;
  cout << "Masukan brand mobil : ";
  cin >> newNode3->brandMobil;

  if (head3 == nullptr)
  {
    head3 = newNode3;
    tail3 = newNode3;
    newNode3->next = nullptr;
  }
  else
  {
    tail3->next = newNode3;
    newNode3->prev = tail3;
    tail3 = newNode3;
    tail3->next = nullptr;
  }

  cout << "Data berhasil ditambahkan!!" << endl;
}

void tampilDataSupir(Supir *cur)
{
  // cout << "              Jumblah Data : " << hitungJumlahData() << endl;
  if (cur == NULL)
  {
    cout << "\t   data supir belum ada!\n"
         << endl;
  }
  else
  {

    cout << "-------------------------------------------" << endl;
    cout << "| Nama          : " << cur->nama << endl;
    cout << "| ID            : " << cur->ID << endl;
    cout << "| Tanggal lahir : " << cur->date.tglDay << "-" << cur->date.tglMonth << "-" << cur->date.tglYear << endl;
    cout << "| Jenis kelamin : " << cur->kelamin << endl;
    cout << "| Alamat        : " << cur->alamat << endl;
    cout << "-------------------------------------------" << endl;
  }
}
void tampil()
{
  Supir *cur = head;
  if (!cur)
  {
    cout << "Tidak ada supir yang terdaftar." << endl;
    return;
  }
  else
  {
    tampilDataSupir(cur);
  }
}
void cariDataSupir(string ID)
{
  cur = head;
  while (cur != nullptr && cur->ID != ID)
  {
    cur = cur->next;
    if (cur == head)
    {
      cout << "Tidak ada data dengan ID " << ID << endl;
      return;
    }
  }

  if (cur != nullptr && cur->ID == ID)
  {
    cout << "Data dengan ID " << ID << " ditemukan." << endl;
    tampilDataSupir(cur);
  }
  else
  {
    cout << "Tidak ada data dengan ID " << ID << endl;
  }
}

void nextDataSupir()
{
  if (!head)
  {
    cout << "Tidak ada supir yang terdaftar." << endl;
  }
  else if (head == tail)
  {
    tampilDataSupir(head);
  }
  else
  {
    head = head->next;
    tail = tail->next;
    tampilDataSupir(head);
  }
}

void prevDataSupir()
{
  if (!head)
  {
    cout << "Tidak ada supir yang terdaftar." << endl;
  }
  else if (head == tail)
  {
    tampilDataSupir(head);
  }
  else
  {
    head = head->prev;
    tail = tail->prev;
    tampilDataSupir(head);
  }
}
void accept()
{

  if (head2 == nullptr)
  {
    return;
  }
  else
  {
    // Menghapus stack
    if (tail3 == head3)
    {
      del3 = tail3;
      delete del3;
      head3 = nullptr;
      tail3 = nullptr;
    }
    else if (tail3->prev == head3)
    {
      del3 = tail3;
      delete del3;
      tail3 = head3;
      head3 = tail3;
    }
    else
    {

      del3 = tail3;
      tail3 = tail3->prev;
      delete del3;
    }

    // Menghapus queue
    del2 = head2;
    head2 = head2->next;
    cout << "\nPesanan dengan Id " << del2->IDorder << " telah diproses !!" << endl;
    delete del2;
  }
}
void reject()
{

  if (head2 == nullptr)
  {
    return;
  }
  else
  {
    del2 = head2;
    head2 = head2->next;
    cout << "\nPesanan dengan Id " << del2->IDorder << " dibatalkan !!" << endl;
    delete del2;
  }
}

void prosesOrderan()
{
  if (head2 == nullptr)
  {
    cout << "\nTidak ada pesanan!!!" << endl;
    return;
  }
  int pilihOrderan;
  do
  {
    tampilkanOrderan();
    cout << "1. Accept " << endl;
    cout << "2. Reject " << endl;
    cout << "0. Exit " << endl;
    cin >> pilihOrderan;
    switch (pilihOrderan)
    {
    case 1:
      accept();
      break;
    case 2:
      reject();
      break;
    case 0:
      break;
    default:
      cout << "Pilihan anda tidak valid" << endl;
      break;
    }
  } while (pilihOrderan != 0);
}

int main()
{
  addDataSupir("muhammad ilham", 24, 06, 2003, 'L', "jember");
  addDataSupir("joko anwar ", 12, 02, 2008, 'P', "jakarta");

  int pilihMenuUtama;
  do
  {
    system("cls");
    cout << "\n-------------------------------------------" << endl;
    cout << "|------------   Sugeng Taxi   ------------|" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "1.Masuk Sebagai Admin" << endl;
    cout << "2.Masuk Sebagai User" << endl;
    cout << "> : ";
    cin >> pilihMenuUtama;
    cout << "\n";
    switch (pilihMenuUtama)
    {
    case 1:
      int pilihMenuAdmin;
      do
      {
        cout << "\n==========================" << endl;
        cout << "===== Dashbord Admin =====" << endl;
        cout << "==========================" << endl;
        cout << "1. Cari Data Supir" << endl;
        cout << "2. Menghapus Data Supir" << endl;
        cout << "3. Mengubah Data Supir" << endl;
        cout << "4. Tambah Data Supir" << endl;
        cout << "5. Proses Orderan" << endl;
        cout << "6. Tambah Unit Mobil" << endl;
        cout << "0. Exit" << endl;
        cout << "> : ";
        cin >> pilihMenuAdmin;

        switch (pilihMenuAdmin)
        {
        case 1:
          cout << "Masukan ID Supir yang ingin dicari : ";
          cin >> dataSupir.ID;
          cariDataSupir(dataSupir.ID);
          break;
        case 2:
          cout << "Masukan ID Supir yang ingin dihapus : ";
          cin >> dataSupir.ID;
          hapusDataSupir(dataSupir.ID);
          break;
        case 3:
          cout << "Masukan ID Supir yang ingin diubah : ";
          cin >> dataSupir.ID;
          ubahDataSupir(dataSupir.ID);
          break;
        case 4:
          cout << "\n--------------------------" << endl;
          cout << "Masukan Data Supir : " << endl;
          cout << "--------------------------" << endl;
          cout << "Masukan Nama : ";
          cin.ignore();
          getline(cin, dataSupir.nama);
          cout << "Masukan Tanggal Lahir DD/MM/YYYY : ";
          cin >> dataSupir.date.tglDay >> dataSupir.date.tglMonth >> dataSupir.date.tglYear;
          cout << "Masukan Jenis Kelamin (L/P) : ";
          cin >> dataSupir.kelamin;
          cout << "Masukan Alamat : ";
          cin >> dataSupir.alamat;
          dataSupir.ID = generateID(dataSupir.nama, dataSupir.date.tglDay, dataSupir.date.tglMonth, dataSupir.date.tglYear, dataSupir.kelamin);
          addDataSupir(dataSupir.nama, dataSupir.date.tglDay, dataSupir.date.tglMonth, dataSupir.date.tglYear, dataSupir.kelamin, dataSupir.alamat);
          break;
        case 5:
          prosesOrderan();
          break;
        case 6:
          char pilih;
          do
          {
            addUnitMobil();
            cout << "Ingin menambahkan unit mobil lagi? (y/n) :";
            cin >> pilih;
            switch (pilih)
            {
            case 'y':
              break;
            case 'n':
              break;
            default:
              cout << "Pilihan yang anda masukan salah" << endl;
              break;
            }
          } while (pilih == 'y');

          break;
        case 0:
          break;
        default:
          cout << "Pilihan yang anda masukan salah" << endl;
        }
      } while (pilihMenuAdmin != 0);
      break;
    case 2:
      int pilihMenuUser;
      do
      {
        cout << "\n-------------------------------------------" << endl;
        cout << "|------------- Dashbord User -------------|" << endl;
        cout << "-------------------------------------------" << endl;
        tampil();
        cout << "1. Next" << endl;
        cout << "2. Previous" << endl;
        cout << "3. Order" << endl;
        cout << "0. Exit" << endl;
        cout << "> : ";
        cin >> pilihMenuUser;
        switch (pilihMenuUser)
        {
        case 1:
          nextDataSupir();
          break;
        case 2:
          prevDataSupir();
          break;
        case 3:
          if (head == NULL)
          {
            cout << "Tidak ada supir yang terdaftar." << endl;
          }

          if (head3 == NULL)
          {
            cout << "\n\nUnit mobil sedang kosong harap menunggu...." << endl;
          }
          else
          {

            char repeatOrder;
            do
            {
              cout << "Masukan nama pelanggan : ";
              cin.ignore();
              getline(cin, orderan.nama);
              cout << "Masukan tujuan         : ";
              cin >> orderan.tujuan;
              dataSupir.ID = head->ID;
              dataSupir.nama = head->nama;
              orderan.platNomor = tail3->platNomor;
              orderan.IDorder = generateIDorder(orderan.platNomor, orderan.nama, orderan.tujuan, dataSupir);
              buatOrderan(orderan.IDorder, orderan.platNomor, orderan.nama, orderan.tujuan, dataSupir.nama);
              orderSuccess(orderan.IDorder);

              cout << "Apakah anda ingin membuat pesanan lagi (y/n)  : ";
              cin >> repeatOrder;
              if (repeatOrder == 'y')
              {
                if (head3 == NULL)
                {
                  cout << "\n\nUnit mobil sedang kosong harap menunggu...." << endl;
                  break;
                }
              }
            } while (repeatOrder != 'n');
            break;
          }

        default:
          break;
        }
      } while (pilihMenuUser != 0);
      break;
    case 0:
      break;
    default:
      cout << "Pilihan yang anda masukan salah" << endl;
    }
  } while (pilihMenuUtama != 0);
  return 0;
}