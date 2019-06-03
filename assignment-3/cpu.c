#include "oslabs.h"
#include <stdio.h>

int main(int argc, char*argv[]){
    struct PCB ready_queue[10];
    int queue_cnt = 0;
    struct PCB current_process = {
        .process_id = 1,
        .arrival_timestamp = 1,
        .total_bursttime = 4,
        .execution_starttime = 1,
        .execution_endtime = 5,
        .remaining_bursttime = 4,
        .process_priority = 8
    };
    struct PCB new_process = {
        .process_id = 2,
        .arrival_timestamp = 2,
        .total_bursttime = 3,
        .execution_starttime = 0,
        .execution_endtime = 0,
        .remaining_bursttime = 3,
        .process_priority = 6
    };
    
    struct PCB res = handle_process_arrival_pp(ready_queue, &queue_cnt, current_process, new_process, 2);
    printf("%d\n", ready_queue[0].process_id);
    printf("%d\n", ready_queue[0].arrival_timestamp);
    printf("%d\n", ready_queue[0].total_bursttime);
    printf("%d\n", ready_queue[0].execution_starttime);
    printf("%d\n", ready_queue[0].execution_endtime);
    printf("%d\n", ready_queue[0].remaining_bursttime);
    printf("%d\n", ready_queue[0].process_priority);
    printf("%d\n", queue_cnt);
    printf("%d\n", res.process_id);
    printf("%d\n", res.arrival_timestamp);
    printf("%d\n", res.total_bursttime);
    printf("%d\n", res.execution_starttime);
    printf("%d\n", res.execution_endtime);
    printf("%d\n", res.remaining_bursttime);
    printf("%d\n", res.process_priority);

    return 0;
}