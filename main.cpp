#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>

#define CLEAR "cls"

using namespace std;

struct Penduduk
{
  int noKtp, status;
  string nama, golDar;
};

// R/W Files
void readFile(Penduduk penduduk[], int &jml);
void writeFile(Penduduk penduduk[], int jml, string namaFile);

// Main Menu
void addPenduduk(Penduduk penduduk[], int jml);
void cetakPenduduk(Penduduk penduduk[], int jml, int awal = 0);
void searchPenduduk(Penduduk penduduk[], int jml);
void sortPenduduk(Penduduk penduduk[], int jml);
void transaksiPenduduk(Penduduk penduduk[], int jml);

// Search Method
int seqSearch(Penduduk penduduk[], int jml, int input, int searchCode);
int seqSearch(Penduduk penduduk[], int jml, string input, int searchCode);
int binarySearch(Penduduk penduduk[], int awal, int akhir, int input, int searchCode);
int binarySearch(Penduduk penduduk[], int awal, int akhir, string input, int searchCode);

// Sort Method
void bubbleSort(Penduduk penduduk[], int jml, int sortCode);
void selectionSort(Penduduk penduduk[], int jml, int sortCode);
void insertionSort(Penduduk penduduk[], int jml, int sortCode);
void shellSort(Penduduk penduduk[], int jml, int sortedCode);

// Transaction Menu
void updatePenduduk(Penduduk penduduk[], int index, int jml);
void splitPenduduk(Penduduk penduduk[], int jml);

// Sting Manipulation
string replaceSpasi(string str);
string replaceHyphen(string str);

// Misc
void cetakField(Penduduk penduduk[], int jml, int fieldCode);
string statusCode(int kode);
void statusCode();
void showFileName();
void Garis(int length);
void pressAnyKey();

string fileName = "data-penduduk";

int main()
{
  Penduduk penduduk[100];
  int jmlPenduduk = 0;
  bool isExit, repeatMainMenu;
  char inputMenu;

  system(CLEAR);
  do
  {
    repeatMainMenu = 1;

    cout << "[FILE DATA PENDUDUK] \n"
         << "Masukkan Nama File (tanpa .txt): ";
    cin >> fileName;
    system(CLEAR);

    // MAIN MENU
    while (repeatMainMenu)
    {
      // Membaca file
      readFile(penduduk, jmlPenduduk);

      cout << "FILE: " + fileName + ".txt \n\n"
           << "[TUGAS PROJEK ALGO 2022] \n"
           << "[1] Input Data \n"
           << "[2] Tampilkan Data \n"
           << "[3] Searching Data \n"
           << "[4] Sorting Data \n"
           << "[5] Transaksi \n"
           << "[6] Ganti File \n"
           << "[...] Keluar \n"
           << "Pilih > ";
      cin >> inputMenu;
      cout << "\n";

      switch (inputMenu)
      {
      case '1':
        system(CLEAR);
        addPenduduk(penduduk, jmlPenduduk);
        break;

      case '2':
        system(CLEAR);
        showFileName();
        cetakPenduduk(penduduk, jmlPenduduk);
        pressAnyKey();
        break;

      case '3':
        system(CLEAR);
        searchPenduduk(penduduk, jmlPenduduk);
        break;

      case '4':
        system(CLEAR);
        sortPenduduk(penduduk, jmlPenduduk);
        break;

      case '5':
        system(CLEAR);
        transaksiPenduduk(penduduk, jmlPenduduk);
        break;

      case '6':
        repeatMainMenu = 0;
        showFileName();
        break;

      default:
        repeatMainMenu = 0;
        isExit = 1;
        break;
      }
    }
  } while (!isExit);

  cout << "Terima kasih. \n\n";
  pressAnyKey();
  return 0;
}

void readFile(Penduduk penduduk[], int &jml)
{
  string nameOfFile = fileName + ".txt";

  ifstream myFile(nameOfFile);
  jml = 0;

  if (myFile.is_open())
  {
    int i = jml;
    while (!myFile.eof())
    {
      myFile >> penduduk[i].noKtp >> penduduk[i].nama;
      myFile >> penduduk[i].golDar >> penduduk[i].status;
      penduduk[i].nama = replaceHyphen(penduduk[i].nama); // Menghilangkan "-"
      i++;
    }

    jml += i - 1;
    myFile.close();
  }
}

