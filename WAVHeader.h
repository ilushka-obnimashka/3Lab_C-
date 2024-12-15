#include <cstdint>
/**
 * @file WAVHeader.h
 * @brief Header file defining the structure of a WAV file header.
 */

#pragma once
#define FIXED_SAMPLE_RATE 44100

/**
 * @brief A structure representing the header of a WAV file.
 *
 * This structure describes the format and characteristics of audio data stored in a WAV file.
 */
struct WAVHeader {
    // RIFF Chunk
    char chunk_id[4];        ///< Chunk ID. Indicates that the file is a RIFF file.
    uint32_t chunk_data_size;   ///< Size of the RIFF chunk data (file size minus the first 8 bytes).
    char riff_type_id[4];    ///< Format type ID. Indicates that the file is a WAVE file.

    // format sub-chunk
    uint8_t chunk1_id[4];       ///< Format sub-chunk ID. Indicates that the following sub-chunk contains format information.
    uint32_t chunk1_data_size;  ///< Size of the format sub-chunk in bytes.
    uint16_t format_tag;        ///< Audio format code (1 = PCM).
    uint16_t num_channels;      ///< Number of audio channels (1 = mono, 2 = stereo, etc.).
    uint32_t sample_rate;       ///< Sampling frequency in Hz (e.g., 44100 for CD-quality audio).
    uint32_t byte_rate;         ///< Byte rate (sampleRate * numChannels * bitsPerSample / 8).
    uint16_t block_align;       ///< Block align (numChannels * bitsPerSample / 8).
    uint16_t bits_per_sample;   ///< Bits per sample (e.g., 8, 16, 24, or 32).

    /* "data" sub-chunk */
    uint8_t chunk2_id[4];       ///< Data sub-chunk ID. Indicates that the following sub-chunk contains audio data.
    uint32_t chunk2_data_size;  ///< Size of the audio data in bytes.
};
