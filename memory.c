#include "oslabs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {
    
    struct MEMORY_BLOCK temp_memory_block, allocated_memory;
    allocated_memory.end_address = 0;
    allocated_memory.start_address = 0;
    allocated_memory.process_id = 0;
    allocated_memory.segment_size = 0;
    bool match = false;
    int memory_map_index = 0 , best_fit_segmant = 0;
    for (int i = 0; i <= *map_cnt - 1; i++) { //finding best fit
        if (request_size == memory_map[i].segment_size) { //perfect match, save memory index and then break
            match = true;
            memory_map_index = i;
            best_fit_segmant = request_size;
            break;
        }
        else if ((memory_map[i].segment_size > request_size) && (memory_map[i].process_id == 0)) { // good match, keep looking for best match
            if (match == false){ //first match
                match = true;
                memory_map_index = i;
                best_fit_segmant = memory_map[i].segment_size;
            }
            else { //found a better match than before
                if (best_fit_segmant > memory_map[i].segment_size){
                    memory_map_index = i;
                    best_fit_segmant = memory_map[i].segment_size;
                }
            }
            
        }
    }
    if (match == true){ //found match, now swap
        temp_memory_block = memory_map[memory_map_index];
        allocated_memory.start_address = temp_memory_block.start_address;
        allocated_memory.end_address = allocated_memory.start_address + request_size - 1;
        allocated_memory.process_id = process_id;
        allocated_memory.segment_size = request_size;
        *map_cnt = *map_cnt + 1;
        
        for (int i = memory_map_index; i <= *map_cnt; i++){
            memory_map[memory_map_index+1] = memory_map[i];
        }
        memory_map[memory_map_index+1].start_address = allocated_memory.end_address + 1;
        memory_map[memory_map_index+1].end_address = memory_map[memory_map_index].end_address;
        memory_map[memory_map_index+1].process_id = memory_map[memory_map_index].process_id;
        memory_map[memory_map_index+1].segment_size = memory_map[memory_map_index].segment_size - request_size;
        memory_map[memory_map_index] = allocated_memory;
    }
    return allocated_memory;
}

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {
    
    struct MEMORY_BLOCK temp_memory_block, allocated_memory;
    allocated_memory.end_address = 0;
    allocated_memory.start_address = 0;
    allocated_memory.process_id = 0;
    allocated_memory.segment_size = 0;
    bool match = false;
    int memory_map_index = 0 , best_fit_segmant = 0;
    for (int i = 0; i <= *map_cnt - 1; i++) { //finding best fit
        if (request_size <= memory_map[i].segment_size) { //perfect match, save memory index and then break
            match = true;
            memory_map_index = i;
            best_fit_segmant = request_size;
            break;
        }
    }
    if (match == true){ //found match, now swap
        temp_memory_block = memory_map[memory_map_index];
        allocated_memory.start_address = temp_memory_block.start_address;
        allocated_memory.end_address = allocated_memory.start_address + request_size - 1;
        allocated_memory.process_id = process_id;
        allocated_memory.segment_size = request_size;
        *map_cnt = *map_cnt + 1;
        
        for (int i = memory_map_index; i <= *map_cnt; i++){
            memory_map[memory_map_index+1] = memory_map[i];
        }
        memory_map[memory_map_index+1].start_address = allocated_memory.end_address + 1;
        memory_map[memory_map_index+1].end_address = memory_map[memory_map_index].end_address;
        memory_map[memory_map_index+1].process_id = memory_map[memory_map_index].process_id;
        memory_map[memory_map_index+1].segment_size = memory_map[memory_map_index].segment_size - request_size;
        memory_map[memory_map_index] = allocated_memory;
    }
    return allocated_memory;
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {
    
    struct MEMORY_BLOCK temp_memory_block, allocated_memory;
    allocated_memory.end_address = 0;
    allocated_memory.start_address = 0;
    allocated_memory.process_id = 0;
    allocated_memory.segment_size = 0;
    bool match = false;
    int memory_map_index = 0 , worst_fit_segmant = 0;
    for (int i = 0; i <= *map_cnt - 1; i++) { //finding worst fit
        if ((memory_map[i].segment_size >= request_size) && (memory_map[i].process_id == 0)) { // good match, keep looking for best match
            if (match == false){ //first match
                match = true;
                memory_map_index = i;
                worst_fit_segmant = memory_map[i].segment_size;
            }
            else { //found a worst match than before
                if (worst_fit_segmant < memory_map[i].segment_size){
                    memory_map_index = i;
                    worst_fit_segmant = memory_map[i].segment_size;
                }
            }
            
        }
    }
    if (match == true){ //found match, now swap
        temp_memory_block = memory_map[memory_map_index];
        allocated_memory.start_address = temp_memory_block.start_address;
        allocated_memory.end_address = allocated_memory.start_address + request_size - 1;
        allocated_memory.process_id = process_id;
        allocated_memory.segment_size = request_size;
        *map_cnt = *map_cnt + 1;
        
        for (int i = memory_map_index; i <= *map_cnt; i++){
            memory_map[memory_map_index+1] = memory_map[i];
        }
        memory_map[memory_map_index+1].start_address = allocated_memory.end_address + 1;
        memory_map[memory_map_index+1].end_address = memory_map[memory_map_index].end_address;
        memory_map[memory_map_index+1].process_id = memory_map[memory_map_index].process_id;
        memory_map[memory_map_index+1].segment_size = memory_map[memory_map_index].segment_size - request_size;
        memory_map[memory_map_index] = allocated_memory;
    }
    return allocated_memory;
}

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address) {
    
    struct MEMORY_BLOCK temp_memory_block, allocated_memory;
    allocated_memory.end_address = 0;
    allocated_memory.start_address = 0;
    allocated_memory.process_id = 0;
    allocated_memory.segment_size = 0;
    bool match = false;
    int memory_map_index = 0 , best_fit_segmant = 0;
    int index = 0;
    for (int i = last_address; i <= *map_cnt+ last_address - 1; i++) { //finding next fit
        if (i >= *map_cnt){
            index = i - *map_cnt;
        }
        else
            index = i;
        if ((request_size <= memory_map[index].segment_size) && (memory_map[i].process_id == 0)){ // match, save memory index and then break
            match = true;
            memory_map_index = index;
            best_fit_segmant = request_size;
            break;
        }
    }
    if (match == true){ //found match, now swap
        temp_memory_block = memory_map[memory_map_index];
        allocated_memory.start_address = temp_memory_block.start_address;
        allocated_memory.end_address = allocated_memory.start_address + request_size - 1;
        allocated_memory.process_id = process_id;
        allocated_memory.segment_size = request_size;
        *map_cnt = *map_cnt + 1;
        
        for (int i = memory_map_index; i <= *map_cnt; i++){
            memory_map[memory_map_index+1] = memory_map[i];
        }
        memory_map[memory_map_index+1].start_address = allocated_memory.end_address + 1;
        memory_map[memory_map_index+1].end_address = memory_map[memory_map_index].end_address;
        memory_map[memory_map_index+1].process_id = memory_map[memory_map_index].process_id;
        memory_map[memory_map_index+1].segment_size = memory_map[memory_map_index].segment_size - request_size;
        memory_map[memory_map_index] = allocated_memory;
    }
    return allocated_memory;
}

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt) {
    bool flag = false;
    if ((*map_cnt == 1) &&  (memory_map[0].end_address == 0) && (memory_map[0].start_address == 0) && (memory_map[0].process_id == 0) && (memory_map[0].segment_size == 0))
        return;
    else  {
        for (int i = 0; i < *map_cnt; i++){ //looking for the memory block index to free
            if((freed_block.start_address == memory_map[i].start_address) && (freed_block.end_address == memory_map[i].end_address) && (freed_block.process_id == memory_map[i].process_id)) {
                memory_map[i].process_id = 0;
                if (i > 0){
                    if (memory_map[i-1].process_id == 0){
                        memory_map[i-1].end_address = freed_block.end_address;
                        memory_map[i-1].segment_size = memory_map[i-1].segment_size + freed_block.segment_size;
                        for (int index = i; index <= *map_cnt; index++){
                            memory_map[index] = memory_map[index + 1];
                        }
                        *map_cnt = *map_cnt - 1;
                        flag = true;
                    }
                }
                if (i < *map_cnt-1){
                    if (flag == false){
                        i = i+1;
                    }
                    if (memory_map[i].process_id == 0){
                        memory_map[i].start_address = memory_map[i-1].start_address;
                        memory_map[i].segment_size = memory_map[i].end_address -memory_map[i].start_address+1;
                        for (int index = i; index <= *map_cnt; index++){
                            memory_map[index-1] = memory_map[index];
                        }
                        *map_cnt = *map_cnt - 1;
                    }
                }
                break;
            }
        }
    }
}
