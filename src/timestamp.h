//
// Created by feddersen on 10.12.23.
//

#ifndef P2P_FOOD_DONATION_TIME_H
#define P2P_FOOD_DONATION_TIME_H

#endif //P2P_FOOD_DONATION_TIME_H

struct timestamp{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int seconds;
};

struct timestamp timestamp_now();
struct timestamp create_timestamp(int second, int minute, int hour, int day, int month, int year);
void print_timestamp(struct timestamp timestamp);
int cmp_timestamp(struct timestamp t1, struct timestamp t2);
struct timestamp timestamp_delta(int delta);