void writeFile(Penduduk penduduk[], int jml, string namaFile)
{
  int i;
  string nameOfFile = namaFile + ".txt";

  for (i = 0; i < jml; i++)
    penduduk[i].nama = replaceSpasi(penduduk[i].nama);

  ofstream myFile(nameOfFile);
  if (myFile.is_open())
  {
    for (i = 0; i < jml; i++)
    {
      // Contoh format file:
      // 123210078 Muhammad_Rafli A 1

      myFile << penduduk[i].noKtp << " "
             << penduduk[i].nama << " "
             << penduduk[i].golDar << " "
             << penduduk[i].status << "\n";
    }
    myFile.close();
  }
  else
    cout << "Gagal membuka file. \n";
}

void addPenduduk(Penduduk penduduk[], int jml)
{
  showFileName();
  cout << "[TAMBAH PENDUDUK] \n";
  cout << "Nomor KTP: ";
  cin >> penduduk[jml].noKtp;

  cout << "Nama: ";
  cin.ignore();
  getline(cin, penduduk[jml].nama);

  cout << "Gol. Darah: ";
  cin >> penduduk[jml].golDar;
  cout << "\n";

  statusCode();
  cout << "Status: ";
  cin >> penduduk[jml].status;

  cout << "Penduduk berhasil ditambahkan. \n\n";
  jml++;

  writeFile(penduduk, jml, fileName); // File di-overwrite oleh struct yang telah ditambahkan
  pressAnyKey();
}

void cetakPenduduk(Penduduk penduduk[], int jml, int awal)
{
  int jmlGaris = 79;

  cout << "[Informasi Penduduk] \n";
  Garis(jmlGaris);
  cout << left
       << "| " << setw(17) << "NIK"
       << "| " << setw(25) << "Nama"
       << "| " << setw(11) << "Gol. Darah"
       << "| " << setw(19) << "Status"
       << "| \n";
  Garis(jmlGaris);

  if (jml > 0)
  {
    for (int i = 0; i < jml; i++)
    {
      cout << left
           << "| " << setw(17) << penduduk[i].noKtp
           << "| " << setw(25) << penduduk[i].nama
           << "| " << setw(11) << penduduk[i].golDar
           << "| " << setw(19) << statusCode(penduduk[i].status);
      cout << "| \n";
    }
  }
  else
  {
    cout << left << "| " << setw(78) << "Penduduk masih kosong!";
    cout << "| \n";
  }

  Garis(jmlGaris);
  cout << "\n";
}

void searchPenduduk(Penduduk penduduk[], int jml)
{
  int searchCode;
  bool isRepeatMenu = 1;
  char inputMenu, inputMethod;
  string strSearchBy, strSearchMethod;

  do
  {
    showFileName();
    cout << "[PENCARIAN DATA PENDUDUK] \n"
         << "[1] NIK \n"
         << "[2] Nama \n"
         << "[3] Gol. Darah \n"
         << "[4] Status \n"
         << "[...] Kembali \n"
         << "Pilih > ";
    cin >> inputMenu;
    system(CLEAR);

    switch (inputMenu)
    {
    case '1':
      searchCode = 1;
      strSearchBy = "No. KTP";
      break;

    case '2':
      searchCode = 2;
      strSearchBy = "Nama";
      break;

    case '3':
      searchCode = 3;
      strSearchBy = "Gol. Darah";
      break;

    case '4':
      searchCode = 4;
      strSearchBy = "Status";
      break;

    default:
      isRepeatMenu = 0;
      break;
    }

    switch (inputMenu)
    {
    case '1' ... '4':
    {
      bool isRepeatSort = 1;
      int inputInt, searchIndex;
      string inputStr;

      cout << "[Pencarian Penduduk Berdasarkan " + strSearchBy + "] \n"
           << "[1] Sequential Search \n"
           << "[2] Binary Search \n"
           << "[...] Kembali \n"
           << "Pilih > ";
      cin >> inputMethod;
      cout << "\n";

      if (isRepeatMenu)
      {
        if (inputMenu == '4')
          statusCode();
        cout << "\n";

        cout << "Masukkan kata kunci: ";
        if (inputMenu == '1' || inputMenu == '4')
          cin >> inputInt;
        else
        {
          cin.ignore();
          getline(cin, inputStr);
        }
        cout << "\n";
      }
      system(CLEAR);

      switch (inputMethod)
      {
      case '1': // Seq. Search
      {
        strSearchMethod = "Sequential Search";

        // Mengecek tipe data dari input
        searchIndex = (inputMenu == '1' || inputMenu == '4')
                          ? seqSearch(penduduk, jml, inputInt, searchCode)
                          : seqSearch(penduduk, jml, inputStr, searchCode);
        break;
      }

      case '2': // Binary Search
      {
        strSearchMethod = "Binary Search";

        // Mengurutkan data terlebih dahulu
        shellSort(penduduk, jml, searchCode);

        // Mengecek tipe data dari input
        searchIndex = (inputMenu == '1' || inputMenu == '4')
                          ? binarySearch(penduduk, 0, jml - 1, inputInt, searchCode)
                          : binarySearch(penduduk, 0, jml - 1, inputStr, searchCode);
        break;
      }

      default:
        isRepeatSort = 0;
        break;
      }

      // Menampilkan Data
      if (isRepeatSort)
      {
        cout << "[Pencarian Penduduk Berdasarkan " + strSearchBy + "] \n"
             << "Metode Pencarian: " << strSearchMethod << "\n\n";
        // << "Kata Kunci: " <<

        if (searchIndex != -1)
          cetakPenduduk(penduduk, searchIndex + 1, searchIndex);
        else
          cout << "Data Tidak ditemukan. \n\n";

        pressAnyKey();
      }
    }
    break;

    default:
      isRepeatMenu = 0;
      break;
    }
  } while (isRepeatMenu);
}

