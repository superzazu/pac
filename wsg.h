#ifndef PAC_WSG_H
#define PAC_WSG_H
// Namco WSG (Waveform Sound Generator): 3 voice mono wavetable chip (96kHz)

#include <stdint.h>

#define WSG_SAMPLE_RATE 96000

typedef struct wsg_voice {
    uint32_t frequency; // 20 bit value
    uint32_t accumulator; // 20 bit value
    uint8_t waveform_no; // 3 bit value
    uint8_t volume; // 4 bit value
} wsg_voice;

typedef struct wsg {
    wsg_voice voices[3];
    uint8_t* sound_rom;
    int gain;
} wsg;

void wsg_init(wsg* const w, uint8_t* const sound_rom);
void wsg_write(wsg* const w, uint8_t address, uint8_t value);
void wsg_play(wsg* const w, int16_t* const buffer, int buffer_len);

#endif // PAC_WSG_H
