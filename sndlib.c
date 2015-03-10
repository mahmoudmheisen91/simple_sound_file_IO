// Include header file:
#include "sndlib.h"

// Open wav file function:
// inputs:
//   char *file_name : name of the wav file
//   int mode        : opening mode
// return:
//   WAVFILE*        : pointer to the wav file
WAVFILE* wav_open(char *file_name, int mode) {
    // check if the mode is correct:
    if (mode != WAV_READ && mode != WAV_WRITE && mode != WAV_RDWR) {
        fprintf(stderr, "Error opening file %s: mode type is not correct\n", file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // create wav file object and fill it is fields:
    WAVFILE wav_file;
    wav_file.file_discriptor = open(file_name, mode);
    wav_file.is_read   = (mode == WAV_READ  || mode == WAV_RDWR) ? 1 : 0;
    wav_file.is_write  = (mode == WAV_WRITE || mode == WAV_RDWR) ? 1 : 0;

    // create new file if the file does not exists and the mode is write or read/write:
    if ((wav_file.file_discriptor < 1) && (wav_file.is_write)) {
        wav_file.file_discriptor = open(file_name, mode | O_CREAT | O_EXCL, 0666);
    }

    // check if the file opened correctly:
    if (wav_file.file_discriptor < 1) {
        fprintf(stderr, "Error opening file %s: file does not exists\n", file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // return pointer to the opened file:
    WAVFILE *wav_file2 = &wav_file;
    return wav_file2;
}

// Read wav file function:
// inputs:
//   WAVFILE *wav_file    : pointer to the wav file
//   wav_header_t *header : data structure to store wav file header
//   wav_data_t *data     : pointer where the data need to be stored
// return:
//   int                   : to indicate reading status
int wav_read(WAVFILE *wav_file, wav_header_t *header, wav_data_t *data) {
    // check if the file opened for reading:
    if (!wav_file->is_read) {
        fprintf(stderr, "Error reading from file %s: File is write only\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // allocate data element:
    *data = (wav_data_t)malloc(header->data_length);

    // read header of the wav file and check it's size:
    int header_size = read(wav_file->file_discriptor, header, sizeof(wav_header_t));
    if (header_size < sizeof(wav_header_t)) {
        fprintf(stderr, "Error reading from file %s: broken header\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // check if the file is a wav file, by checking the chunk_id or the format:
    if (strncmp(header->chunk_id, "RIFF", 4) || strncmp(header->format, "WAVE", 4)) {
        fprintf(stderr, "Error reading from file %s: Not a wav file\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // check if the encoding is supported:
    if (header->audio_format != 1) {
        fprintf(stderr, "Error reading from file %s: only PCM encoding support\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // check if the number of channels is supported:
    if (header->audio_format != 1) {
        fprintf(stderr, "Error reading from file %s: only PCM encoding support\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // read data of the wav file and check it's size:
    int data_size = read(wav_file->file_discriptor, *data, header->data_length);
    if (data_size < sizeof(wav_header_t)) {
        fprintf(stderr, "Error reading from file %s: broken data\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // indicate successfull reading:
    return 1;
}

// Write wav file function:
// inputs:
//   WAVFILE *wav_file    : pointer to the wav file
//   wav_header_t *header : data structure contain wav file header
//   wav_data_t *data     : pointer where to wav file data
// return:
//   int                   : to indicate writing status
int wav_write(WAVFILE *wav_file, wav_header_t *header, wav_data_t data) {
    // check if the file opened for writing:
    if (!wav_file->is_write) {
        fprintf(stderr, "Error writing to file %s: File is read only\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // write header of the wav file and check it's size:
    int header_size = write(wav_file->file_discriptor, header, sizeof(wav_header_t));
    if (header_size < sizeof(wav_header_t)) {
        fprintf(stderr, "Error writing header to the file %s\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // write data of the wav file and check it's size:
    int data_size = write(wav_file->file_discriptor, data, header->data_length);
    if (data_size < header->data_length) {
        fprintf(stderr, "Error writing data to the file %s\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // indicate successfull writing:
    return 1;
}

// Close wav file function:
// inputs:
//   WAVFILE *wav_file : pointer to the wav file
// return:
//   int                : to indicate closing status
int wav_close(WAVFILE *wav_file) {
    // close the file and check if it is closed correctly:
    if (!close(wav_file)) {
        fprintf(stderr, "Error closing file %s\n", wav_file->file_name);
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    // indicate successfull closing:
    return 1;
}
