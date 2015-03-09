#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include "sndlib.h"

void main(void) {

    WAVFILE *test_wave;
    wav_data_t data = NULL;
    wav_header_t header;

    test_wave = wav_open("testSignal.wav", SFM_READ);
    wav_read(test_wave, &header, &data);
    wav_close(test_wave);

    test_wave = wav_open("testSignal8.wav", SFM_WRITE);
    wav_write(test_wave, &header, data);
    wav_close(test_wave);

    printf("No. of channels: %d\n",     header.num_channels);
    printf("Sample rate:     %d\n",     header.sample_rate);
    printf("Bit rate:        %dkbps\n", header.byte_rate*8 / 1000);
    printf("Bits per sample: %d\n",     header.bit_rate);
    printf("Sample 0:        %d\n",     data[112]);
    printf("Sample 1:        %d\n\n",   data[410]);

    //int i;
    //for (i= 0; i < 100000; i++)
    //    printf("Sample 0:        %d\n",     data[i]);

    // Modify the header values & samples before writing the new file

    //free(header);
    //free(data);
}
