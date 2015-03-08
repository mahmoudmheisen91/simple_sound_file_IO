// sndlib.h:
// Sound Library - Header File:

#ifndef SNDLIB_H_
#define SNDLIB_H_

    // Include Libraries:
    #include <inttypes.h>

    // Define Constants:
    #define SFM_READ   O_RDONLY  // read only mode
    #define SFM_WRITE  O_RDONLY  // write only mode
    #define SFM_RDWR   O_RDONLY  // read/write mode

    // Type Definition:
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

    typedef int16_t* wav_data_t;
    typedef int WAVFILE;

    // Global Variables:
    wav_header_t *header;

    // Functions Prototypes:
    WAVFILE wav_open(const char *file_name, const int mode);
    void wav_close(char *file_name, wav_data_t* samples);
    int wav_read(WAVFILE *wav_file, wav_data_t* data, wav_header_t *header);
    void wav_read_header(char *file_name, wav_data_t* samples);
    void wav_read_data(char *file_name, wav_data_t* samples);
    void wav_write(char *file_name, wav_data_t samples);
    void wav_write_header(char *file_name, wav_data_t samples);
    void wav_write_data(char *file_name, wav_data_t samples);

#endif // SNDLIB_H_
