#ifndef NPC_H
# define NPC_H

# define NPC_SMART   0x00000001 // = b00000001
# define NPC_TELE    0x00000002 // = b00000010
# define NPC_TUNNEL  0x00000004 // = b00000100
# define NPC_ERRATIC 0x00000008 // = b00001000

# define has_characterstic(character, bit) \
     (character.characterstics & NPC_##bit)

# define SCREEN_HEIGHT 20
# define MAX_MONSTERS  50

typedef struct dungeon dungeon_t;
typedef struct character character_t;

typedef struct npc {
  uint16_t characteristics;
} npc_t;

int npc_init(dungeon_t *d, int seed);
void npc_delete(npc_t *npc);
int npc_move(dungeon_t *d, character_t *npc);
int display_monsters(dungeon_t *d, char m);

int npc_move00(dungeon_t *d, character_t *c);
int npc_move01(dungeon_t *d, character_t *c);
int npc_move02(dungeon_t *d, character_t *c);
int npc_move03(dungeon_t *d, character_t *c);
int npc_move04(dungeon_t *d, character_t *c);
int npc_move05(dungeon_t *d, character_t *c);
int npc_move06(dungeon_t *d, character_t *c);
int npc_move07(dungeon_t *d, character_t *c);
int npc_move08(dungeon_t *d, character_t *c);
int npc_move09(dungeon_t *d, character_t *c);
int npc_move10(dungeon_t *d, character_t *c);
int npc_move11(dungeon_t *d, character_t *c);
int npc_move12(dungeon_t *d, character_t *c);
int npc_move13(dungeon_t *d, character_t *c);
int npc_move14(dungeon_t *d, character_t *c);
int npc_move15(dungeon_t *d, character_t *c);

#endif
