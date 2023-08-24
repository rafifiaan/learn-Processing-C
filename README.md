# Processing - Get files and processing in various forms using C Languages

## **Documentation In *Bahasa (ID/INA)***

### Question Description
Grape-kun adalah seorang penjaga hewan di kebun binatang, dia mendapatkan tugas dari atasannya untuk melakukan penjagaan pada beberapa hewan-hewan yang ada di kebun binatang sebelum melakukan penjagaan Grape-kun harus mengetahui terlebih dahulu hewan apa aja yang harus dijaga dalam drive kebun binatang tersebut terdapat folder gambar dari hewan apa saja yang harus dijaga oleh Grape-kun. Berikut merupakan link download dari drive kebun binatang tersebut : https://drive.google.com/uc?export=download&id=1oDgj5kSiDO0tlyS7-20uz7t20X3atwrq

* Grape-kun harus mendownload file tersebut untuk disimpan pada penyimpanan local komputernya. Dan untuk melakukan melihat file gambar pada folder yang telah didownload Grape-kun harus melakukan unzip pada folder tersebut.
* Setelah berhasil melakukan unzip Grape-kun melakukan pemilihan secara acak pada file gambar tersebut untuk melakukan shift penjagaan pada hewan tersebut.
* Karena Grape-kun adalah orang yang perfeksionis Grape-kun ingin membuat direktori untuk memilah file gambar tersebut. Direktori tersebut dengan nama HewanDarat, HewanAmphibi, dan HewanAir. Setelah membuat direktori tersebut Grape-kun harus melakukan filter atau pemindahan file gambar hewan sesuai dengan tempat tinggal nya.
* Setelah mengetahui hewan apa saja yang harus dijaga Grape-kun melakukan zip kepada direktori yang dia buat sebelumnya agar menghemat penyimpanan.

**Catatan : untuk melakukan `zip` dan `unzip` tidak boleh menggunakan system**

### Running Program
Untuk compile dengan perintah sebagai berikut :
```R
gcc -0 binatang binatang.c -lcurl -lzip  
```
Setelah berhasil compile, maka jalankan dengan menggunakan command berikut :
```R
./binatang
```

### Problem Solving
Pertama, definisikan library yang akan digunakan untuk membuat sebuah program penyelesaian tersebut. Dalam kasus penyelesaian tersebut, saya menggunakan library antara lain :

- `stdio.h`: library standar C yang menyediakan fungsi input/output standar seperti printf(), scanf(), dan lain-lain.
- `curl/curl.h`: library untuk melakukan transfer data dengan protokol internet seperti HTTP, FTP, SMTP, dan lain-lain.
- `stdlib.h`: library standar C yang menyediakan fungsi untuk manajemen memori seperti alokasi dan dealokasi memori, konversi tipe data, dan lain-lain.
- `unistd.h`: library standar C yang menyediakan fungsi-fungsi sistem seperti sleep(), fork(), dan lain-lain.
- `sys/wait.h`: library standar C yang menyediakan fungsi untuk mengatur proses seperti wait(), waitpid(), dan lain-lain.
- `dirent.h`: library untuk mengakses direktori dan berkas-berkas yang ada di dalamnya.
- `string.h`: library standar C yang menyediakan fungsi-fungsi pemrosesan string seperti strcpy(), strcat(), dan lain-lain.
- `sys/stat.h`: library untuk mendapatkan informasi tentang status suatu berkas atau direktori seperti ukuran, waktu pembuatan, dan lain-lain.
- `zip.h`: library untuk melakukan kompresi dan dekompresi berkas dalam format ZIP.
- `time.h`: library untuk mengakses dan memanipulasi informasi waktu seperti tanggal, jam, dan lain-lain.
- `sys/types.h`: library standar C yang menyediakan definisi tipe data umum seperti pid_t, size_t, dan lain-lain.
- `errno.h`: library standar C yang menyediakan variabel errno untuk menangkap kesalahan sistem yang terjadi selama program berjalan.

***Kemudian membuat 1 fungsi yaitu `int main ()` sebagai program utama dengan berbagai fungsi didalamnya yaitu :***

#### ***Poin 1***
```R
// diubah menjadi docs karena pake wget dan no check-certif (non-aktif ssl/tls saat unduh lwt https)
char *srcf_download = "wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=1oDgj5kSiDO0tlyS7-20uz7t20X3atwrq' -O binatang.zip";
// Perintah untuk download file dari link
system(srcf_download);
```
Untuk hasil-nya seperti berikut :

