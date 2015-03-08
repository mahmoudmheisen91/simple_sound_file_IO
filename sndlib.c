#include <stdio.h>      /* for fprintf and stderr */
#include <stdlib.h>     /* for exit */
#include <err.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sndlib.h"

WAVFILE wav_open(char *file_name, int mode) {
    WAVFILE wav_file;

    wav_file = open(file_name, mode);

    if (wav_file < 1) {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    return wav_file;
}

void wav_read(char *file_name, wav_data_t* samples) {
    int fd;
    if ((fd = open(file_name, O_RDONLY)) < 1)
        errx(1, "Error opening file");
    if (!header)
        header = (wav_header_t*)malloc(sizeof(wav_header_t));
    if (read(fd, header, sizeof(wav_header_t)) < sizeof(wav_header_t))
        errx(1, "File broken: header");
    if (strncmp(header->chunk_id, "RIFF", 4) ||
        strncmp(header->format, "WAVE", 4))
        errx(1, "Not a wav file");
    if (header->audio_format != 1)
        errx(1, "Only PCM encoding supported");
    if (*samples)
        free(*samples);
    *samples = (int16_t*)malloc(header->data_chunk_size);
    if (!*samples)
        errx(1, "Error allocating memory");
    if (read(fd, *samples, header->data_chunk_size) < header->data_chunk_size)
        errx(1, "File broken: samples");
    close(fd);
}

void wav_write(char *file_name, wav_data_t samples) {
    int fd;
    if ((fd = creat(file_name, 0666)) < 1)
        errx(1, "Error creating file");
    if (write(fd, header, sizeof(wav_header_t)) < sizeof(wav_header_t))
        errx(1, "Error writing header");
    if (write(fd, samples, header->data_chunk_size) < header->data_chunk_size)
        errx(1, "Error writing samples");
    close(fd);
}
