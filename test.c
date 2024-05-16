#include <stdio.h>
#include "Cycle_Log.c"

void test_log(const char *format, ...)
{
    long long time_total;
    int done;
    char ch;
    char wzlog[256];
    char buffer[1024];

    // 格式化系统时间、日志内容
    va_list arg;
    va_start(arg, format);
    vsprintf(wzlog, format, arg);

    time_t time_log = time(NULL);
    struct tm* tm_log = localtime(&time_log);
    time_total = clock();

    snprintf(buffer, 1024, "%04d-%02d-%02d %02d:%02d:%02d %012lld %s",
                            tm_log->tm_year+1900, tm_log->tm_mon+1, tm_log->tm_mday,
                            tm_log->tm_hour, tm_log->tm_min, tm_log->tm_sec,
                            time_total, wzlog);

    // 调用写入
    FileWriteLog(buffer);
}

int main(){
    FileInit("tmp.log", "out.log", 200*1024);
    for(int i=1; i<4000; i++) {
        test_log("log test %09d\n", i);
        //usleep(2);
    }
    test_log("1\n");

    FileClose();
    return 0;
}
