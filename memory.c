#include "oslabs.h"
#include <stdio.h>

struct MEMORY_BLOCK NULLBLOCK = {0,0,0,0}; 

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id)
{
    if(memory_map[*map_cnt].segment_size == request_size){
        return memory_map[*map_cnt];
    }
    else if(memory_map[*map_cnt].segment_size > request_size){

        memory_map[*map_cnt].segment_size -= request_size;
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