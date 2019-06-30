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
    for(m = 0; m < number_of_files; m++)
      {
            for(n = 0; n < number_of_blocks; n++)
            {
                  if(block_arr[n] != 1)
                  {
                        temp = block[n] - file[m];
                        if(temp >= 0)
                        {
                              if(lowest > temp)
                              {
                                    file_arr[m] = n;
                                    lowest = temp;
                              }
                        }
                  }
                  fragments[m] = lowest;
                  block_arr[file_arr[m]] = 1;
                  lowest = 10000;
            }
      }
}

struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id)
{    
    int temp, number_of_files, number_of_blocks;

    for(int m = 0; m < number_of_files; m++)
      {
            for(int n = 0; n < number_of_blocks; n++)
            {
                  if(block_arr[n] != 1)
                  {
                        temp = blocks[n] - files[m];
                        if(temp >= 0)
                        {
                              file_arr[m] = n;
                              break;
                        }
                  }
            }
            fragments[m] = temp;
            block_arr[file_arr[m]] = 1;
      }

    
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id)
{
    for(m = 0; m < number_of_files; m++)
      {
            for(n = 0; n < number_of_blocks; n++)
            {
                  if(block_arr[n] != 1)
                  {
                        temp = blocks[n] - files[m];
                        if(temp >= 0)
                        {
                              if(top < temp)
                              {
                                    file_arr[m] = n;
                                    top = temp;
                              }
                        } 
                  }
                  fragments[m] = top;
                  block_arr[file_arr[m]] = 1;
                  top = 0;
            }   
      }
}

struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address)
{
    for(i = 0; i < total_processes; i++)
      {
            while(j < total_memory)
            {
                  if(memory_size[j][1] == 0 && process_size[i][0] <= memory_size[j][0])
                  {
                        process_size[i][1] = 1;
                        memory_size[j][1] = 1;
                        printf("\nProcess [%d] Allocated to Memory Block:\t%d", i + 1, j + 1);
                        break;
                  }
                  j++;
            }
      }
      for(i = 0; i < total_memory; i++)
      {
            if(process_size[i][1] == 0)
            {
                  printf("\nProcess [%d] Unallocated\n", i + 1);
            }
      }
}