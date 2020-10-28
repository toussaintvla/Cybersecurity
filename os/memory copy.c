#include "oslabs.h"
#include <stdio.h>

struct MEMORY_BLOCK NULLBLOCK = {0,0,0,0}; 

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id)
{
    int temp;
    if(memory_map[*map_cnt].segment_size == request_size){
        return memory_map[*map_cnt];
    }
    else if(memory_map[*map_cnt].segment_size > request_size){
        memory_map[*map_cnt].start_address = 0;
        temp = memory_map[*map_cnt].end_address - request_size;
        memory_map[*map_cnt].end_address -= (temp - 1);  
        memory_map[*map_cnt].segment_size -= (temp - 1);
        memory_map[*map_cnt].process_id = process_id;
    }
    else{
        return NULLBLOCK;
    }
}

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id)
{    
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id)
{
}

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address)
{
}

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt)
{
    
}