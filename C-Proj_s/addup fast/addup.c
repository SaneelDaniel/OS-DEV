#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/*
* program acts as a linux utility to add numbers in a text file
 * reads the numeric values from various files and returns the grand total
*/
int main (int argc, char **argv){
    double total = 0.000 , current = 0.000;
    char *buf;
    int fds[2], fCount = argc -1;
    FILE *fp;
    pipe(fds);
    pid_t pid;

    //create new processes for every file, and the child calculates the sum and exits
    for(int i = 0; i<fCount; i++){

        double cftotal = 0;     //current file total
        buf = (char *)malloc(250*sizeof(char));     //creates the memory to store the path
        getcwd(buf,200);        //stores the path
        strcat(buf, "/");       //formatting the string
        strcat( buf, argv[i+1]);  //formatting the string
        pid = fork();


        //if child, calculate the total for current file
        if(pid == 0){
            close(fds[0]);
            fp = fopen( argv[i+1], "r");

            if(fp == NULL){     //null pointer check
                printf("the file: %s -> cannot be opened\n", argv[i+1]);
                exit(0);
            }
            else{       //read each line and calculate the total until the end of file is reached
                fscanf(fp, "%lf", &current);

                while(!feof(fp)){
                    cftotal = cftotal + current;
                    fscanf(fp, "%lf", &current );
                }

                write(fds[1], &cftotal, sizeof(cftotal));
                free(buf);
                fclose(fp);
                exit(0);
            }
        }


    }

    close(fds[1]);

    //read all the individual total and calculate the Grand total.
    for(int i = 0; i<argc-1; i++){
        double pReturn = 0;
        read(fds[0], &pReturn, sizeof(pReturn));
        total = total + pReturn;
    }

    printf("%lf\n", total);
}