![dwnld](https://user-images.githubusercontent.com/91828276/227481705-c073c1c9-bbec-4be6-b513-27e765499258.png)

Penjelasan : 
- Mendefinisikan perintah `download` menggunakan `char pointer` dengan nama variabel `srcf_download`
- Menjalankan perintah `download` dengan menggunakan perintah `system` dan bantuan perintah `wget` dengan `URL Drive` diubah di-passing menjadi `URL Docs` untuk mengunduh file secara non-interaktif dari jaringan (tidak memerlukan interaksi/input user). Opsi `--no-check-certificate` pada perintah `wget` digunakan untuk menonaktifkan SSL/TLS saat melakukan pengunduhan.
- `-O binatang.zip` merupakan argumen untuk menentukan nama file dari hasil download. Dalam hal ini, tentu nama yang akan disimpan yaitu sesuai dengan nama file pada drive yaitu `binatang.zip`.

```R
int pid, outStatus;
CURL *myCurl; //req http ke server untuk download (wget)
CURLcode resCurl; //def status hasil dari curl 
FILE *fiPo; //repr file (menyimpan hasil download)
    
srand(time(NULL)); //inisiasi seed acak
```
Penjelasan : 
- `pid` sebagai Process ID yang dihasilkan oleh fungsi `fork()` nantinya
- `outStatus` sebagai output status dari proses child yang dihasilkan oleh fungsi `waitpid()`
- `myCurl` sebagai variabel untuk menyimpan pointer ke objek CURL, yang berfungsi untuk melakukan request HTTP menggunakan library curl
- `resCurl` sebagai variabel hasil yang digunakan untuk menyimpan hasil status operasi yang dijalankan oleh objek CURL
- `fiPo` sebagai representasi file pointer untuk menyimpan pointer ke file yang akan digunakan untuk menyimpan hasil download
- `srand(time(NULL))` digunakan untuk inisiasi seed acak dengan menggunakan fungsi `srand()` dan memasukkan nilai `time(NULL)` sebagai parameter.

```R
// Unzip file hasil download
pid = fork(); //make child process
   
if (pid == 0) {
    execlp("unzip", "unzip", "binatang.zip", NULL); 
    exit(1);
} else if (pid > 0) {
	waitpid(pid, &outStatus, 0);
```
Untuk hasil-nya seperti berikut :

![unzip](https://user-images.githubusercontent.com/91828276/227487796-d5e7c298-d0c3-467b-b607-0eb4f66d4700.png)

Penjelasan :
- Membuat child proses dengan `pid = fork()`
- Child proses digunakan untuk menjalankan perintah `unzip` pada file `binatang.zip` dengan `execlp()`. Jika gagal program akan terminate dengan `exit(1)`
- Setelah child proses selesai, maka parent process akan menunggu hingga child process selesai dijalankan menggunakan fungsi `waitpid()` Fungsinya yaitu digunakan untuk menunggu hingga child process dengan pid yang diidentifikasi selesai dijalankan dan memberikan status keluaran (output) dari child process tersebut pada variabel `outStatus`

```R
//cek child process apakah clear (0 = sukses)	
if (WIFEXITED(outStatus) && WEXITSTATUS(outStatus) == 0) {
   // pilih file gambar acak
   DIR *dir;
   struct dirent *itm; //item to dirent
   char *imgName = malloc(sizeof(char) * 500); //size name img
```
Penjelasan :
- `if (WIFEXITED(outStatus) && WEXITSTATUS(outStatus) == 0)` digunakna untuk Memeriksa status keluaran child process. WIFEXITED digunakan untuk memeriksa apakah child process telah berakhir, dan WEXITSTATUS digunakan untuk memeriksa status keluaran dari child process. Dalam hal ini, jika status keluaran dari child process sama dengan `0`, maka child process dianggap berhasil dan program akan melanjutkan ke tahap selanjutnya.
- `DIR *dir` digunakan untuk membuat pointer untuk direktori yang akan diproses.
- `struct dirent *itm`  digunakan untuk membuat pointer untuk item yang ditemukan dalam direktori.
- `char *imgName = malloc(sizeof(char) * 500)` digunakan untuk membuat pointer `imgName` dengan alokasi memori sebesar `500 byte`. `imgName` akan menyimpan nama file gambar `acak` yang dipilih selanjutnya.

```R
//current dir
char *currDir = "."; 
dir = opendir(currDir);
if (dir  == NULL) {
	perror("Gagal membuka direktori.");
	exit(1);
    }
```
Penjelasan :
- `char *currDir = "."` digunakan untuk mendefinisikan variabel `currDir` sebagai string dengan nilai `"."`, yang merupakan `direktori saat ini`.
- `dir = opendir(currDir)` digunakan untuk membuka direktori yang diarahkan oleh variabel currDir menggunakan fungsi opendir. Fungsi ini akan mengembalikan pointer ke direktori yang telah dibuka.
- `if (dir == NULL)` digunakan untuk memeriksa apakah pembukaan direktori berhasil. Jika dir sama dengan `NULL`, maka pembukaan direktori gagal dengan mengeluarkan pesan error `"Gagal membuka direktori."` dan program terminate dengan `exit(1)`.

```R
if (dir != NULL) {
        int fileCount = 0;
        
         while ((itm = readdir(dir)) != NULL) {
             //menangkap hanya nama file ber-ekstensi .jpg
             if (strstr(itm->d_name, ".jpg") == NULL) {
            	 continue;
             }
             //di generate random
             if (rand() % ++fileCount == 0) {
                 strcpy(imgName, itm->d_name);
             }
         } 
         closedir(dir);
       } else {
         perror("");
         return 1;
       }
```
Penjelasan :
- Kebalikan dengan kondisi sebelumnya, yaitu jika `dir != NULL` atau berhasil membuka direktori maka melakukan inisiasi variabel `fileCount` (untuk menyimpan jumlah file gambar) dengan nilai `0`
- Kemudian dilakukan loop while untuk membaca `setiap item` di dalam direktori hingga tidak ada lagi item yang bisa dibaca.
- Didalam loop, dilakukan pengecekan apakah nama file mengandung ekstensi `".jpg"`. Jika tidak, maka loop dilanjutkan ke item selanjutnya. Loop hanya menangkap file yang mengandung ekstensi `.jpg`
- Setelah itu, jika file memiliki ekstensi ".jpg", `increment nilai fileCount`, lalu dilakukan perhitungan random untuk menentukan apakah file tersebut akan dipilih. Jika file terpilih (nilai random adalah 0), maka nama file disalin ke variabel `imgName`.  
- Setelah loop selesai, direktori ditutup dengan `closedir(dir)`.
- Jika dir bernilai NULL (gagal membuka direktori), akan menampilkan pesan error dan mengembalikan nilai 1 (terminate).

#### ***Poin 2***
```R
// Shift Grape-kun menjaga hewan
printf("Saat ini, Grape-kun melakukan penjagaan hewan : %s\n\n", imgName);
```
Untuk hasil-nya seperti berikut :

![rndmpick](https://user-images.githubusercontent.com/91828276/227487784-eb0bea9c-9577-445c-8af8-a2aa64125b0b.png)

Penjelasan :
- Setelah dipilih secara acak, pilihan yang telah dipilih tersebut `dicetak dalam console` dengan menggunakan `printf`

#### ***Poin 3***
```R
//array habitat
char* jenisHewan[] = {"HewanDarat", "HewanAmphibi", "HewanAir"};   
//sum elemen dalam jenisHewan
int totalJenis = sizeof(jenisHewan) / sizeof(jenisHewan[0]); //ukuran total 
```
Penjelasan : 
- Setelah berhasil memilih random, selanjutnya yaitu deklarasi array `jenisHewan` berisi tiga elemen yaitu `"HewanDarat"`, `"HewanAmphibi"`, dan `"HewanAir"`
- Kemudian dilakukan `perhitungan jumlah elemen pada array jenisHewan` dengan cara menghitung `total ukuran array dalam byte (sizeof(jenisHewan))` **dibagi** dengan `ukuran tiap elemen (sizeof(jenisHewan[0]))`
- Dengan cara ini, kita bisa mendapatkan jumlah total elemen pada array jenisHewan tanpa harus menghitung manual. Hasil perhitungan tersebut disimpan dalam variabel `totalJenis`

```R
// perulangan untuk cek direktori hewan
for (int idx = 0; idx < totalJenis; idx++) {
	// inisiasi file/dir
	struct stat FD = {};
	// cek kondisi direktori
	if (stat(jenisHewan[idx], &FD) == -1) {
		if (mkdir(jenisHewan[idx], 0777) == -1) { // mode semua (rwx)
			printf("Direktori gagal dibuat!\n");
			exit(1);
		} else {
			printf("Direktori %s berhasil dibuat! \n", jenisHewan[idx]);
		}
	}
}
```
Penjelasan :
- Setelah mendeklarasi array direktori, selanjutnya yaitu memeriksa direktori hewan dengan perulangan.
- Didalamnya di-inisiasi filde/direktori variabel `FD` dengan `struct stat kosong`
- Setelah itu melakukan cek kondisi direktori dengan menggunakan stat. Fungsi ini akan mengembalikan nilai `-1` jika tidak dapat membaca status dari direktori.
- Jika direktori tidak ada, maka akan dibuat direktori baru menggunakan fungsi `mkdir` dengan mode akses `0777` (semua memiliki hak akses read, write, dan execute). Jika tidak berhasil dibuat, maka program akan mencetak pesan `"Direktori gagal dibuat!"` dan program keluar/terminate dengan exit status `1`
- Sebaliknya, jika direktori berhasil dibuat, akan mencetak pesan `"Direktori %s berhasil dibuat!"` dengan nama direktori yang dibuat.

**NB : Untuk membuat direktori tidak disertakan dokumentasi karena program hanya sekali jalan dari download hingga melakukan zipping, tetapi hanya ditampilkan berupa bukti pesan telah berhasil seperti berikut :*

![mkdir](https://user-images.githubusercontent.com/91828276/227487791-57830c20-5601-4b6a-be32-07a3669238c5.png)

```R
// Pindahkan file-file hewan sesuai habitat nya (direktori-nya)
system("find . -iname '*_darat.jpg' -exec mv -n {} HewanDarat/ \\;");
system("find . -iname '*_amphibi.jpg' -exec mv -n {} HewanAmphibi/ \\;");
system("find . -iname '*_air.jpg' -exec mv -n {} HewanAir/ \\;");
printf("Bagus! Hewan berhasil dipindahkan sesuai jenisnya.\n\n");
        }
}
```
Penjelasan :
- Setelah direktori berhasil dibuat, langkah selanjutnya yaitu `meng-klasifikasikan` hewan sesuai dengan `jenisnya`
- Klasifikasi dengan menggunakan bantuan `system` dan perintah `find` yang digunakan untuk mencari nama file dengan akhiran `'*_darat.jpg'`, `'*_amphibi.jpg'`, `'*_air.jpg'` pada direktori tempat program dijalankan. Kemudian dipindahkan sesuai jenisnya yaitu `HewanDarat/`, `HewanAmphibi/`, `HewanAir/`. Pemindahan file-file ini dengan bantuan perintah `mv` dan argumen `-n` yang digunakan tersebut bertujuan agar file tidak ditimpa jika file dengan nama yang sama sudah ada di direktori tujuan.
- Terakhir jika proses pemindahan sudah selesai, akan mengeluarkan pesan `"Bagus! Hewan berhasil dipindahkan sesuai jenisnya"`

**NB : Untuk meng-klasifikasikan/memindahkan sesuai direktori jenis juga tidak disertakan dokumentasi karena program hanya sekali jalan dari download hingga melakukan zipping, tetapi hanya ditampilkan berupa bukti pesan telah berhasil seperti berikut :*

![pindahjenis](https://user-images.githubusercontent.com/91828276/227487792-9b6a1352-f3d9-41bd-993b-c072d7e50d0d.png)

#### ***Poin 4***
```R
//fungsi zip menggunakan data pointer
void zipDir(const char* dir_name) {
            
        pid_t pid;
        int statPros;
            
        pid = fork(); // buat child proses

        if (pid < 0) {
            fprintf(stderr, "Yah Proses fork gagal!\n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // child process
            char zip_name[100];
            sprintf(zip_name, "%s.zip", dir_name);
            execlp("zip", "zip", "-r", zip_name, dir_name, NULL);
            exit(EXIT_SUCCESS);
        } else {
            
            // parent process
            waitpid(pid, &statPros, 0);
```
Penjelasan :
- Setelah di-klasifikasikan sesuai dengan jenisnya, langkah selanjutnya yaitu melakukan `zip` pada ketiga direktori tersebut
- Langkah awal yaitu membuat fungsi `zipDir` dengan satu argumen yaitu `dir_name` menggunakan `const char pointer`
- Setelah itu mendeklarasikan variabel `pid` dengan tipe data `pid_t` dan variabel `statPros` dengan tipe data `int`
- Kemudian membuat child proses dengan `pid = fork()`
- Setelah membuat child proses, terdapat conditional statement dengan pernyataan jika `pid < 0` maka kondisi gagal yang kemudian mengeluarkan pesan `"Yah Proses fork gagal!"` dan program akan selesai/terminate
- Sebaliknya, jika kondisi `pid == 0` maka program akan berjalan dengan mendeklarasikan variabel `char zip_name[100]` dengan tipe data `char` dan berukuran `100`.
- Setelah itu, `sprintf(zip_name, "%s.zip", dir_name)` akan menyalin `nama direktori (dir_name)` ke variabel `zip_name` dengan menambahkan ekstensi `.zip`
- Kemudian terdapat proses `execlp("zip", "zip", "-r", zip_name, dir_name, NULL)` yang digunakan untuk menjalankan perintah zip dengan argumen `-r (rekursif)` dan `nama file zip (zip_name)` yang ingin dicompress beserta direktorinya (dir_name).
- Jika proses menjalankan perintah zip telah selesai maka program akan `exit(EXIT_SUCCESS)`
- Kondisi sebaliknya, `waitpid(pid, &statPros, 0)` menunggu child process selesai dieksekusi dengan menggunakan `waitpid` dan menyimpan status dari child process ke variabel `statPros`.

```R
 // remove dir setelah zip
    char rmvDir[100];
    sprintf(rmvDir, "rm -rf %s", dir_name);
    system(rmvDir);  
        }
}
```
Penjelasan :
- Setelah proses zip selesai, dikarenakan pada perintah `agar menghemat penyimpanan`, maka dilakukan `remove` pada folder yang sebelumnya dilakukan `zip`.
- Langkah awal yang dilakukan yaitu dengan mendeklarasikan variabel `rmvDir` sebagai array dengan panjang karakter `100` dan tipe data `char`.
- Setelah itu, dalam `sprintf(rmvDir, "rm -rf %s", dir_name)` digunakan `sprintf` untuk memformat string ke variabel rmvDir. String ini akan berisi command `rm -rf` yang akan digunakan untuk menghapus direktori dengan nama yang disimpan di `dir_name`.
- Dan pada akhirnya menggunakan bantuan `system(rmvDir)` untuk menjalankan command `rm -rf` untuk menghapus direktori yang disimpan di `dir_name`. Fungsi system digunakan untuk mengeksekusi command di dalam shell dan mengembalikan status hasil eksekusi.

```R
// def value dari dir_name
char dirDar[100] = "HewanDarat";
char dirAmp[100] = "HewanAmphibi";
char dirAir[100] = "HewanAir";
	   
// zip semua dir
zipDir(dirDar);
zipDir(dirAmp);
zipDir(dirAir);

printf("Selamat! Proses Zip folder berhasil.\n");

    return 0;
}
```
Untuk hasil-nya seperti berikut :

**Tampilan ketika didalam folder linux :*

![zipAll](https://user-images.githubusercontent.com/91828276/227489352-bc5135f0-dd44-4c57-adfe-a176fa7a682a.png)

**Tampilan jika dibuka satu-per-satu dalam folder linux :*

![zipDar](https://user-images.githubusercontent.com/91828276/227489371-fee3d8e4-738f-4585-86ff-80c48c954fee.png)

![zipAmp](https://user-images.githubusercontent.com/91828276/227489363-ede5620d-95bc-4cc9-96d0-e5f205eacbd1.png)

![zipAir](https://user-images.githubusercontent.com/91828276/227489339-3e91e239-5d38-4a8f-a244-fa02e50c519e.png)

**Tampilan pesan console :*

![zipCons](https://user-images.githubusercontent.com/91828276/227489411-05d85e48-c6ea-43d6-bfb5-9a9313ee851b.png)

Penjelasan :
- `char dir...[100] = "Hewan..."` merupakan variabel definisi dari argumen `dir_name` pada fungsi `zipDir`
- `zipDir(...)` merupakan proses fungsi dijalankan setelah melewati conditional statements
- Setelah proses zip selesai, akan mengeluarkan pesan `"Selamat! Proses Zip folder berhasil"` dan program selesai. 

***Thank you for visiting this repository, stay tuned for more projects!***
