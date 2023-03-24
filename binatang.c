#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <zip.h>
#include <time.h>
#include <sys/types.h>
#include <errno.h>

int main () {

    // diubah menjadi docs karena pake wget dan no check-certif (non-aktif ssl/tls saat unduh lwt https)
    char *srcf_download = "wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=1oDgj5kSiDO0tlyS7-20uz7t20X3atwrq' -O binatang.zip";
    // Perintah untuk download file dari link
    system(srcf_download);

    int pid, outStatus;
    CURL *myCurl; //req http ke server untuk download (wget)
    CURLcode resCurl; //def status hasil dari curl 
    FILE *fiPo; //repr file (menyimpan hasil download)
    
    srand(time(NULL)); //inisiasi seed acak

    // Unzip file hasil download
    pid = fork(); //make child process
   
    if (pid == 0) {
        execlp("unzip", "unzip", "binatang.zip", NULL); 
        exit(1);
    } else if (pid > 0) {
    	waitpid(pid, &outStatus, 0);
    
    //cek child process apakah clear (0 = sukses)	
    if (WIFEXITED(outStatus) && WEXITSTATUS(outStatus) == 0) {
	    // pilih file gambar acak
	   DIR *dir;
	   struct dirent *itm; //item to dirent
	   char *imgName = malloc(sizeof(char) * 500); //size name img
	//current dir
	char *currDir = "."; 
	dir = opendir(currDir);
	if (dir  == NULL) {
	   perror("Gagal membuka direktori.");
	   exit(1);
	   }    	
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
	
        // Shift Grape-kun menjaga hewan
        printf("Saat ini, Grape-kun melakukan penjagaan hewan : %s\n\n", imgName);
	
	//array habitat
	char* jenisHewan[] = {"HewanDarat", "HewanAmphibi", "HewanAir"};   
	//sum elemen dalam jenisHewan
	int totalJenis = sizeof(jenisHewan) / sizeof(jenisHewan[0]); //ukuran total / tiap elemen (byte)
	
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
         // Pindahkan file-file hewan sesuai habitat nya (direktori-nya)
        system("find . -iname '*_darat.jpg' -exec mv -n {} HewanDarat/ \\;");
        system("find . -iname '*_amphibi.jpg' -exec mv -n {} HewanAmphibi/ \\;");
        system("find . -iname '*_air.jpg' -exec mv -n {} HewanAir/ \\;");
        printf("Bagus! Hewan berhasil dipindahkan sesuai jenisnya.\n\n");
        	}
 	}

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
                
                // remove dir setelah zip
                char rmvDir[100];
                sprintf(rmvDir, "rm -rf %s", dir_name);
                system(rmvDir);
                 
                }
            }
        
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

