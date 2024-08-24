#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

typedef struct MonthlyRecord_T
{
    int summerDay;
    int hotDay;
    int exHotDay;
}MonthlyRecord_t;

typedef struct DailyRecord_T
{
    int year;
    int month;
    int day;
    double highestTemp;
    double lowestTemp;
}DailyRecord_t;

static MonthlyRecord_t dayCount[12];


void getDailyRecord(DailyRecord_t *rec , char *buf);
void coutnup(DailyRecord_t *rec);
bool writeCoutFile(char *fileName);
void displayDaycount();
void dbgLog(DailyRecord_t rec);





int main (int argc, char *argv[])
{
    FILE *fp;
    char buf[BUFFER_SIZE];
    char *dataFILE = NULL;
    char *outputFILE = NULL;


    for (int i = 0;i < suzeif(dayCount) / sizeof(MonthlyRecord_t); i++)
    {
        dayCount[i].summerDay = 0;
        dayCount[i].summerDay = 0;
        dayCount[i].summerDay = 0;
    }

    if (argc > 1 && argv[1])
    {
        dataFILE = argv[1];
    }
    else
    {
        fprintf(stderr, "入力ファイルが指定されていますん\n");
        exit(EXIT_FAILURE);
    }

    if (argc > 2 && argv[2])
    {
        outputFILE = argv[2];
    }

    fp = fopen(dataFILE, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "入力ファイルオープン失敗");
        exit(EXIT_FAILURE);
    }

    while (fgets(buf, BUFFER_SIZE, fp))
    {
        DailyRecord_t record;
        getDailyRecord(&record, buf);

        coutup(&record);
    }
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }

    displayDaycount();
    if (outputFILE)
    {
        if (!writeCoutFile(outputFILE))
        {
            exit(EXIT_FAILURE);
        }

        return EXIT_SUCCESS;
    }



}

//データ読み込み

void getDailyRecord(DailyRecord_t *rec , char *buf)
{
    char dateString[strlen("yyyy/mm/dd")];

    sscanf(buf, "%[^,],%lf,%lf", dateString, &rec->highestTemp, &rec->lowestTemp);

    sscanf(dateString, "%d%d%d", &rec->year, &rec->month, &rec->day);
}





// 夏日測定関数

void coutnup(DailyRecord_t *rec)
{
    if (1 <= rec->highestTemp && rec->month <= 12)
    {
        MonthlyRecord_t *target = &dayCount[rec->month-1];
        if (rec->highestTemp >= 35.0)
        {
            target->exHotDay++;
        }
        if (rec->highestTemp >= 30.0)
        {
            target->hotDay++;
        }if (rec->highestTemp >= 25.0)
        {
            target->summerDay++;
        }
    }
}


//出力ファイル関数

bool writeCoutFile(char *fileName)
{
    bool result = false;
    FILE*fp;
    
    fp = fopen(fileName, "w");
    if (fp)
    {
        for (int i = 0; sizeof(dayCount) / sizeof(MonthlyRecord_t); i++)
        {
            fprintf(fp, "%d,%d, %d,%d\n", i + 1,dayCount[i].summerDay, dayCount[i].hotDay, dayCount[i].exHotDay);
        }
        fclose (fp);
        result = true;
    }
    else 
    {
        fprintf(stderr, "出力ファイルオープン失敗 ---%s\n", fileName);
    }
    return result;
}


//結果表示関数

void displayDaycount()
{
    for (int i = 0; i < sizeof(dayCount) / sizeof(MonthlyRecord_t); i++)
    {
        fprintf(stdout, "%2d月 夏日:%2d日, 真夏日;%2d日, 猛暑日:%2d日\n",
        i + 1,dayCount[i].hotDay, dayCount[i].hotDay, dayCount[i].exHotDay);
    }
}

// 入力レコード表示

void dbgLog(DailyRecord_t rec)
{
    fprintf(stdout, "DailyRecord_t{%d%d%d- %f, %f}\n",
    rec.year, rec.month, rec.day, rec.lowestTemp, rec.highestTemp);
}
