#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include "sndlib.h"

void main(void) {

    int16_t *samples = NULL;
    wav_read2("testSignal.wav", &samples);

    printf("No. of channels: %d\n",     header->num_channels);
    printf("Sample rate:     %d\n",     header->sample_rate);
    printf("Bit rate:        %dkbps\n", header->byte_rate*8 / 1000);
    printf("Bits per sample: %d\n\n",   header->bit_rate);
    printf("Sample 0:        %d\n", samples[0]);
    printf("Sample 1:        %d\n", samples[1]);

    // Modify the header values & samples before writing the new file
    wav_write("testSignal2.wav", samples);
    free(header);
    free(samples);
}
