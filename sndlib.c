#include <stdio.h>      /* for fprintf and stderr */
#include <stdlib.h>     /* for exit */
#include <err.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sndlib.h"

WAVFILE* wav_open(const char *file_name, const int mode) {
    if (mode != SFM_READ && mode != SFM_WRITE && mode != SFM_RDWR) {
        fprintf(stderr, "Error mode type\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    WAVFILE wav_file;
    wav_file.file_discriptor = open(file_name, mode);
    wav_file.is_read = (mode == SFM_READ) ? True : False;
    wav_file.is_write = (mode == SFM_WRITE) ? True : False;

    if (mode == SFM_RDWR) {
        wav_file.is_read = True;
        wav_file.is_write = True;
    }

    if ((wav_file.file_discriptor < 1) && (mode == SFM_WRITE || mode == SFM_RDWR)) {
        wav_file.file_discriptor = open(file_name, mode | O_CREAT | O_EXCL, 0666);
    }

    if (wav_file.file_discriptor < 1) {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    WAVFILE *wav_file2 = &wav_file;
    return wav_file2;
}

int wav_read(WAVFILE *wav_file, wav_header_t *header, wav_data_t *data) {
    if (wav_file->is_read == False) {
        fprintf(stderr, "File is write only\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    free(*data);
    *data = (wav_data_t)malloc(header->data_chunk_size);

    int header_size = read(wav_file->file_discriptor, header, sizeof(wav_header_t));
    if (header_size < sizeof(wav_header_t)) {
        fprintf(stderr, "File broken header\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    if (strncmp(header->chunk_id, "RIFF", 4) || strncmp(header->format, "WAVE", 4)) {
        fprintf(stderr, "Not a wav file\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }
    if (header->audio_format != 1) {
        fprintf(stderr, "Only PCM encoding supported\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    int data_size = read(wav_file->file_discriptor, *data, header->data_chunk_size);
    if (data_size < sizeof(wav_header_t)) {
        fprintf(stderr, "File broken data\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    return 1;
}

int wav_write(WAVFILE *wav_file, wav_header_t *header, wav_data_t data) {
    if (wav_file->is_write == False) {
        fprintf(stderr, "File is read only\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    int header_size = write(wav_file->file_discriptor, header, sizeof(wav_header_t));
    if (header_size < sizeof(wav_header_t)) {
        fprintf(stderr, "Error writing header\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    int data_size = write(wav_file->file_discriptor, data, header->data_chunk_size);
    if (data_size < header->data_chunk_size) {
        fprintf(stderr, "Error writing data\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    return 1;
}

int wav_close(WAVFILE *wav_file) {
    close(wav_file);
}
