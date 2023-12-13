//
// Created by feddersen on 10.12.23.
//

#include "timestamp.h"
#include <time.h>
#include <stdio.h>

#define ENTRIES_IN_TIMESTAMP 6

struct timestamp timestamp_delta(int delta){
    time_t t = time(NULL);
    t += delta;
    struct tm* tm = localtime(&t);
    return create_timestamp(tm->tm_sec, tm->tm_min, tm->tm_hour, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
}

struct timestamp timestamp_now(){
    return timestamp_delta(0);
}

struct timestamp create_timestamp(int second, int minute, int hour, int day, int month, int year){
    struct timestamp t = {year, month, day, hour, minute, second};
    return t;
}

void print_timestamp(struct timestamp timestamp){
    printf("%02d:%02d:%02d %02d/%02d/%04d", timestamp.hour, timestamp.minute, timestamp.seconds, timestamp.day, timestamp.month, timestamp.year);
}

/**
 * cmp_timestamp returns 1 if the first parameter is later than the second, -1 if the second is later and 0 if they are the same
 */
int cmp_timestamp(struct timestamp t1, struct timestamp t2){

    int t1_data[ENTRIES_IN_TIMESTAMP] = {t1.year, t1.month, t1.day, t1.hour, t1.minute, t1.seconds};
    int t2_data[ENTRIES_IN_TIMESTAMP] = {t2.year, t2.month, t2.day, t2.hour, t2.minute, t2.seconds};

    for (int i = 0; i < ENTRIES_IN_TIMESTAMP; ++i) {
        if (t1_data[i] > t2_data[i]){
            return 1;
        } else if (t1_data[i] < t2_data[i]){
            return -1;
        }
    }
    return 0;
}
