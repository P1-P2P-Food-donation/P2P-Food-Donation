//
// Created by feddersen on 10.12.23.
//

#include "timestamp.h"
#include <time.h>
#include <stdio.h>

#define ENTRIES_IN_TIMESTAMP 6

/**
 * This function is used to get a timestamp that is a certain number of seconds from the current time.
 * It adds the specified number of seconds to the current time and returns the resulting timestamp.
 *
 * @param delta The number of seconds to add to the current time.
 * @return Returns a timestamp that is delta seconds from the current time.
 */
struct timestamp timestamp_delta(int delta){
    time_t t = time(NULL);
    t += delta;
    struct tm* tm = localtime(&t);
    return create_timestamp(tm->tm_sec, tm->tm_min, tm->tm_hour, tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
}

/**
 * This function is used to get the current timestamp.
 * It calls the timestamp_delta function with a delta of 0, which returns the current time.
 *
 * @return Returns the current timestamp.
 */
struct timestamp timestamp_now(){
    return timestamp_delta(0);
}

/**
 * This function is used to create a timestamp.
 * It takes in the second, minute, hour, day, month, and year and creates a timestamp struct with these values.
 *
 * @param second The second of the timestamp.
 * @param minute The minute of the timestamp.
 * @param hour The hour of the timestamp.
 * @param day The day of the timestamp.
 * @param month The month of the timestamp.
 * @param year The year of the timestamp.
 * @return Returns a timestamp struct with the specified values.
 */
struct timestamp create_timestamp(int second, int minute, int hour, int day, int month, int year){
    struct timestamp t = {year, month, day, hour, minute, second};
    return t;
}

/**
 * This function is used to print a timestamp.
 * It takes in a timestamp and prints it in the format "HH:MM:SS DD/MM/YYYY".
 *
 * @param timestamp The timestamp to be printed.
 */
void print_timestamp(struct timestamp timestamp){
    printf("%02d:%02d:%02d %02d/%02d/%04d", timestamp.hour, timestamp.minute, timestamp.seconds, timestamp.day, timestamp.month, timestamp.year);
}

/**
 * This function is used to compare two timestamps.
 * It compares the year, month, day, hour, minute, and second of the two timestamps in that order.
 * If the first timestamp is later, it returns 1.
 * If the second timestamp is later, it returns -1.
 * If the two timestamps are the same, it returns 0.
 *
 * @param t1 The first timestamp to be compared.
 * @param t2 The second timestamp to be compared.
 * @return Returns 1 if the first timestamp is later, -1 if the second timestamp is later, and 0 if the two timestamps are the same.
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