void sortPenduduk(Penduduk penduduk[], int jml)
{
  Penduduk sortedPenduduk[100];
  int sortedCode;
  bool isRepeatMenu = 1;
  char inputMenu, inputSort;
  string strSortedBy, sortMethod;

  do
  {
    showFileName();
    cout << "[PENGURUTAN DATA PENDUDUK] \n"
         << "[1] NIK \n"
         << "[2] Nama \n"
         << "[3] Gol. Darah \n"
         << "[4] Status \n"
         << "[...] Kembali \n"
         << "Pilih > ";
    cin >> inputMenu;
    system(CLEAR);

    switch (inputMenu)
    {
    case '1':
      sortedCode = 1;
      strSortedBy = "No. KTP";
      break;

    case '2':
      sortedCode = 2;
      strSortedBy = "Nama";
      break;

    case '3':
      sortedCode = 3;
      strSortedBy = "Gol. Darah";
      break;

    case '4':
      sortedCode = 4;
      strSortedBy = "Status";
      break;

    default:
      break;
    }

    switch (inputMenu)
    {
    case '1' ... '4':
    {
      bool isRepeatSort = 1;

      do
      {
        // Copy Data
        for (int i = 0; i < jml; i++)
          sortedPenduduk[i] = penduduk[i];

        cout << "[Pengurutan Data Penduduk Berdasarkan " + strSortedBy + "] \n"
             << "[1] Bubble Sort \n"
             << "[2] Selection Sort \n"
             << "[3] Insertion Sort \n"
             << "[4] Shell Sort \n"
             << "[...] Kembali \n"
             << "Pilih > ";
        cin >> inputSort;
        system(CLEAR);
        cout << "[PROSES SORTING] \n";

        switch (inputSort)
        {
        case '1':
          sortMethod = "Bubble Sort";
          bubbleSort(sortedPenduduk, jml, sortedCode);
          break;

        case '2':
          sortMethod = "Selection Sort";
          selectionSort(sortedPenduduk, jml, sortedCode);
          break;

        case '3':
          sortMethod = "Insertion Sort";
          insertionSort(sortedPenduduk, jml, sortedCode);
          break;

        case '4':
          sortMethod = "Shell Sort";
          shellSort(sortedPenduduk, jml, sortedCode);
          break;

        default:
          isRepeatSort = 0;
          break;
        }

        if (isRepeatSort)
        {
          cout << "\n";
          cout << "[Pengurutan Data Penduduk Berdasarkan " + strSortedBy + "] \n"
               << "Metode: " << sortMethod << "\n\n";

          cetakPenduduk(sortedPenduduk, jml);
          pressAnyKey();
        }
      } while (isRepeatSort);
    }
    break;

    default:
      isRepeatMenu = 0;
      break;
    }

  } while (isRepeatMenu);
}

