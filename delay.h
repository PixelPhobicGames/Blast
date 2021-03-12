#include <time.h>

void delay(float number_of_seconds) 
{  
    int milli_seconds = 1 * number_of_seconds; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds) 
        ; 
}