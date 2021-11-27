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
    //Validate statFile
    if(statFile == NULL) {
        return NULL;
    }
    //Allocate space for ProcEntry in heap and validate
    ProcEntry * newProcess = (ProcEntry *) malloc(sizeof(ProcEntry));
    if(newProcess == NULL) {
        return NULL;
    }

    return newProcess;
}

void DestroyProcEntry(ProcEntry * entry) {
    //Validate Parameter
    if(entry == NULL) {
        return;
    }

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