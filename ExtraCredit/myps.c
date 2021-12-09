/* 
 * Author: Eric Melin
 * Date: Weds 1 Dec 2021 11:50:00 AM MNT
 * Description: Starter code for final project (myps)
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "ProcEntry.h"

#define MAX_PATH_LENGTH 4096
#define UNUSED(x) (void)x

//check if directory & first index is a number filter function
static int defaultFilter (const struct dirent *current) {
    if(current->d_type == DT_DIR && current->d_name[0] >= '0' && current->d_name[0] <= '9') {  
        return 1;
    }
    return 0;
}

//no sort filter
int noSort(const struct dirent ** entryA, const struct dirent ** entryB) {
    UNUSED(entryA);
    UNUSED(entryB);

    return 0;
}

//sorts by process_id
static int pidSort(const void *a, const void *b)
{
     ProcEntry *f = *(ProcEntry **)a;
     ProcEntry *s = *(ProcEntry **)b;
     int rval = f->process_id - s->process_id;
     return rval;
}

//sorts by comm 
static int comSort(const void *a, const void *b)
{
     ProcEntry *f = *(ProcEntry **)a;
     ProcEntry *s = *(ProcEntry **)b;
     int rval = strcmp(f->comm, s->comm);
     return rval;
}

//default proc filter
int ProcEntryDefaultFilter(const ProcEntry *entry) {
    UNUSED(entry);

    return 1;
}

//togle display for proc zombie state
static int zombieFilter (const ProcEntry *entry) {
    return entry->state == 'Z';
}

//prints the functionality of all available arguments
void printFunctionality(void) {
    printf("Usage: ./myps [-d <path>] [-p] [-c] [-z] [-h]\n");
    printf("        -d <path> Directory containing proc entries (default: /proc)\n");
    printf("        -p        Display proc entries sorted by pid (default)\n");
    printf("        -c        Display proc entries sorted by command lexicographically\n");
    printf("        -z        Display ONLY proc entries in the zombie state\n");
    printf("        -h        Display this help message\n");
    exit(0);
}

int main (int argc, char * argv[]) {
    //declare variables
    struct dirent **eps;
    int opt;
    int n;

    /* Declare filterFunction pointer */
    int (*filterFunction)(const struct dirent *);
    filterFunction = defaultFilter;

    /* Delcare sortFunction pointer */
    int (*sortFunction)(const struct dirent **, const struct dirent **);
    sortFunction = noSort;

    //Declare procSort function
    int (*procSort)(const void *a, const void *b);
    procSort = pidSort;

    //Delcare proc state filter function
    int (*procEntryFilter)(const ProcEntry *entry);
    procEntryFilter = ProcEntryDefaultFilter;

    /* Declare dirPath and set default to current directory */
    char dirPath[MAX_PATH_LENGTH];
    strcpy(dirPath,"/proc");

    /* Use getopt() to process command line arugments */
    while((opt = getopt(argc, argv, "d:pczh")) != -1) {
        switch(opt) {
            case 'd':
                strncpy(dirPath,optarg,MAX_PATH_LENGTH);
                break;
            case 'p':
                procSort = pidSort;
                break;
            case 'c':
                procSort = comSort;
                break;
            case 'z':
                procEntryFilter = zombieFilter;
                break;
            case 'h': 
                printFunctionality();
                break;
            default:
                fprintf(stderr,"Error: Invalid Option Specified\n");
                fprintf(stderr,"Usage: %s [-d <path>] \n", argv[0]);
                break;
        }
    }

    /* Perfrom the scan dir of the dirPath */
    errno = 0;  
    n = scandir (dirPath, &eps, filterFunction, sortFunction);

    /* validate directory was opened successfully */
    if (n < 0) {
        perror("scandir: ");
        exit(1);
    }

    //Declare an array of ProcEntry* items
    ProcEntry ** myprocs = (ProcEntry **) (malloc(sizeof(ProcEntry *) * n));
    
    //Build full file path to the stat file
    for(int i = 0; i < n; i++) {
        int size = 6 + strlen(dirPath) + strlen(eps[i]->d_name) +1;
        char path[size];
        strcpy(path, dirPath);
        strcat(path, "/");
        strcat(path, eps[i]->d_name);
        strcat(path, "/stat");
        path[size -1] = '\0';
        myprocs[i] = CreateProcEntryFromFile(path);
    }
    //call qsort
    qsort(myprocs, n, sizeof(ProcEntry*), procSort);

    //print header
    fprintf(stdout,"%7s %7s %5s %5s %5s %7s %-25s %-20s\n"
    ,"PID","PPID","STATE","UTIME","STIME","THREADS","CMD","STAT_FILE");

    //print based on filters and functions
    int cnt;
    for (cnt = 0; cnt < n; ++cnt) {
       if(procEntryFilter(myprocs[cnt])) {
           PrintProcEntry(myprocs[cnt]);
       }
    }

    /* Cleaup memory */
    for(int i = 0; i < n; i++) {
        free(eps[i]);
    }
    for(int i = 0; i < n; i++) {
        DestroyProcEntry(myprocs[i]);
    }
    free(eps);
    free(myprocs);
    
    return(0);
}
