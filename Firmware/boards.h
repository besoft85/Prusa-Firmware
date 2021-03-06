#ifndef BOARDS_H
#define BOARDS_H

#define BOARD_UNKNOWN -1

#define BOARD_RAMBO_MINI_1_0    200  // Rambo-mini 1.0 - 200 (orig 102)
#define BOARD_RAMBO_MINI_1_3    203  // Rambo-mini 1.3 - 203 (orig 302)

#define BOARD_EINSY_1_0a        310  // EINSy 1.0a     - 310 (new)

/*RAMPS*/
#define BOARD_RAMPS_14_EFB      33   // RAMPS 1.3 / 1.4 (Power outputs: Extruder, Fan, Bed)
/*RAMPS*/

#define MB(board) (MOTHERBOARD==BOARD_##board)
#define IS_RAMPS (MB(RAMPS_OLD) || MB(RAMPS_13_EFB) || MB(RAMPS_13_EEB) || MB(RAMPS_13_EFF) || MB(RAMPS_13_EEF) || MB(RAMPS_14_EFB))

#endif //__BOARDS_H
