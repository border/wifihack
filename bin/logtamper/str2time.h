#ifndef STR2TIME_H
#define STR2TIME_H

#include <string.h>
#include <time.h>
/* converts from "YYYY:MM:DD:hh:mm:ss:uuuuuu" to struct timeval */
time_t str2time(const char *s);


#endif