void transaksiPenduduk(Penduduk penduduk[], int jml)
{
  bool isRepeatMenu = 1;
  char inputMenu;

  do
  {
    showFileName();
    cout << "[TRANSAKSI PENDUDUK] \n"
         << "[1] Updating \n"
         << "[2] Splitting \n"
         << "[...] Kembali \n"
         << "Pilih > ";
    cin >> inputMenu;
    system(CLEAR);

    switch (inputMenu)
    {
    case '1':
    {
      int inputNIK, index;

      cetakPenduduk(penduduk, jml);
      cout << "Masukkan NIK > ";
      cin >> inputNIK;

      // Melakukan pencarian berdasarkan NIK untk mendapatkan index
      index = seqSearch(penduduk, jml, inputNIK, 1);

      if (index != -1)
      {
        system(CLEAR);
        updatePenduduk(penduduk, index, jml);
      }
      else
      {
        cout << "Data tidak ditemukan \n\n";
        pressAnyKey();
      }
      break;
    }

    case '2':
      splitPenduduk(penduduk, jml);
      break;

    default:
      isRepeatMenu = 0;
      break;
    }
  } while (isRepeatMenu);
}

int seqSearch(Penduduk penduduk[], int jml, int input, int searchCode)
{
  if (searchCode == 4)
  {
    for (int i = 0; i < jml; i++)
      if (input == penduduk[i].status)
        return i;
  }
  else
    for (int i = 0; i < jml; i++)
      if (input == penduduk[i].noKtp)
        return i;

  return -1;
}

int seqSearch(Penduduk penduduk[], int jml, string input, int searchCode)
{
  if (searchCode == 3)
  {
    for (int i = 0; i < jml; i++)
      if (input == penduduk[i].golDar)
        return i;
  }
  else
    for (int i = 0; i < jml; i++)
      if (input == penduduk[i].nama)
        return i;

  return -1;
}

int binarySearch(Penduduk penduduk[], int awal, int akhir, int input, int searchCode)
{
  int tengah = (awal + akhir) / 2;

  if (awal <= akhir)
  {
    if (searchCode == 4)
    {
      /* Jika index awal <= index akhir, maka lakukan pencarian,
         jika tidak maka pencarian tidak ditemukan. */

      /* - Jika input = nilai tengah, maka fungsi mengembalikan nilai tengah.
         - Jika input berada di sisi kiri nilai tengah,
           maka lakukan pemanggilan fungsi lagi (rekursif) dengan nilai tengah-1 sebagai parameter akhir
         - Jika input berada di sisi kanan nilai tengah,
           maka lakukan pemanggilan fungsi lagi (rekursif) dengan nilai tengah+1 sebagai parameter awal
      */
      return (input == penduduk[tengah].status) ? tengah
             : (input < penduduk[tengah].status)
                 ? binarySearch(penduduk, awal, tengah - 1, input, searchCode)
                 : binarySearch(penduduk, tengah + 1, akhir, input, searchCode);
    }

    else
    {
      return (input == penduduk[tengah].noKtp) ? tengah
             : (input < penduduk[tengah].noKtp)
                 ? binarySearch(penduduk, awal, tengah - 1, input, searchCode)
                 : binarySearch(penduduk, tengah + 1, akhir, input, searchCode);
    }
  }

  return -1;
}

int binarySearch(Penduduk penduduk[], int awal, int akhir, string input, int searchCode)
{
  int tengah = (awal + akhir) / 2;

  if (awal <= akhir)
  {
    if (searchCode == 3)
    {
      return (input == penduduk[tengah].golDar) ? tengah
             : (input < penduduk[tengah].golDar)
                 ? binarySearch(penduduk, awal, tengah - 1, input, searchCode)
                 : binarySearch(penduduk, tengah + 1, akhir, input, searchCode);
    }

    else
    {
      return (input == penduduk[tengah].nama) ? tengah
             : (input < penduduk[tengah].nama)
                 ? binarySearch(penduduk, awal, tengah - 1, input, searchCode)
                 : binarySearch(penduduk, tengah + 1, akhir, input, searchCode);
    }
  }

  return -1;
}

