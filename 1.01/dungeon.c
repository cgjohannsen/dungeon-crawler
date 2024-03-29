#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

int place_rooms(uint8_t num_rooms, 
		struct room rooms[], 
		uint8_t map[21][80])
{

  /* Initialize some things */
  uint16_t i, j, r, c, isValid, max_height = 10, max_width = 20;
  srand(time(NULL));

  /*  
   *  Each room has a coordinate which specifies the upper left corner,  
   *  a width, and height. There are then always a set of valid coordinates 
   *  to place a room, and a valid width/height range for each room.
   */ 

  /* Place immutable spaces and rest of map with rock */
  for(i = 0; i < DUNGEON_HEIGHT; i++){
    if(i == 0 || i == DUNGEON_HEIGHT-1){
      for(j = 0; j < DUNGEON_WIDTH; j++){
	map[i][j] = 255;
      }
    }else{
      map[i][0] = 255;
      map[i][DUNGEON_WIDTH-1] = 255;
      for(j = 1; j < DUNGEON_WIDTH-1; j++){
	map[i][j] = 1;
      }
    }
  }

  /* Begin creating and placing rooms */
  for(i = 0; i < num_rooms; i++){
    do{
      /* Calculate coordinate for room */
      rooms[i].y = (rand() % (DUNGEON_HEIGHT-4)) + 1;
      rooms[i].x = (rand() % (DUNGEON_WIDTH-5)) + 1;
    
      /* Calculate width and height for room */
      rooms[i].width = (rand() % (max_width-4)) + 4;
      rooms[i].height = (rand() % (max_height-3)) + 3;

      isValid = 1;

      for(r = rooms[i].y-1; r < rooms[i].y+rooms[i].height+1; r++){
	for(c = rooms[i].x-1; c < rooms[i].x+rooms[i].width+1; c++){
	  if(map[r][c] == 0 || map[r][c] == 255){ isValid = 0; }
	}
      }
    }while(!isValid);

    /* Place room */
    for(r = rooms[i].y; r < rooms[i].y+rooms[i].height; r++){
      for(c = rooms[i].x; c < rooms[i].x+rooms[i].width; c++){
	map[r][c] = 0;
      }
    }
  }

  return 0;
}

int place_corridors(uint8_t num_rooms, 
		    struct room rooms[],
		    uint8_t map[21][80]){

  uint16_t i, r, c, room1, room2;

  for(i = 0; i < num_rooms; i++){
    room1 = i;
    room2 = (i + 1) % num_rooms;

    r = rooms[room1].y;
    c = rooms[room1].x;
    
    do{
      if(r < rooms[room2].y){ r++; }
      else if(r > rooms[room2].y){ r--; }
      else if(c < rooms[room2].x){ c++; }
      else if(c > rooms[room2].x){ c--; }
      
      if(map[r][c] != 255){ map[r][c] = 0; }
    }while( r != rooms[room2].y || c != rooms[room2].x);
  }

  return 0;
}

int place_stairs(uint8_t stairs[],
		 uint8_t num_rooms,
		 struct room rooms[],
		 uint8_t map[21][80]){

  uint16_t rand_room, rand_row, rand_col;
  srand(time(NULL));

  rand_room = rand() % num_rooms;
  rand_row = (rand() % rooms[rand_room].height) + rooms[rand_room].y;
  rand_col = (rand() % rooms[rand_room].width) + rooms[rand_room].x;
  stairs[0] = 0;
  stairs[1] = rand_row;
  stairs[2] = rand_col;

  do{
    rand_room = rand() % num_rooms;
    rand_row = (rand() % rooms[rand_room].height) + rooms[rand_room].y;
    rand_col = (rand() % rooms[rand_room].width) + rooms[rand_room].x;
    stairs[3] = 1;
    stairs[4] = rand_row;
    stairs[5] = rand_col;
  }while(stairs[1] == stairs[4] || stairs[2] == stairs[5]);

  return 0;
}

int main(int argc, char *argv[]){

  uint8_t dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH], num_rooms = 6;
  uint8_t stairs[6];
  struct room rooms[num_rooms];

  place_rooms(num_rooms, rooms, dungeon);
  place_corridors(num_rooms, rooms, dungeon);
  place_stairs(stairs, num_rooms, rooms, dungeon);
  
  char char_dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH];
  int r, c, i;
  for(r = 0; r < DUNGEON_HEIGHT; r++){
    for(c = 0; c < DUNGEON_WIDTH; c++){
      char_dungeon[r][c] = ' ';
    }
  }

  for(i = 0; i < num_rooms; i++){
    for(r = rooms[i].y; r < rooms[i].y+rooms[i].height; r++){
      for(c = rooms[i].x; c < rooms[i].x+rooms[i].width; c++){
	char_dungeon[r][c] = '.';
      }
    }
  }

  for(i = 0; i < 6; i=i+3){
    if(stairs[i] == 0){
      char_dungeon[stairs[i+1]][stairs[i+2]] = '>';
    }else{
      char_dungeon[stairs[i+1]][stairs[i+2]] = '<';
    }
  }

  for(r = 0; r < DUNGEON_HEIGHT; r++){
    for(c = 0; c < DUNGEON_WIDTH; c++){
      if(char_dungeon[r][c] != '.' && 
	char_dungeon[r][c] != '>' &&
	char_dungeon[r][c] != '<'){
	if(dungeon[r][c] > 0){ char_dungeon[r][c] = ' '; }
	else{ char_dungeon[r][c] = '#'; }
      }
    }
  }

  printf("%c\n", char_dungeon[20][2]);

  for(r = 0; r < DUNGEON_HEIGHT; r++){
    for(c = 0; c < DUNGEON_WIDTH; c++){
      printf("%c", char_dungeon[r][c]);
    }
    printf("\n");
  }

  return 0;
}
