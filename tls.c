#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;

    //char pathname[200];
    int i = 0;
    int detailCount = 0;
    int pointDir = 0;
    char* detail = "-a";
    int success = 0;
    char cwd[1024];


    if(argc == 1){
        //printf("./tls\n");
        detailCount = 0;
        if(getcwd(cwd, sizeof(cwd)) != NULL){
            if((dir = opendir(cwd)) == NULL){
                success = 0;
                detailCount = 0;
                printf("Open directory does not success.\n");
            }else{
                success = 1;
                dir = opendir(cwd);

                while(((ptr = readdir(dir)) != NULL)){
                     printf("%s\n", ptr->d_name);
                }
                closedir(dir);
                return 0;
            }
        }
    }
    if(argc == 3){
        //printf("./tls -a DIR\n");
        pointDir = 1;
        if(strcmp(argv[1], detail) == 0){
            detailCount = 1;
            if((dir = opendir(argv[2])) == NULL){
                success = 0;
                detailCount = 0;
                pointDir = 0;
                printf("Open directory does not success.\n");
            }else{
                success = 1;
            }
        }
    }

    if((strcmp(argv[1], detail) == 0) && (argc == 2)){
        //printf("./tls -a\n");
        detailCount = 1;
        if(getcwd(cwd, sizeof(cwd)) != NULL){
            if((dir = opendir(cwd)) == NULL){
                success = 0;
                detailCount = 0;
                printf("Open directory does not success.\n");
            }else{
                success = 1;
                dir = opendir(cwd);
            }
        }else{
            printf("Directory is not exist.\n");
            detailCount = 0;
            success = 0;
        }

    }


    while(((ptr = readdir(dir)) != NULL) && (detailCount == 1) && (success == 1)){
        //printf("%s", ptr->d_name);
        char pathname[200];
        //strcpy(pathname, argv[1]);
        //strcat(pathname, ptr->d_name);
        if(pointDir == 0){
            sprintf(pathname, "%s/%s", cwd, ptr->d_name );
            stat(pathname, &buf);
        }else{
            sprintf(pathname,"%s/%s", argv[2],ptr->d_name);
            stat(pathname, &buf);
        }


        if(S_ISREG(buf.st_mode)){
            printf("-");
        }else{
            printf("d");
        }

        i = buf.st_mode & S_IRUSR;
        if(i == S_IRUSR){
            printf("r");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IWUSR;
        if(i == S_IWUSR){
            printf("w");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IXUSR;
        if(i == S_IXUSR){
            printf("x");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IRGRP;
        if(i == S_IRGRP){
            printf("r");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IWGRP;
        if(i == S_IWGRP){
            printf("w");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IXGRP;
        if(i == S_IXGRP){
            printf("x");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IROTH;
        if(i == S_IROTH){
            printf("r");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IWOTH;
        if(i == S_IWOTH){
            printf("w");
        }else{
            printf("-");
        }

        i = buf.st_mode & S_IXOTH;
        if(i == S_IXOTH){
            printf("x");
        }else{
            printf("-");
        }
        printf("      %-8d", (int)buf.st_nlink);
        printf("%-8d", (int)buf.st_size);

        struct tm *tm;
        //time_t timep;
        //p = gmtime(&buf.st_mtime);
        //printf("%d/%d/%d", (1900 + p -> tm_year), (1 + p -> tm_mon), p -> tm_mday);
        char field_modified_time[100];
        tm = localtime(&buf.st_mtime);
        strftime(field_modified_time, sizeof(field_modified_time),
                "%Y/%m/%d/%H:%M:%S",tm);
        printf("%s", field_modified_time);
        printf("     %s\n", ptr->d_name);
    }



    closedir(dir);

    return 0;

}