void bubbleSort(Penduduk penduduk[], int jml, int sortedCode)
{
  Penduduk tempStruct;
  int i, j;

  // Sort by Nama
  if (sortedCode == 2)
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        cetakField(penduduk, jml, 2);
        if (penduduk[j].nama > penduduk[j + 1].nama)
        {
          // Menukar elemen
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
    cetakField(penduduk, jml, 2);
  }

  // Sort by Goldar
  else if (sortedCode == 3)
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        cetakField(penduduk, jml, 3);
        if (penduduk[j].golDar > penduduk[j + 1].golDar)
        {
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
    cetakField(penduduk, jml, 3);
  }

  // Sort by Status
  else if (sortedCode == 4)
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        cetakField(penduduk, jml, 4);
        if (penduduk[j].status > penduduk[j + 1].status)
        {
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
    cetakField(penduduk, jml, 4);
  }

  // Sort by NIK
  else
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        cetakField(penduduk, jml, 1);
        if (penduduk[j].noKtp > penduduk[j + 1].noKtp)
        {
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
    cetakField(penduduk, jml, 1);
  }
}

void selectionSort(Penduduk penduduk[], int jml, int sortedCode)
{
  Penduduk tempStruct;
  int i, j, min_idx;

  // Sort by Nama
  if (sortedCode == 2)
  {
    // One by one move boundary of unsorted subarray
    for (i = 0; i < jml - 1; i++)
    {
      // Find the minimum element in unsorted array
      min_idx = i;
      for (j = i + 1; j < jml; j++)
        if (penduduk[j].nama < penduduk[min_idx].nama)
          min_idx = j;

      cetakField(penduduk, jml, 2);
      // Menukar elemen
      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
    cetakField(penduduk, jml, 2);
  }

  // Sort by Gol. Darah
  else if (sortedCode == 3)
  {
    for (i = 0; i < jml - 1; i++)
    {
      min_idx = i;
      for (j = i + 1; j < jml; j++)
        if (penduduk[j].golDar < penduduk[min_idx].golDar)
          min_idx = j;

      cetakField(penduduk, jml, 3);
      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
    cetakField(penduduk, jml, 3);
  }

  // Sort by Status
  else if (sortedCode == 4)
  {
    for (i = 0; i < jml - 1; i++)
    {
      min_idx = i;
      for (j = i + 1; j < jml; j++)
        if (penduduk[j].status < penduduk[min_idx].status)
          min_idx = j;

      cetakField(penduduk, jml, 4);
      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
    cetakField(penduduk, jml, 4);
  }

  // Sort by NIK
  else
  {
    for (i = 0; i < jml - 1; i++)
    {
      min_idx = i;
      for (j = i + 1; j < jml; j++)
        if (penduduk[j].noKtp < penduduk[min_idx].noKtp)
          min_idx = j;

      cetakField(penduduk, jml, 1);
      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
    cetakField(penduduk, jml, 1);
  }
}

void insertionSort(Penduduk penduduk[], int jml, int sortedCode)
{
  Penduduk key, tempStruct;
  int i, j;

  // Sort by Nama
  if (sortedCode == 2)
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      /* Bandingkan key sama elemen di kirinya. Kalo key lebih kecil,
         tuker sampe key lebih besar dari elemen di kirinya
         atau mentok paling ujung kiri */
      while (j >= 0)
      {
        if (key.nama < penduduk[j].nama)
        {
          cetakField(penduduk, jml, 2);

          // Menukar elemen
          tempStruct = penduduk[j + 1];
          penduduk[j + 1] = penduduk[j];
          penduduk[j] = tempStruct;
          j--;
        }
        else
          break;
      }
      penduduk[j + 1] = key;
    }
    cetakField(penduduk, jml, 2);
  }

  // Sort by Goldar
  else if (sortedCode == 3)
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      while (j >= 0)
      {
        if (key.golDar < penduduk[j].golDar)
        {
          cetakField(penduduk, jml, 3);
          tempStruct = penduduk[j + 1];
          penduduk[j + 1] = penduduk[j];
          penduduk[j] = tempStruct;
          j--;
        }
        else
          break;
      }
      penduduk[j + 1] = key;
    }
    cetakField(penduduk, jml, 3);
  }

  // Sort by Status
  else if (sortedCode == 4)
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      while (penduduk[j].status > key.status && j >= 0)
      {
        cetakField(penduduk, jml, 4);
        tempStruct = penduduk[j + 1];
        penduduk[j + 1] = penduduk[j];
        penduduk[j] = tempStruct;
        j--;
      }
      penduduk[j + 1] = key;
    }
    cetakField(penduduk, jml, 4);
  }

  // Sort by No. KTP
  else
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      while (penduduk[j].noKtp > key.noKtp && j >= 0)
      {
        cetakField(penduduk, jml, 1);
        tempStruct = penduduk[j + 1];
        penduduk[j + 1] = penduduk[j];
        penduduk[j] = tempStruct;
        j--;
      }
      penduduk[j + 1] = key;
    }
    cetakField(penduduk, jml, 1);
  }
}

