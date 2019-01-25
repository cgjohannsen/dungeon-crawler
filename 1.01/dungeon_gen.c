#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DUNGEON_HEIGHT 21
#define DUNGEON_WIDTH 80

struct room {
  uint8_t x;
  uint8_t y;
  uint8_t width;
  uint8_t height;
};

int remove_element(uint16_t arr[], uint16_t arr_size, uint16_t e){

  int i;
  for(i = e; i < arr_size; i++){
    uint16_t temp = arr[i];
    arr[i] = arr[i+1];
    arr[i+1] = temp;
  }

  arr_size--;

  return 0;
}

int place_rooms(uint8_t num_rooms, char map[21][80]){

  /* Initialize some things */
  uint16_t i, max_height = 10, max_width = 10,
    num_cells = DUNGEON_HEIGHT*DUNGEON_WIDTH, num_valid = num_cells, 
    valid_coords[num_cells];
  for(i = 0; i < num_cells; i++){valid_coords[i] = i;}
  struct room rooms[num_rooms];
  srand(time(NULL));

  /*  
   *  Each room has a coordinate which specifies the upper left corner,  
   *  a width, and height. There are then always a set of valid coordinates 
   *  to place a room, and a valid width/height range for each room.
   */ 

  /* Start by intializing invalid spaces */
  

  /* Begin creating a placing rooms */
  for(i = 0; i < num_rooms; i++){
    /* Calculate coordinate for room */
    uint16_t coord = rand() % num_valid;

    rooms[i].y = coord / DUNGEON_WIDTH;
    rooms[i].x = coord % DUNGEON_WIDTH;

    /* Calculate width and height for room */
    
  }

  return 0;
}

int place_corridors(char map[21][80]){
  
}

int main(int argc, char *argv[]){
  
  char dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH];
  if(place_rooms(2, dungeon) < 0){
    return -1;
  }
  
  int r, c;
  for(r = 0; r < DUNGEON_HEIGHT; r ++){
    for(c = 0; c < DUNGEON_WIDTH; c++){
      
    }
    printf("\n");
  }

  return 0;
}
