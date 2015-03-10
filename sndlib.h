// sndlib.h:
// Sound Library - Header File:
// TODO: header and data types, Makefile:

#ifndef SNDLIB_H_
#define SNDLIB_H_

    // Include Libraries:
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <string.h>

    // Define Constants:
    #define WAV_READ   O_RDONLY  // read only mode
    #define WAV_WRITE  O_WRONLY  // write only mode
    #define WAV_RDWR   O_RDWR    // read/write mode

    // Type Definition:
    // wav file data type that contain pointer to the data:
    typedef int16_t* wav_data_t;

    // wav file header type that contain information about the wav signal, eg:
    // number of channels, audio format, sampling frequency, data length, etc:
    typedef struct _wav_header_t {
        char            chunk_id[4];
        unsigned int    chunk_size      : 32;
        char            format[4];
        char            format_id[4];
        unsigned int    format_size     : 32;
        unsigned int    audio_format    : 16;
        unsigned int    num_channels    : 16;
        unsigned int    sample_rate     : 32;
        unsigned int    byte_rate       : 32;
        unsigned int    block_align     : 16;
        unsigned int    nbit_per_sample : 16;
        char            data_id[4];
        unsigned int    data_length     : 32;
    } wav_header_t;

    // TODO: extract name:
    // ???: calling two data structures insideeach other
    // wav file info: name, Fs, nbits:
    typedef struct _INFO {
        int data_length;
        int nbit_per_sample;
        int Fs;
    } INFO;

    // WAVFILE type that contain information about the file itself, eg. discriptor, name, open mode:
    typedef struct _WAVFILE {
        char* file_name;
        int file_discriptor;
        int is_read;
        int is_write;
    } WAVFILE;

    // Functions Prototypes:
    WAVFILE *wav_open(char *file_name, int mode);
    int wav_close(WAVFILE *wav_file);
    int wav_read(WAVFILE *wav_file, wav_header_t *header, wav_data_t *data);
    int wav_write(WAVFILE *wav_file, wav_header_t *header, wav_data_t data);

#endif // SNDLIB_H_
