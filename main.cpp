#include <iostream>
#include <fstream>
#include <conio.h>

#define CLEAR "cls"

using namespace std;

struct Penduduk
{
  int noKtp, status;
  char golDar;
  string nama;
};

void readFile(Penduduk penduduk[], int &jml);
void writeFile(Penduduk penduduk[], int jml);

void addPenduduk(Penduduk penduduk[], int jml);
void cetakPenduduk(Penduduk penduduk[], int jml, int awal = 0);
void sortingPenduduk(Penduduk penduduk[], int jml);

void bubbleSort(Penduduk penduduk[], int jml, int sortCode);
void selectionSort(Penduduk penduduk[], int jml, int sortCode);
void insertionSort(Penduduk penduduk[], int jml, int sortCode);
void shellSort(Penduduk penduduk[], int jml, int sortedCode);

string replaceSpasi(string str);
string replaceHyphen(string str);

string statusCode(int kode);
void statusCode();
void pressAnyKey();

int main()
{
  Penduduk penduduk[100];
  int jmlPenduduk = 0;
  bool isExit;
  char inputMenu;

  do
  {
    readFile(penduduk, jmlPenduduk);

    cout << "TUGAS PROJEK ALGO 2022 \n"
         << "[1] Input Data \n"
         << "[2] Tampilkan Data \n"
         << "[3] Searching Data \n"
         << "[4] Sorting Data \n"
         << "[5] Transaksi \n"
         << "[...] Keluar \n"
         << "Pilih > ";
    cin >> inputMenu;

    system(CLEAR);

    switch (inputMenu)
    {
    case '1':
      addPenduduk(penduduk, jmlPenduduk);
      break;

    case '2':
      cetakPenduduk(penduduk, jmlPenduduk);
      pressAnyKey();
      break;

    case '4':
      sortingPenduduk(penduduk, jmlPenduduk);
      break;

    default:
      isExit = 1;
      break;
    }

  } while (!isExit);

  cout << "Terima kasih.";
  return 0;
}

void readFile(Penduduk penduduk[], int &jml)
{
  string fileName = "data-penduduk.txt";

  ifstream myFile(fileName);
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
  else
    cout << "Gagal membuka file. \n";
}

void writeFile(Penduduk penduduk[], int jml)
{
  int i;
  string fileName = "data-penduduk.txt";

  for (i = 0; i < jml; i++)
    penduduk[i].nama = replaceSpasi(penduduk[i].nama);

  ofstream myFile(fileName);
  if (myFile.is_open())
  {
    for (i = 0; i < jml; i++)
    {
      // Contoh format file:
      // 123210078 Muhammad_Rafli a belum_kawin

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
  cout << "Tambah Penduduk \n";
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

  writeFile(penduduk, jml); // File di-overwrite oleh struct yang telah ditambahkan
  pressAnyKey();
}

void cetakPenduduk(Penduduk penduduk[], int jml, int awal)
{
  if (jml > 0)
  {
    cout << "[Informasi Penduduk] \n";
    for (int i = awal; i < jml; i++)
    {
      cout << "Penduduk ke-" << i + 1 << "\n"
           << "No. KTP: " << penduduk[i].noKtp << "\n"
           << "Nama: " << penduduk[i].nama << "\n"
           << "Gol. Darah: " << penduduk[i].golDar << "\n"
           << "Status: " << statusCode(penduduk[i].status) << "\n\n";
    }
  }
  else
    cout << "Penduduk masih kosong! \n\n";
}

void sortingPenduduk(Penduduk penduduk[], int jml)
{
  Penduduk sortedPenduduk[100];
  int sortedCode;
  bool isRepeatMenu = 0;
  char inputMenu, inputSort;
  string strSortedBy, sortMethod;

  // Copy Data
  for (int i = 0; i < jml; i++)
    sortedPenduduk[i] = penduduk[i];

  do
  {
    cout << "[PENGURUTAN DATA PENDUDUK] \n"
         << "[1] No. KTP \n"
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
      bool isRepeatSort = 0;

      do
      {
        cout << "[PENGURUTAN DATA PENDUDUK] \n"
             << "[1] Bubble Sort \n"
             << "[2] Selection Sort \n"
             << "[3] Insertion Sort \n"
             << "[4] Shell Sort \n"
             << "[...] Kembali \n"
             << "Pilih > ";
        cin >> inputSort;
        system(CLEAR);

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
          isRepeatSort = 1;
          break;
        }

        if (!isRepeatSort)
        {
          cout << "[Pengurutan Data Penduduk Berdasarkan " + strSortedBy + "] \n"
               << "Metode: " << sortMethod << "\n\n";

          cetakPenduduk(sortedPenduduk, jml);
          pressAnyKey();
        }
      } while (!isRepeatSort);
    }
    break;

    default:
      isRepeatMenu = 1;
      break;
    }

  } while (!isRepeatMenu);
}

void bubbleSort(Penduduk penduduk[], int jml, int sortedCode)
{
  Penduduk tempStruct;
  int i, j;

  if (sortedCode == 2)
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        if (penduduk[j].nama > penduduk[j + 1].nama)
        {
          // Menukar elemen
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
  }

  else if (sortedCode == 3)
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        if (penduduk[j].golDar > penduduk[j + 1].golDar)
        {
          // Menukar elemen
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
  }

  else if (sortedCode == 4)
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        if (penduduk[j].status > penduduk[j + 1].status)
        {
          // Menukar elemen
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
  }

  else
  {
    for (i = 0; i < jml - 1; i++)
    {
      for (j = 0; j < jml - i - 1; j++)
      {
        if (penduduk[j].noKtp > penduduk[j + 1].noKtp)
        {
          // Menukar elemen
          tempStruct = penduduk[j];
          penduduk[j] = penduduk[j + 1];
          penduduk[j + 1] = tempStruct;
        }
      }
    }
  }
}

