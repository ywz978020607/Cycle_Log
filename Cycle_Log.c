#include "Cycle_Log.h"

_LOG_FILE_INF LOG_FILE_INF;

void FileInit(char *tmp_filepath, char *filepath, int LOG_FILE_MAX_SIZE)
{
    LOG_FILE_INF.tmp_log_name = tmp_filepath;
    LOG_FILE_INF.log_name = filepath;
    LOG_FILE_INF.fp = fopen(LOG_FILE_INF.tmp_log_name, "wb+");
    LOG_FILE_INF.LOG_FILE_MAX_SIZE = LOG_FILE_MAX_SIZE;
    LOG_FILE_INF.g_offset = 0;
}

void FileWriteLog(char* buffer)
{
    if (LOG_FILE_INF.g_offset > LOG_FILE_INF.LOG_FILE_MAX_SIZE){
        LOG_FILE_INF.g_offset = 0;
        fseek(LOG_FILE_INF.fp, LOG_FILE_INF.g_offset, SEEK_SET);
    }
    // fseek(LOG_FILE_INF.fp, LOG_FILE_INF.g_offset, SEEK_SET);
    fwrite(buffer, 1, strlen(buffer), LOG_FILE_INF.fp);
    LOG_FILE_INF.g_offset += strlen(buffer);

    fflush(LOG_FILE_INF.fp);
}

void FileWriteLogBytes(char* buffer, size_t len)
{
    if (LOG_FILE_INF.g_offset > LOG_FILE_INF.LOG_FILE_MAX_SIZE){
        LOG_FILE_INF.g_offset = 0;
        fseek(LOG_FILE_INF.fp, LOG_FILE_INF.g_offset, SEEK_SET);
    }
    // fseek(LOG_FILE_INF.fp, LOG_FILE_INF.g_offset, SEEK_SET);
    fwrite(buffer, 1, len, LOG_FILE_INF.fp);
    LOG_FILE_INF.g_offset += len;

    fflush(LOG_FILE_INF.fp);
}

void FileClose()
{
    FILE *fpbak = fopen(LOG_FILE_INF.log_name, "wb+");
    int ch; // 当纯文本类型时，char型足够；当二进制写入时，由于存在0xFF，导致fgetc死循环，故改成int型。
    fseek(fpbak, 0, SEEK_SET);
    bool after_start = false;
    while ((ch=fgetc(LOG_FILE_INF.fp))!=EOF) {
        // 注意！！
        // if(after_start == false){ // 当文本型日志使用，以换行进行区分，取下行开始调序
        if(false){  // 当二进制日志使用，无换行分割，无脑切割调序
            if(ch=='\n')
                after_start = true;
        }
        else{
            fputc(ch,fpbak);
        }
    }
    fseek(LOG_FILE_INF.fp, 0, SEEK_SET);
    while (LOG_FILE_INF.g_offset>0) {
        ch=fgetc(LOG_FILE_INF.fp);
        fputc(ch,fpbak);
        --LOG_FILE_INF.g_offset;
    }

    fclose(LOG_FILE_INF.fp);
    fclose(fpbak);

    remove(LOG_FILE_INF.tmp_log_name);
}