void shellSort(Penduduk penduduk[], int jml, int sortedCode)
{
  // Sort by Nama
  if (sortedCode == 2)
  {
    // Start with a big gap, then reduce the gap
    for (int gap = jml / 2; gap > 0; gap /= 2)
    {

      // Do a gapped insertion sort for this gap size.
      // The first gap elements a[0..gap-1] are already in gapped order
      // keep adding one more element until the entire array is
      // gap sorted
      for (int i = gap; i < jml; i += 1)
      {
        // add a[i] to the elements that have been gap sorted
        // save a[i] in temp and make a hole at position i
        Penduduk temp = penduduk[i];
        int j;

        cetakField(penduduk, jml, 2);

        // shift earlier gap-sorted elements up until the correct
        // location for a[i] is found
        for (j = i; j >= gap && penduduk[j - gap].nama > temp.nama; j -= gap)
          penduduk[j] = penduduk[j - gap];

        //  put temp (the original a[i]) in its correct location
        penduduk[j] = temp;
      }
    }
    cetakField(penduduk, jml, 2);
  }

  // Sort by Gol. Darah
  else if (sortedCode == 3)
  {
    for (int gap = jml / 2; gap > 0; gap /= 2)
    {
      for (int i = gap; i < jml; i += 1)
      {
        Penduduk temp = penduduk[i];
        int j;

        cetakField(penduduk, jml, 3);
        for (j = i; j >= gap && penduduk[j - gap].golDar > temp.golDar; j -= gap)
          penduduk[j] = penduduk[j - gap];
        penduduk[j] = temp;
      }
    }
    cetakField(penduduk, jml, 3);
  }

  // Sort by Status
  else if (sortedCode == 4)
  {
    for (int gap = jml / 2; gap > 0; gap /= 2)
    {
      for (int i = gap; i < jml; i += 1)
      {
        Penduduk temp = penduduk[i];
        int j;

        cetakField(penduduk, jml, 4);
        for (j = i; j >= gap && penduduk[j - gap].status > temp.status; j -= gap)
          penduduk[j] = penduduk[j - gap];
        penduduk[j] = temp;
      }
    }
    cetakField(penduduk, jml, 4);
  }

  // Sort by NIK
  else
  {
    for (int gap = jml / 2; gap > 0; gap /= 2)
    {
      for (int i = gap; i < jml; i += 1)
      {
        Penduduk temp = penduduk[i];
        int j;

        cetakField(penduduk, jml, 1);
        for (j = i; j >= gap && penduduk[j - gap].noKtp > temp.noKtp; j -= gap)
          penduduk[j] = penduduk[j - gap];
        penduduk[j] = temp;
      }
    }
    cetakField(penduduk, jml, 1);
  }
}

void updatePenduduk(Penduduk penduduk[], int index, int jml)
{
  Penduduk updatedPenduduk[100];
  bool isRepeat = 1;
  char inputMenu;
  int NIK, status;
  string nama, golDar, inputFileName;

  // Copy Data
  for (int i = 0; i < jml; i++)
    updatedPenduduk[i] = penduduk[i];

  do
  {
    showFileName();
    cetakPenduduk(penduduk, index + 1, index);

    cout << "[UPDATING DATA PENDUDUK] \n"
         << "Pilih yang ingin diubah: \n"
         << "[1] NIK \n"
         << "[2] Nama \n"
         << "[3] Gol. Darah \n"
         << "[4] Status \n"
         << "[...] Kembali \n"
         << "Pilih > ";
    cin >> inputMenu;
    cout << "\n";

    switch (inputMenu)
    {
    case '1':
      cout << "NIK lama: " << penduduk[index].noKtp << "\n"
           << "NIK baru: ";
      cin >> NIK;
      updatedPenduduk[index].noKtp = NIK;
      break;

    case '2':
      cout << "Nama lama: " << penduduk[index].nama << "\n"
           << "Nama baru: ";
      cin.ignore();
      getline(cin, nama);
      updatedPenduduk[index].nama = nama;
      break;

    case '3':
      cout << "Gol. Darah lama: " << penduduk[index].golDar << "\n"
           << "Gol. Darah baru: ";
      cin >> golDar;
      updatedPenduduk[index].golDar = golDar;
      break;

    case '4':
      statusCode();
      cout << "\n";

      cout << "Status lama: " << penduduk[index].status << "\n"
           << "Status baru: ";
      cin >> status;
      updatedPenduduk[index].status = status;
      break;

    default:
      system(CLEAR);
      isRepeat = 0;
      break;
    }

    if (isRepeat)
    {
      cout << "\n";
      cout << "Masukkan Nama File (tanpa .txt): ";
      cin >> inputFileName;

      writeFile(updatedPenduduk, jml, inputFileName);

      cout << "Berhasil Mengupdate Data ke file " + inputFileName << ".txt! \n\n";
      pressAnyKey();
    }
  } while (isRepeat);
}

