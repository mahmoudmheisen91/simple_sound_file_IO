// sndlib.h:
// Sound Library - Header File:

#ifndef SNDLIB_H_
#define SNDLIB_H_

    // Include Libraries:
    #include <inttypes.h>
    #include <fcntl.h>

    // Define Constants:
    #define SFM_READ   O_RDONLY  // read only mode
    #define SFM_WRITE  O_WRONLY  // write only mode
    #define SFM_RDWR   O_RDWR    // read/write mode
    #define True       1
    #define False      0

    // Type Definition:
    typedef int boolean;
    typedef int16_t* wav_data_t;

    typedef struct _WAVFILE {
        int file_discriptor;
        boolean is_read;
        boolean is_write;
    } WAVFILE;

    typedef struct _wav_header_t {
        char     chunk_id[4];
        uint32_t chunk_size;
        char     format[4];
        char     format_chunk_id[4];
        uint32_t format_chunk_size;
        uint16_t audio_format;
        uint16_t num_channels;
        uint32_t sample_rate;
        uint32_t byte_rate;
        uint16_t block_align;
        uint16_t bit_rate;
        char     data_chunk_id[4];
        uint32_t data_chunk_size;
    } wav_header_t;

    // Functions Prototypes:
    WAVFILE *wav_open(const char *file_name, const int mode);
    int wav_close(WAVFILE *wav_file);
    int wav_read(WAVFILE *wav_file, wav_header_t *header, wav_data_t *data);
    int wav_read_header(char *file_name, wav_data_t* samples);
    int wav_read_data(char *file_name, wav_data_t* samples);
    int wav_write(WAVFILE *wav_file, wav_header_t *header, wav_data_t data);
    int wav_write_header(char *file_name, wav_data_t samples);
    int wav_write_data(char *file_name, wav_data_t samples);

#endif // SNDLIB_H_
