#include <stdio.h>
#include <stdlib.h>
#include "sndlib.h"

void main(void) {

    // types:
    WAVFILE *test_wave;
    wav_data_t data;
    wav_header_t header;

    // read wav signal:
    test_wave = wav_open("test_signal.wav", SFM_READ );
    wav_read(test_wave, &header, &data);
    wav_close(test_wave);

    // write wav signal:
    test_wave = wav_open("test_signal_2.wav", SFM_WRITE);
    wav_write(test_wave, &header, data);
    wav_close(test_wave);

    // print header:
    printf("\nHeader:\n");
    printf("  chunk_id: \t%.4s\n",      header.chunk_id);
    printf("  chunk_size: \t%d\n",      header.chunk_size);
    printf("  format: \t%.4s\n",        header.format);
    printf("  format_id: \t%.4s\n",     header.format_id);
    printf("  formatk_size: %d\n",    header.format_size);
    printf("  audio_format: %d\n",    header.audio_format);
    printf("  num_channels: %d\n",    header.num_channels);
    printf("  sample_rate: \t%d\n",     header.sample_rate);
    printf("  byte_rate: \t%d\n",       header.byte_rate);
    printf("  block_align: \t%d\n",     header.block_align);
    printf("  nbits\\sample: %d\n", header.nbit_per_sample);
    printf("  data_id: \t%.4s\n",       header.data_id);
    printf("  data_length: \t%d\n",     header.data_length);

    // sample print:
    printf("\nSample print:\n");
    printf("  Bit rate: \t%dkbps\n\n", header.byte_rate*8 / 1000);

    // save wav signal to file:
    FILE *fp;
    fp = fopen("signal_data.txt", "w");

    int i;
    for (i= 0; i < header.data_length; i++)
        fprintf(fp, "%d %d\n", i, data[i]);
    fclose(fp);

    // free memory:
    // TODO: header as pointer
    // free(header);
    free(data);
}