void selectionSort(Penduduk penduduk[], int jml, int sortedCode)
{
  Penduduk tempStruct;
  int i, j, min_idx;

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

      // Menukar elemen
      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
  }

  else if (sortedCode == 3)
  {
    for (i = 0; i < jml - 1; i++)
    {
      min_idx = i;
      for (j = i + 1; j < jml; j++)
        if (penduduk[j].golDar < penduduk[min_idx].golDar)
          min_idx = j;

      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
  }

  else if (sortedCode == 4)
  {
    for (i = 0; i < jml - 1; i++)
    {
      min_idx = i;
      for (j = i + 1; j < jml; j++)
        if (penduduk[j].status < penduduk[min_idx].status)
          min_idx = j;

      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
  }

  else
  {
    for (i = 0; i < jml - 1; i++)
    {
      min_idx = i;
      for (j = i + 1; j < jml; j++)
        if (penduduk[j].noKtp < penduduk[min_idx].noKtp)
          min_idx = j;

      tempStruct = penduduk[i];
      penduduk[i] = penduduk[min_idx];
      penduduk[min_idx] = tempStruct;
    }
  }
}

void insertionSort(Penduduk penduduk[], int jml, int sortedCode)
{
  int i, j;
  Penduduk key;

  if (sortedCode == 2)
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      /* Bandingkan key sama elemen di kirinya. Kalo key lebih kecil,
         tuker sampe key lebih besar dari elemen di kirinya
         atau mentok paling ujung kiri */
      while (penduduk[j].nama > key.nama && j >= 0)
      {
        penduduk[j + 1] = penduduk[j];
        j--;
      }
      penduduk[j + 1] = key;
    }
  }

  else if (sortedCode == 3)
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      /* Bandingkan key sama elemen di kirinya. Kalo key lebih kecil,
         tuker sampe key lebih besar dari elemen di kirinya
         atau mentok paling ujung kiri */
      while (penduduk[j].golDar > key.golDar && j >= 0)
      {
        penduduk[j + 1] = penduduk[j];
        j--;
      }
      penduduk[j + 1] = key;
    }
  }

  else if (sortedCode == 4)
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      /* Bandingkan key sama elemen di kirinya. Kalo key lebih kecil,
         tuker sampe key lebih besar dari elemen di kirinya
         atau mentok paling ujung kiri */
      while (penduduk[j].status > key.status && j >= 0)
      {
        penduduk[j + 1] = penduduk[j];
        j--;
      }
      penduduk[j + 1] = key;
    }
  }

  else
  {
    for (i = 0; i < jml; i++)
    {
      key = penduduk[i];
      j = i - 1;

      /* Bandingkan key sama elemen di kirinya. Kalo key lebih kecil,
         tuker sampe key lebih besar dari elemen di kirinya
         atau mentok paling ujung kiri */
      while (penduduk[j].noKtp > key.noKtp && j >= 0)
      {
        penduduk[j + 1] = penduduk[j];
        j--;
      }
      penduduk[j + 1] = key;
    }
  }
}

void shellSort(Penduduk penduduk[], int jml, int sortedCode)
{
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

        // shift earlier gap-sorted elements up until the correct
        // location for a[i] is found
        int j;
        for (j = i; j >= gap && penduduk[j - gap].nama > temp.nama; j -= gap)
          penduduk[j] = penduduk[j - gap];

        //  put temp (the original a[i]) in its correct location
        penduduk[j] = temp;
      }
    }
  }

  else if (sortedCode == 3)
  {
    for (int gap = jml / 2; gap > 0; gap /= 2)
    {
      for (int i = gap; i < jml; i += 1)
      {
        Penduduk temp = penduduk[i];
        int j;

        for (j = i; j >= gap && penduduk[j - gap].golDar > temp.golDar; j -= gap)
          penduduk[j] = penduduk[j - gap];
        penduduk[j] = temp;
      }
    }
  }

  else if (sortedCode == 4)
  {
    for (int gap = jml / 2; gap > 0; gap /= 2)
    {
      for (int i = gap; i < jml; i += 1)
      {
        Penduduk temp = penduduk[i];
        int j;

        for (j = i; j >= gap && penduduk[j - gap].status > temp.status; j -= gap)
          penduduk[j] = penduduk[j - gap];
        penduduk[j] = temp;
      }
    }
  }

  else
  {
    for (int gap = jml / 2; gap > 0; gap /= 2)
    {
      for (int i = gap; i < jml; i += 1)
      {
        Penduduk temp = penduduk[i];
        int j;

        for (j = i; j >= gap && penduduk[j - gap].noKtp > temp.noKtp; j -= gap)
          penduduk[j] = penduduk[j - gap];
        penduduk[j] = temp;
      }
    }
  }
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

string statusCode(int kode)
{
  if (kode == 2)
    return "Kawin (2)";
  else if (kode == 3)
    return "Cerai Hidup (3)";
  else if (kode == 4)
    return "Cerai Mati (4)";
  else
    return "Belum Kawin (1)";
}

void statusCode()
{
  cout << "[STATUS PERKAWINAN] \n"
       << "[1]: Belum Kawin \n"
       << "[2]: Kawin \n"
       << "[3]: Cerai Hidup \n"
       << "[4]: Cerai Mati \n";
}

void pressAnyKey()
{
  cout << "[Tekan tombol apa saja untuk melanjutkan.]";
  getch();
  system(CLEAR);
}
