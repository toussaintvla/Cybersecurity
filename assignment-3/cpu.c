#include "oslabs.h"
#include <stdio.h>

// int main(int argc, char*argv[]){
//     struct PCB ready_queue[10];
//     int queue_cnt = 3;
//     struct PCB current_process = {
//         .process_id = 1,
//         .arrival_timestamp = 1,
//         .total_bursttime = 4,
//         .execution_starttime = 1,
//         .execution_endtime = 5,
//         .remaining_bursttime = 4,
//         .process_priority = 8
//     };
//     struct PCB new_process = {
//         .process_id = 2,
//         .arrival_timestamp = 2,
//         .total_bursttime = 3,
//         .execution_starttime = 0,
//         .execution_endtime = 0,
//         .remaining_bursttime = 3,
//         .process_priority = 6
//     };

//     struct PCB res = handle_process_arrival_pp(ready_queue, &queue_cnt, current_process, new_process, 2);
//     printf("%d\n", ready_queue[0].process_id);
//     printf("%d\n", ready_queue[0].arrival_timestamp);
//     printf("%d\n", ready_queue[0].total_bursttime);
//     printf("%d\n", ready_queue[0].execution_starttime);
//     printf("%d\n", ready_queue[0].execution_endtime);
//     printf("%d\n", ready_queue[0].remaining_bursttime);
//     printf("%d\n", ready_queue[0].process_priority);
//     printf("%d\n", queue_cnt);
//     printf("%d\n", res.process_id);
//     printf("%d\n", res.arrival_timestamp);
//     printf("%d\n", res.total_bursttime);
//     printf("%d\n", res.execution_starttime);
//     printf("%d\n", res.execution_endtime);
//     printf("%d\n", res.remaining_bursttime);
//     printf("%d\n", res.process_priority);

//     ready_queue[0].process_id = 1;
//     ready_queue[0].arrival_timestamp = 1;
//     ready_queue[0].total_bursttime =4;
//     ready_queue[0].execution_starttime = 0;
//     ready_queue[0].execution_endtime = 0;
//     ready_queue[0].remaining_bursttime = 4;
//     ready_queue[0].process_priority = 23;

//     ready_queue[1].process_id = 2;
//     ready_queue[1].arrival_timestamp = 1;
//     ready_queue[1].total_bursttime = 4;
//     ready_queue[1].execution_starttime = 0;
//     ready_queue[1].execution_endtime = 0;
//     ready_queue[1].remaining_bursttime = 4;
//     ready_queue[1].process_priority = 22;

//     ready_queue[2].process_id = 3;
//     ready_queue[2].arrival_timestamp = 1;
//     ready_queue[2].total_bursttime = 4;
//     ready_queue[2].execution_starttime = 0;
//     ready_queue[2].execution_endtime = 0;
//     ready_queue[2].remaining_bursttime = 4;
//     ready_queue[2].process_priority = 24;

//     struct PCB res1 = handle_process_completion_pp(ready_queue, &queue_cnt, 2);
    
//     for(int i = 0; i < 3; i++){
//         printf("%d\n", ready_queue[i].process_id);
//         printf("%d\n", ready_queue[i].arrival_timestamp);
//         printf("%d\n", ready_queue[i].total_bursttime);
//         printf("%d\n", ready_queue[i].execution_starttime);
//         printf("%d\n", ready_queue[i].execution_endtime);
//         printf("%d\n", ready_queue[i].remaining_bursttime);
//         printf("%d\n", ready_queue[i].process_priority);
//     }

//     return 0;
// }

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{
    current_process.remaining_bursttime -= (timestamp - 1);
    current_process.execution_endtime = 0;

    ready_queue[*queue_cnt] = current_process;

    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = new_process.remaining_bursttime + timestamp;

    *queue_cnt += 1;

    return new_process;
}

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
    if(ready_queue != NULL)
    {
        if(ready_queue[*queue_cnt].process_id > ready_queue[*queue_cnt - 1].process_id)
        {
            *queue_cnt -= 1;
            ready_queue[*queue_cnt].execution_starttime = timestamp;
            ready_queue[*queue_cnt].execution_endtime = ready_queue[*queue_cnt].remaining_bursttime + timestamp;
        }
    }
    
    return ready_queue[*queue_cnt];
}

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{
}

struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum)
{
}