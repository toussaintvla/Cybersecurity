#include "oslabs.h"
#include "stdbool.h"
#include <stdio.h>


struct PCB NULLPCB = {0, 0, 0, 0, 0, 0, 0};

bool compare(struct PCB a, struct PCB b){
    return ((a.process_id == b.process_id) && 
            (a.arrival_timestamp == b.arrival_timestamp) && 
            (a.total_bursttime == b.total_bursttime) && 
            (a.execution_starttime == b.execution_starttime) && 
            (a.execution_endtime == b.execution_endtime) && 
            (a.remaining_bursttime == b.remaining_bursttime) && 
            (a.process_priority == b.process_priority));
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{   
    if(compare(current_process, NULLPCB)){
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = new_process.total_bursttime + timestamp;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }
    else if(new_process.process_priority >= current_process.process_priority){
        new_process.execution_starttime = new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[(*queue_cnt)++] = new_process;
        return current_process;
    }
    else{ 
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = new_process.total_bursttime + timestamp;
        new_process.remaining_bursttime = new_process.total_bursttime;

        current_process.execution_endtime = 0;
        current_process.remaining_bursttime = current_process.total_bursttime;
        ready_queue[(*queue_cnt)++] = current_process;
        return new_process;
    } 
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

    for (c = ppValue; c < *queue_cnt; c++)
        (c == *queue_cnt - 1) ? (ready_queue[c] = NULLPCB) : (ready_queue[c] = ready_queue[c + 1]);

    (*queue_cnt)--;
    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = new_process.remaining_bursttime + timestamp;
    
    return new_process;  
}

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp)
{
     if(compare(current_process, NULLPCB)){
        new_process.execution_starttime = time_stamp;
        new_process.execution_endtime = new_process.total_bursttime + time_stamp;
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }
    else if(new_process.total_bursttime <= current_process.total_bursttime){
        new_process.execution_starttime = time_stamp;
        new_process.execution_endtime = new_process.total_bursttime + time_stamp;
        new_process.remaining_bursttime = new_process.total_bursttime;

        current_process.execution_starttime = current_process.execution_endtime = 0;
        current_process.remaining_bursttime = current_process.total_bursttime;
        ready_queue[(*queue_cnt)++] = current_process;
        return new_process; 
    }
    else{
        new_process.execution_starttime = new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[(*queue_cnt)++] = new_process;
        return current_process;
    }
    

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

    for (c = srtpValue; c < *queue_cnt; c++)
        (c == *queue_cnt - 1) ? (ready_queue[c] = NULLPCB) : (ready_queue[c] = ready_queue[c + 1]);
    
    (*queue_cnt)--;
    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = new_process.remaining_bursttime + timestamp;

    return new_process;  
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{
    if (compare(current_process, NULLPCB)){
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + MIN(new_process.total_bursttime, time_quantum);
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }
        new_process.execution_starttime = new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[(*queue_cnt)++] = new_process;
        return current_process;
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

    for (c = rrValue; c < *queue_cnt; c++)
        (c == *queue_cnt - 1) ? (ready_queue[c] = NULLPCB) : (ready_queue[c] = ready_queue[c + 1]);

    (*queue_cnt)--;
    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = MIN(new_process.remaining_bursttime, time_quantum) + timestamp;

    return new_process;  
}
