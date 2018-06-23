#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>

void printdir(char *dirpath, int depth) {
     DIR *dir = NULL;
     struct dirent *entry = NULL;
     struct stat statbuf;

     dir = opendir(dirpath);
     if(NULL == dir) {
         perror("opendir failed");
         return ;
     }

     chdir(dirpath);
     while((entry = readdir(dir) ) != NULL ) {
         lstat(entry->d_name, &statbuf);
         if(S_ISDIR(statbuf.st_mode) ) {
             if((strcmp(".", entry->d_name) == 0) || (strcmp("..", entry->d_name) == 0) ) {
                 continue;
             }
             printf("%*s%s\n", depth, "", entry->d_name);
             printdir(entry->d_name, depth+4);
         }
         else {
             printf("%*s%s\n", depth, "", entry->d_name);
         }
     }
     chdir("..");
     closedir(dir);
}

int main(int argc, char *argv[]){
    char *directory = "./";
    int depth = 0;
    if(argc > 1) {
        directory = argv[1];
    }
    if(argc > 2) {
    }
    printf("[%s:%d] Directory scan of %s\n", __FILE__, __LINE__, directory);
    printdir(directory, depth); 
    printf("[%s:%d] DONE\n", __FILE__, __LINE__);
}
