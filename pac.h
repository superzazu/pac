#ifndef PAC_PAC_H
#define PAC_PAC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "z80/z80.h"
#include "wsg.h"

#define PAC_CLOCK_SPEED 3072000 // 3.072 MHz (= number of cycles per second)
#define PAC_FPS 60
#define PAC_CYCLES_PER_FRAME (PAC_CLOCK_SPEED / PAC_FPS)
#define PAC_SCREEN_WIDTH 224
#define PAC_SCREEN_HEIGHT 288

typedef struct pac pac;
struct pac {
  z80 cpu;
  u8 rom[0x10000]; // 0x0000-0x4000
  u8 ram[0x1000]; // 0x4000-0x5000
  u8 sprite_pos[0x10]; // 0x5060-0x506f

  u8 color_rom[32];
  u8 palette_rom[0x100];
  u8 tile_rom[0x1000];
  u8 sprite_rom[0x1000];
  u8 sound_rom1[0x100];
  u8 sound_rom2[0x100];

  u8 tiles[256 * 8 * 8]; // to store predecoded tiles
  u8 sprites[64 * 16 * 16]; // to store predecoded sprites

  u8 int_vector;
  bool vblank_enabled;
  bool sound_enabled;
  bool flip_screen;

  // in 0 port
  bool p1_up, p1_left, p1_right, p1_down, rack_advance, coin_s1, coin_s2,
      credits_btn;

  // in 1 port
  bool board_test, p1_start, p2_start;

  // ppu
  u8 screen_buffer[PAC_SCREEN_HEIGHT * PAC_SCREEN_WIDTH * 3];
  void (*update_screen)(pac* const n);

  // audio
  wsg sound_chip;
  int audio_buffer_len;
  int16_t* audio_buffer;
  int sample_rate;
  bool mute_audio;
  void (*push_sample)(pac* const n, int16_t);
};

int pac_init(pac* const p, const char* rom_dir);
void pac_quit(pac* const p);
void pac_update(pac* const p, int ms);

void pac_cheat_invincibility(pac* const p);

#endif // PAC_PAC_H
