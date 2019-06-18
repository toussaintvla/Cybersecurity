#include "oslabs.h"
#include "stdbool.h"
#include <stdio.h>

// int main(int argc, char*argv[])
// {
//     struct PCB ready_queue[10];
//     int queue_cnt = 3;
    // struct PCB current_process = {
    //     .process_id = 1,
    //     .arrival_timestamp = 1,
    //     .total_bursttime = 8,
    //     .execution_starttime = 1,
    //     .execution_endtime = 9,
    //     .remaining_bursttime = 8,
    //     .process_priority = 0
    // };
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

struct PCB NULLPCB = {0, 0, 0, 0, 0, 0, 0};

bool compareStruct(struct PCB a, struct PCB b){
    return (
        (a.process_id == b.process_id) && 
        (a.arrival_timestamp == b.arrival_timestamp) && 
        (a.total_bursttime == b.total_bursttime) && 
        (a.execution_starttime == b.execution_starttime) && 
        (a.execution_endtime == b.execution_endtime) && 
        (a.remaining_bursttime == b.remaining_bursttime) && 
        (a.process_priority == b.process_priority)
        );
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{   
    if(new_process.process_priority <= current_process.process_priority)
    {
        current_process.execution_endtime = 0;
        current_process.remaining_bursttime -= (timestamp - 1);
        ready_queue[*queue_cnt] = current_process;

        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = new_process.total_bursttime + timestamp;
        new_process.remaining_bursttime = new_process.total_bursttime;
    } 

    (*queue_cnt)++;

    return new_process;     
}

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
    int ppComparison, ppValue, c;

    if ((*queue_cnt) == 0) return NULLPCB;

    ppComparison = ready_queue[0].process_priority;
    ppValue = 0;

    for (int i = 1; i < *queue_cnt; i++)
        if (ready_queue[i].process_priority < ppComparison)
        {
            ppComparison = ready_queue[i].process_priority;
            ppValue = i;
        }

    struct PCB new_process = ready_queue[ppValue];

    //remove PCB from ready queue
    for (c = ppValue; c < *queue_cnt; c++)
        (c == *queue_cnt - 1) ? (ready_queue[c] = NULLPCB) : (ready_queue[c] = ready_queue[c + 1]);

    (*queue_cnt)--;
    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = new_process.remaining_bursttime + timestamp;
    
    return new_process;  
}

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{
    if(new_process.total_bursttime <= current_process.total_bursttime)
    {
        current_process.remaining_bursttime -= (time_stamp - 1);
        current_process.execution_starttime = time_stamp - 2;
        current_process.execution_endtime = 0;

        ready_queue[*queue_cnt] = current_process;

        new_process.execution_starttime = time_stamp;
        new_process.execution_endtime = new_process.total_bursttime + time_stamp;
        new_process.remaining_bursttime = new_process.total_bursttime;
    }

    *queue_cnt += 1;

    return new_process;
}

struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)
{
    int srtpComparison, srtpValue, c;

    if ((*queue_cnt) == 0) return NULLPCB;

    srtpComparison = ready_queue[0].remaining_bursttime;
    srtpValue = 0;

    for (int i = 1; i < *queue_cnt; i++)
        if (ready_queue[i].remaining_bursttime < srtpComparison)
        {
            srtpComparison = ready_queue[i].remaining_bursttime;
            srtpValue = i;
        }

    struct PCB new_process = ready_queue[srtpValue];

    //remove the PCB from Ready Queue
    for (c = srtpValue; c < *queue_cnt; c++)
        (c == *queue_cnt - 1) ? (ready_queue[c] = NULLPCB) : (ready_queue[c] = ready_queue[c + 1]);
    
    (*queue_cnt)--;
    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = new_process.remaining_bursttime + timestamp;

    return new_process;  
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{
    if(new_process.total_bursttime <= current_process.total_bursttime)
    {
        current_process.execution_endtime = 0;
        current_process.remaining_bursttime -= (timestamp - 1);
        current_process.execution_endtime = 0;

        ready_queue[*queue_cnt] = current_process;

        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = new_process.total_bursttime + timestamp + MIN(new_process.remaining_bursttime,time_quantum);
        new_process.remaining_bursttime = new_process.total_bursttime;
    }

    (*queue_cnt)++;

    return new_process;
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum)
{
    int rrComparison, rrValue, c;

    if ((*queue_cnt) == 0) return NULLPCB;

    rrComparison = ready_queue[0].arrival_timestamp;
    rrValue = 0;

    for (int i = 1; i < *queue_cnt; i++)
        if (ready_queue[i].arrival_timestamp < rrComparison)
        {
            rrComparison = ready_queue[i].arrival_timestamp;
            rrValue = i;
        }

    struct PCB new_process = ready_queue[rrValue];

    //remove the PCB from Ready Queue
    for (c = rrValue; c < *queue_cnt; c++)
        (c == *queue_cnt - 1) ? (ready_queue[c] = NULLPCB) : (ready_queue[c] = ready_queue[c + 1]);

    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = MIN(new_process.remaining_bursttime, time_quantum) + timestamp;
    
    (*queue_cnt)--;

    return new_process;  
}