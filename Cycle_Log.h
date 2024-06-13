#ifndef _CYCLE_LOG_H
#define _CYCLE_LOG_H

#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <memory.h>
#include <stdarg.h>
#include <stdbool.h>
#include "syslog.h"

typedef struct _LOG_FILE_INF_STRUCT
{
    FILE *fp;
    int LOG_FILE_MAX_SIZE;
    volatile long long g_offset;
    char *tmp_log_name;
    char *log_name;
} _LOG_FILE_INF;
extern _LOG_FILE_INF LOG_FILE_INF;

void FileInit(char *tmp_filepath, char *filepath, int LOG_FILE_MAX_SIZE);
void FileWriteLog(char* buffer);
void FileWriteLogBytes(char* buffer, size_t len)
void FileClose();

#endif