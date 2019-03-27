#ifndef PATHFINDER_H
# define PATHFINDER_H

# include <cstdint>
# include "heap.h"

# define DUNGEON_X 80
# define DUNGEON_Y 21

class pathfinder{

public:

	class dungeon_path{
	public:
		heap_node_t *hn;
 		uint8_t pos[2];
 		uint8_t from[2];
 		int32_t cost;
	};

	uint8_t h[DUNGEON_Y][DUNGEON_X];
	dungeon_path path[DUNGEON_Y][DUNGEON_X];

	pathfinder();
	~pathfinder();

	int init(uint8_t hardness[DUNGEON_Y][DUNGEON_X]);
	int pathfinder_dijkstra_floor(uint8_t, uint8_t);
	int pathfinder_dijkstra_all(uint8_t, uint8_t);

};

#endif
