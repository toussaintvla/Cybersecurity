#include "oslabs.h"

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