/* File: ProcEntry.c
 * Author: Eric Melin
 * Date: Fri 26 Nov 2021 06:17:00 PM PST
 * Description: Struct and functions for working with ProcEntry data
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ProcEntry.h"

#define MAX_LENGTH 4096

ProcEntry * CreateProcEntry(void) {
    //Allocate space for ProcEntry in heap and validate
    ProcEntry * newProcess = (ProcEntry *) malloc(sizeof(ProcEntry));
    if(newProcess == NULL) {
        return NULL;
    }

    return newProcess;
}

/*  
The command field (comm) and path field 
will be allocated on the heap using malloc.
*/
ProcEntry * CreateProcEntryFromFile(const char statFile[]) {
    //Create Variables
    char * dummy = NULL; //holder
    int process_id; //1
    char *comm = NULL; //2
    char state; //3
    int ppid; //4
    unsigned long int utime; //14
    unsigned long int stime; //15
    long number_threads; //20

    //Validate statFile
    if(statFile == NULL) {
        return NULL;
    }

    FILE * fp = fopen(statFile, "r");

    if(fp == NULL) {
        fprintf(stderr, "Stat file couldn't open.\n");
        return NULL;  
    } else {
        fscanf(fp, "%d %s %c %d %s %s %s %s %s %s %s %s %s %lu %lu %s %s %s %s %ld", 
        &process_id, comm, &state, &ppid, dummy, dummy, dummy, dummy, dummy, dummy, dummy, 
        dummy, dummy, &utime, &stime, dummy, dummy, dummy, dummy, &number_threads);
    }

    //Allocate space for ProcEntry in heap and validate
    ProcEntry * newProcess = CreateProcEntry();
    if(newProcess == NULL) {
        fprintf(stderr, "Couldn't file new ProcEntry.\n");
        return NULL;
    }
    
    newProcess->process_id = process_id;
    newProcess->comm = (char*) malloc(strlen(comm) + 1);        //Allocating space for string
    strncpy(newProcess->comm, comm, MAX_LENGTH);
    newProcess->state = state;
    newProcess->parent_process_id = ppid;
    newProcess->utime = utime;
    newProcess->stime = stime;
    newProcess->number_of_threads = number_threads;

    return newProcess;
}

void DestroyProcEntry(ProcEntry * entry) {
    //Validate Parameter
    if(entry == NULL) {
        return;
    }

    free(entry->comm);
    free(entry);
}

void PrintProcEntry(ProcEntry *entry)
{
     unsigned long int utime = entry->utime / sysconf(_SC_CLK_TCK);
     unsigned long int stime = entry->stime / sysconf(_SC_CLK_TCK);
     fprintf(stdout, "%7d %7d %5c %5lu %5lu %7ld %-25s %-20s\n",
             entry->process_id,
             entry->parent_process_id,
             entry->state,
             utime,
             stime,
             entry->number_of_threads,
             entry->comm,
             entry->path);
}