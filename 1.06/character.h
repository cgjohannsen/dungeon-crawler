#ifndef CHARACTER_H
# define CHARACTER_H

# include <cstdint>

# include "heap.h"

class dungeon;

class character{

public:

  uint8_t is_pc;
  heap_node_t *hn;
  uint8_t isAlive;
  uint8_t speed;
  uint32_t move_time;
  char symbol;
  uint8_t x;
  uint8_t y;
  uint8_t next_x;
  uint8_t next_y;

  character();

};

#endif
