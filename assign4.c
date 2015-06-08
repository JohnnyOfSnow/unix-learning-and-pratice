#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#define BUFFERSIZE 200

int main(int argc, char* argv[]){

    char* putDir = "-d";
    char* synLink = "-s";
    int dir = 0;
    int link = 0;
    int fd_read;
    int fd_write;
    char buffer[BUFFERSIZE];
    char *ptr;
    int errno;
    int byte_read, byte_write;
    int targetLength;

    if(strcmp(argv[1],putDir) == 0){
        dir = 1;
    }else if(strcmp(argv[1],synLink) == 0){
        link = 1;
    }else{

    }

    if((dir == 0) && (link == 0)){
        if(argc != 3){
            printf("parameter are not enough\n");
        }else{
            if((fd_read = open(argv[1], O_RDONLY, 0644)) == -1){
                printf("SOURCE does not exist\n");
            }else{
                targetLength = strlen(argv[2]);
                if(targetLength <= 25){
                //printf("Open file Success for read\n");
                    if((fd_write = open(argv[2], O_RDONLY, 0644)) == -1){
                        if((fd_write = open(argv[2], O_RDWR | O_CREAT | O_TRUNC)) == -1){
                            printf("your target path does not exist\n");
                        }else{
                            //printf("open a file for writing\n");
                            while((byte_read = read(fd_read, buffer, BUFFERSIZE)) > 0){
                                write(fd_write, buffer, byte_read);
                            }
                        }
                        close(fd_read);
                        close(fd_write);

                    }else{
                        printf("TARGET is a file that is already exist\n");
                        close(fd_read);
                    }

                    close(fd_read);
                    close(fd_write);
                }else{
                    printf("TARGET lenth shouldn't be bigger than 25\n");
                }
                close(fd_read);
            }
        }
    }
    if(dir == 1){
        if(argc != 4){
            printf("TARGET is a directory, but the parameter is not specified\n");
        }else{
            char target[26];
            strcpy(target, argv[3]);
            strcat(target, "/");
            strcat(target, argv[2]);
            if((fd_read = open(argv[2], O_RDONLY, 0644)) == -1){
                printf("SOURCE does not exist\n");
            }else{
                targetLength = strlen(target);
                if(targetLength <= 25){
                //printf("Open file Success for read\n");
                    if((fd_write = open(target, O_RDONLY, 0644)) == -1){
                        if((fd_write = open(target, O_RDWR | O_CREAT | O_TRUNC)) == -1){
                            printf("your target path does not exist\n");
                        }else{
                            //printf("open a file for writing\n");
                            while((byte_read = read(fd_read, buffer, BUFFERSIZE)) > 0){
                                write(fd_write, buffer, byte_read);
            printf("TARGET is a directory, but the parameter is not specified\n");
        }else{
            char target[26];
            strcpy(target, argv[3]);
            strcat(target, "/");
            strcat(target, argv[2]);
            if((fd_read = open(argv[2], O_RDONLY, 0644)) == -1){
                printf("SOURCE does not exist\n");
            }else{
                targetLength = strlen(target);
                if(targetLength <= 25){
                //printf("Open file Success for read\n");
                    if((fd_write = open(target, O_RDONLY, 0644)) == -1){
                        if((fd_write = open(target, O_RDWR | O_CREAT | O_TRUNC)) == -1){
                            printf("your target path does not exist\n");
                        }else{
                            //printf("open a file for writing\n");
                            while((byte_read = read(fd_read, buffer, BUFFERSIZE)) > 0){
                                write(fd_write, buffer, byte_read);
                            }
                        }
                        close(fd_read);
                        close(fd_write);

                    }else{
                        printf("TARGET is a file that is already exist\n");
                        close(fd_read);
                    }
                }

                close(fd_read);
                close(fd_write);
            }
        }
    }

    if(link == 1){
       // printf("create a link for file");
        if(argc != 4){
            printf("TARGET is link, but the parameter is not specified\n");
        }else{
            if((fd_read = open(argv[2], O_RDONLY, 0644)) == -1){
                printf("SOURCE does not exist\n");
            }else{
                int linkRight = symlink(argv[2], argv[3]);
                if(linkRight == 0){

                }else{
                    printf("Link error");
                }
            }
        }
    }
    return 0;
}

