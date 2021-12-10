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
    
    //set fields to 0 or NULL
    newProcess->process_id = 0;
    newProcess->parent_process_id = 0;
    newProcess->comm = NULL;
    newProcess->state = 0;
    newProcess->utime = 0;
    newProcess->stime = 0;
    newProcess->number_of_threads = 0;
    newProcess->path = NULL;

    if(newProcess == NULL) {
        return NULL;
    }

    return newProcess;
}

ProcEntry * CreateProcEntryFromFile(const char statFile[]) {
    //Create Variables
    int numRead;
    int process_id; //1
    char comm[255]; //2
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
    //Allocate space for ProcEntry in heap and validate
    ProcEntry * newProcess = CreateProcEntry();
    if(newProcess == NULL) {
        fprintf(stderr, "Couldn't file new ProcEntry.\n");
        return NULL;
    }

    newProcess->comm = (char*) malloc(255);                         //Allocating space for string
    newProcess->path = (char*) malloc(strlen(statFile) + 1);        //Allocate space for path

    if(fp == NULL) {
        fprintf(stderr, "Stat file couldn't open.\n");
        DestroyProcEntry(newProcess);
        return NULL;  
    } else {
        numRead = fscanf(fp, "%d %s %c %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %ld", 
        &process_id, comm, &state, &ppid, &utime, &stime, &number_threads);
    }
    
    //checking for scanf errors
    if(numRead != 7) {
        printf("Scanf Error");
        DestroyProcEntry(newProcess);
        return NULL;
    }

    newProcess->process_id = process_id;
    strncpy(newProcess->path, statFile, strlen(statFile) + 1);
    strncpy(newProcess->comm, comm, 255);
    newProcess->state = state;
    newProcess->parent_process_id = ppid;
    newProcess->utime = utime;
    newProcess->stime = stime;
    newProcess->number_of_threads = number_threads;
    fclose(fp);

    return newProcess;
}

void DestroyProcEntry(ProcEntry * entry) {
    //Validate Parameter
    if(entry == NULL) {
        return;
    }

    free(entry->comm);
    free(entry->path);
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