#include "oslabs.h"
#include <stdio.h>

// int main(int argc, char*argv[])
// {
//     struct PCB ready_queue[10];
//     int queue_cnt = 3;
// //     // struct PCB current_process = {
// //     //     .process_id = 1,
// //     //     .arrival_timestamp = 1,
// //     //     .total_bursttime = 8,
// //     //     .execution_starttime = 1,
// //     //     .execution_endtime = 9,
// //     //     .remaining_bursttime = 8,
// //     //     .process_priority = 0
// //     // };
// //     // struct PCB new_process = {
// //     //     .process_id = 2,
// //     //     .arrival_timestamp = 2,
// //     //     .total_bursttime = 6,
// //     //     .execution_starttime = 0,
// //     //     .execution_endtime = 0,
// //     //     .remaining_bursttime = 6,
// //     //     .process_priority = 0
// //     // };

// //     // struct PCB res = handle_process_arrival_pp(ready_queue, &queue_cnt, current_process, new_process, 2);
// //     // printf("%d\n", ready_queue[0].process_id);
// //     // printf("%d\n", ready_queue[0].arrival_timestamp);
// //     // printf("%d\n", ready_queue[0].total_bursttime);
// //     // printf("%d\n", ready_queue[0].execution_starttime);
// //     // printf("%d\n", ready_queue[0].execution_endtime);
// //     // printf("%d\n", ready_queue[0].remaining_bursttime);
// //     // printf("%d\n", ready_queue[0].process_priority);
// //     // printf("%d\n", queue_cnt);
// //     // printf("%d\n", res.process_id);
// //     // printf("%d\n", res.arrival_timestamp);
// //     // printf("%d\n", res.total_bursttime);
// //     // printf("%d\n", res.execution_starttime);
// //     // printf("%d\n", res.execution_endtime);
// //     // printf("%d\n", res.remaining_bursttime);
// //     // printf("%d\n", res.process_priority);

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
    
//     for(int i = 0; i < 3; i++)
//     {
//         printf("%d\n", ready_queue[i].process_id);
//         printf("%d\n", ready_queue[i].arrival_timestamp);
//         printf("%d\n", ready_queue[i].total_bursttime);
//         printf("%d\n", ready_queue[i].execution_starttime);
//         printf("%d\n", ready_queue[i].execution_endtime);
//         printf("%d\n", ready_queue[i].remaining_bursttime);
//         printf("%d\n", ready_queue[i].process_priority);
//         printf("%d\n\n", queue_cnt);
//     }

//     return 0;
// }

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{
    if(new_process.process_priority < current_process.process_priority)
    {
        current_process.remaining_bursttime -= (timestamp - 1);
        current_process.execution_endtime = 0;

        ready_queue[*queue_cnt] = current_process;

        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = new_process.total_bursttime + timestamp;
        new_process.remaining_bursttime = new_process.total_bursttime;

        *queue_cnt += 1;
    }

    return new_process;
}

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
    int temp, i, j;
    if(ready_queue != NULL)
    {
        if(ready_queue[*queue_cnt - 1].process_priority > ready_queue[*queue_cnt - 2].process_priority)
        {   
            int t1 = ready_queue[*queue_cnt - 2].process_id;
            int t2 = ready_queue[*queue_cnt - 2].arrival_timestamp;
            int t3 = ready_queue[*queue_cnt - 2].total_bursttime;
            int t4 = ready_queue[*queue_cnt - 2].execution_starttime;
            int t5 = ready_queue[*queue_cnt - 2].execution_endtime;
            int t6 = ready_queue[*queue_cnt - 2].remaining_bursttime;
            int t7 = ready_queue[*queue_cnt - 2].process_priority;

            ready_queue[*queue_cnt - 2].process_id = ready_queue[*queue_cnt - 1].process_id;
            ready_queue[*queue_cnt - 2].arrival_timestamp = ready_queue[*queue_cnt - 1].arrival_timestamp;
            ready_queue[*queue_cnt - 2].total_bursttime = ready_queue[*queue_cnt - 1].total_bursttime;
            ready_queue[*queue_cnt - 2].execution_starttime = ready_queue[*queue_cnt - 1].execution_starttime;
            ready_queue[*queue_cnt - 2].execution_endtime = ready_queue[*queue_cnt - 1].execution_endtime;
            ready_queue[*queue_cnt - 2].remaining_bursttime = ready_queue[*queue_cnt - 1].remaining_bursttime;
            ready_queue[*queue_cnt - 2].process_priority = ready_queue[*queue_cnt - 1].process_priority;

            ready_queue[*queue_cnt - 1].process_id = t1;
            ready_queue[*queue_cnt - 1].arrival_timestamp = t2;
            ready_queue[*queue_cnt - 1].total_bursttime = t3;
            ready_queue[*queue_cnt - 1].execution_starttime = t4;
            ready_queue[*queue_cnt - 1].execution_endtime = t5;
            ready_queue[*queue_cnt - 1].remaining_bursttime = t6;
            ready_queue[*queue_cnt - 1].process_priority = t7;
            
            ready_queue[*queue_cnt - 1].execution_starttime = timestamp;
            ready_queue[*queue_cnt - 1].execution_endtime = ready_queue[*queue_cnt - 1].remaining_bursttime + timestamp;
            *queue_cnt -= 1;
        }
    }
    else
    {
    }
    
    return ready_queue[*queue_cnt];
}

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{
    if(new_process.total_bursttime < current_process.total_bursttime)
    {
        current_process.remaining_bursttime -= (time_stamp - 1);
        current_process.execution_starttime = time_stamp - 2;
        current_process.execution_endtime = 0;

        ready_queue[*queue_cnt] = current_process;

        new_process.execution_starttime = time_stamp;
        new_process.execution_endtime = new_process.total_bursttime + time_stamp;
        new_process.remaining_bursttime = new_process.total_bursttime;
        
        *queue_cnt += 1;
    }

    return new_process;
}

struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{
 
    current_process.remaining_bursttime -= (timestamp - 1);
    current_process.execution_starttime = timestamp - 2;
    current_process.execution_endtime = 0;

    ready_queue[*queue_cnt] = current_process;

    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = new_process.total_bursttime + timestamp + time_quantum;
    new_process.remaining_bursttime = new_process.total_bursttime;
    
    *queue_cnt += 1;

    return current_process;
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum)
{
}