void splitPenduduk(Penduduk penduduk[], int jml)
{
  Penduduk firstSplit[100], secondSplit[100];
  int j = 0, k = 0;
  int jmlPertama = jml / 2, jmlKedua = jml - jmlPertama;
  string inputFileName1, inputFileName2;

  for (int i = 0; i < jml; i++)
  {
    if (i < jml / 2)
    {
      firstSplit[j] = penduduk[i];
      j++;
    }
    else
    {
      secondSplit[k] = penduduk[i];
      k++;
    }
  }

  cout << "[SPLITTING] \n";
  showFileName();
  cetakPenduduk(penduduk, jml);

  cout << "Masukkan Nama File ke-1 (.txt) > ";
  cin >> inputFileName1;
  cout << "Masukkan Nama File ke-2 (.txt) > ";
  cin >> inputFileName2;
  cout << "\n";

  writeFile(firstSplit, jmlPertama, inputFileName1);
  writeFile(secondSplit, jmlKedua, inputFileName2);

  cout << "File " + fileName + ".txt berhasil dipecah menjadi: \n"
       << "File ke-1: " + inputFileName1 + ".txt \n"
       << "File ke-2: " + inputFileName2 + ".txt \n\n";
  pressAnyKey();
}

string replaceSpasi(string str)
{
  for (int i = 0; i < str.length(); i++)
    if (str[i] == ' ')
      str[i] = '-';

  return str;
}

string replaceHyphen(string str)
{
  for (int i = 0; i < str.length(); i++)
    if (str[i] == '-')
      str[i] = ' ';

  return str;
}

void cetakField(Penduduk penduduk[], int jml, int fieldCode)
{
  if (fieldCode == 1)
  {
    for (int i = 0; i < jml; i++)
    {
      cout << penduduk[i].noKtp;
      cout << (i < jml - 1 ? ", " : "");
    }
  }

  else if (fieldCode == 2)
  {
    for (int i = 0; i < jml; i++)
    {
      cout << penduduk[i].nama;
      cout << (i < jml - 1 ? ", " : "");
    }
  }

  else if (fieldCode == 3)
  {
    for (int i = 0; i < jml; i++)
    {
      cout << penduduk[i].golDar;
      cout << (i < jml - 1 ? ", " : "");
    }
  }

  else
  {
    for (int i = 0; i < jml; i++)
    {
      cout << statusCode(penduduk[i].status);
      cout << (i < jml - 1 ? ", " : "");
    }
  }
  cout << "\n";
}

string statusCode(int kode)
{

  if (kode == 1)
    return "Belum Kawin (1)";
  else if (kode == 2)
    return "Kawin (2)";
  else if (kode == 3)
    return "Cerai Hidup (3)";
  else if (kode == 4)
    return "Cerai Mati (4)";
  else
    return "Lain-lain";
}

void statusCode()
{
  cout << "[STATUS PERKAWINAN] \n"
       << "[1]: Belum Kawin \n"
       << "[2]: Kawin \n"
       << "[3]: Cerai Hidup \n"
       << "[4]: Cerai Mati \n"
       << "[...] Lain-lain \n";
}

void showFileName()
{
  cout << "FILE: " + fileName + ".txt \n\n";
}

void Garis(int length)
{
  cout << "+";
  for (int i = 0; i < length; i++)
    cout << "-";
  cout << "+ \n";
}

void pressAnyKey()
{
  cout << "[Tekan tombol apa saja untuk melanjutkan.]";
  getch();
  system(CLEAR);
}
