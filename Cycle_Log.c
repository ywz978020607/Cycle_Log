#include "Cycle_Log.h"

_LOG_FILE_INF LOG_FILE_INF;

void FileInit(char *tmp_filepath, char *filepath, int LOG_FILE_MAX_SIZE)
{
    LOG_FILE_INF.tmp_log_name = tmp_filepath;
    LOG_FILE_INF.log_name = filepath;
    LOG_FILE_INF.fp = fopen(LOG_FILE_INF.tmp_log_name, "wr+");
    LOG_FILE_INF.LOG_FILE_MAX_SIZE = LOG_FILE_MAX_SIZE;
    LOG_FILE_INF.g_offset = 0;
}

void FileWriteLog(char* buffer)
{
    // 超过文件最大限制，备份一下原来的log文件
    if (LOG_FILE_INF.g_offset > LOG_FILE_INF.LOG_FILE_MAX_SIZE){
        LOG_FILE_INF.g_offset = 0;
        fseek(LOG_FILE_INF.fp, LOG_FILE_INF.g_offset, SEEK_SET);
    }    // 如果没有超过件最大限制则接着写，超过以后则从文件头开始重新记录
    //      原来的文件从文件头开始重新记录覆盖  open的时候记得选w+
    fseek(LOG_FILE_INF.fp, LOG_FILE_INF.g_offset, SEEK_SET);
    fwrite(buffer, 1, strlen(buffer), LOG_FILE_INF.fp);
    LOG_FILE_INF.g_offset += strlen(buffer);

    fflush(LOG_FILE_INF.fp);
}

void FileWritePacket(uint8_t* PacketBaseAddr, int Length)
{
    // write(USB_Inf.File_fd, PacketBaseAddr, Length);
}

void FileClose()
{
    FILE *fpbak = fopen(LOG_FILE_INF.log_name, "w+");
    char ch;
    fseek(fpbak, 0, SEEK_SET);
    bool after_start = false;
    while ((ch=fgetc(LOG_FILE_INF.fp))!=EOF) {
        if(after_start == false){
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