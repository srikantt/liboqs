/**
 * \file aes.h
 * \brief Header defining the API for OQS AES
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef OQS_AES_H
#define OQS_AES_H

#include <stdint.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * Function to fill a key schedule given an initial key for use in ECB mode.
 *
 * @param key            Initial Key.
 * @param ctx            Abstract data structure for a key schedule.
 */
void OQS_AES128_ECB_load_schedule(const uint8_t *key, void **ctx);

/**
 * Function to initialize a context and fill a key schedule given an initial key for
 * use in CTR mode.
 *
 * @param key            Initial Key.
 * @param ctx            Abstract data structure for a key schedule.
 */
void OQS_AES128_CTR_inc_init(const uint8_t *key, void **ctx);

/**
 * Function to fill a context given an IV for use in CTR mode.
 *
 * Handles a 12- or 16-byte IV.  If a 12-byte IV is given, then 4 counter
 * bytes are initialized to all zeros.
 *
 * @param iv             Initialization Vector.
 * @param iv_len         Length of the initialization vector.
 * @param ctx            Abstract data structure for IV.
 */
void OQS_AES128_CTR_inc_iv(const uint8_t *iv, size_t iv_len, void *ctx);

/**
 * Function to fill a context given an IV for use in CTR mode.
 * Handles an 8-byte IV passed as a 64-bit unsigned integer,
 * counter bytes are initialized to zero.
 *
 * @param iv             Initialization Vector as 64-bit integer.
 * @param ctx            Abstract data structure for IV.
 */
void OQS_AES128_CTR_inc_ivu64(uint64_t iv, void *ctx);

/**
 * Function to free a key schedule.
 *
 * @param ctx            Context generated with OQS_AES128_ECB_load_schedule().
 */
void OQS_AES128_free_schedule(void *ctx);

/**
 * Function to encrypt blocks of plaintext using ECB mode.
 * A schedule based on the key is generated and used internally.
 *
 * @param plaintext     Plaintext to be encrypted.
 * @param plaintext_len Length on the plaintext in bytes. Must be a multiple of 16.
 * @param key           Key to be used for encryption.
 * @param ciphertext    Pointer to a block of memory which >= in size to the plaintext block. The result will be written here.
 * @warning plaintext_len must be a multiple of 16.
 */
void OQS_AES128_ECB_enc(const uint8_t *plaintext, const size_t plaintext_len, const uint8_t *key, uint8_t *ciphertext);

/**
 * Same as OQS_AES128_ECB_enc() except a schedule generated by
 * OQS_AES128_ECB_load_schedule() is passed rather then a key. This is faster
 * if the same schedule is used for multiple encryptions since it does
 * not have to be regenerated from the key.
 */
void OQS_AES128_ECB_enc_sch(const uint8_t *plaintext, const size_t plaintext_len, const void *schedule, uint8_t *ciphertext);

/**
 * Function to fill a key schedule given an initial key for use in ECB mode encryption.
 *
 * @param key            Initial Key.
 * @param ctx            Abstract data structure for a key schedule.
 */
void OQS_AES256_ECB_load_schedule(const uint8_t *key, void **ctx);

/**
 * Function to initialize a context and fill a key schedule given an initial key for
 * use in CTR mode.
 *
 * @param key            Initial Key.
 * @param ctx            Abstract data structure for a key schedule.
 */
void OQS_AES256_CTR_inc_init(const uint8_t *key, void **ctx);

/**
 * Function to fill a context given an IV for use in CTR mode.
 *
 * Handles a 12- or 16-byte IV.  If a 12-byte IV is given, then 4 counter
 * bytes are initialized to all zeros.
 *
 * @param iv             Initialization Vector.
 * @param iv_len         Length of the initialization vector.
 * @param ctx            Abstract data structure for IV.
 */
void OQS_AES256_CTR_inc_iv(const uint8_t *iv, size_t iv_len, void *ctx);

/**
 * Function to fill a context given an IV for use in CTR mode.
 * Handles an 8-byte IV passed as a 64-bit unsigned integer,
 * counter bytes are initialized to zero.
 *
 * @param iv             Initialization Vector as 64-bit integer.
 * @param ctx            Abstract data structure for IV.
 */
void OQS_AES256_CTR_inc_ivu64(uint64_t iv, void *ctx);

/**
 * AES counter mode keystream generator.  A context generated by
 * OQS_AES128_CTR_inc_init() is passed rather then a key.
 *
 * Handles a 12- or 16-byte IV.  If a 12-byte IV is given, then 4 counter
 * bytes are initialized to all zeros.
 *
 * @param iv       12- or 16-byte initialization vector.
 * @param iv_len   Lengh of IV in bytes.
 * @param ctx      Abstract data structure for a key schedule.
 * @param out      Pointer to a block of memory which is big enough to contain out_len bytes; the result will be written here.
 * @param out_len  Length of output bytes to generate.
 */
void OQS_AES128_CTR_inc_stream_iv(const uint8_t *iv, size_t iv_len, const void *ctx, uint8_t *out, size_t out_len);

/**
 * AES counter mode keystream generator. A context generated by
 * OQS_AES256_CTR_inc_init() and OQS_AES256_CTR_inc_iv() is passed
 * rather than a key and an IV. The counter is internally updated, which allows
 * the function to be called multiple times.
 *
 * @param ctx         Abstract data structure for key schedule and IV.
 * @param out         Pointer to a block of memory which is big enough to contain out_blks*16 bytes; the result will be written here.
 * @param out_blks    Length of output blocks to generate, where one block is 16 bytes.
 */
void OQS_AES256_CTR_inc_stream_blks(void *ctx, uint8_t *out, size_t out_blks);

/**
 * Function to free a key schedule.
 *
 * @param ctx            Schedule generated with OQS_AES256_ECB_load_schedule
 *                       or OQS_AES256_CTR_inc_init.
 */
void OQS_AES256_free_schedule(void *ctx);

/**
 * Function to encrypt blocks of plaintext using ECB mode.
 * A schedule based on the key is generated and used internally.
 *
 * @param plaintext     Plaintext to be encrypted.
 * @param plaintext_len Length on the plaintext in bytes. Must be a multiple of 16.
 * @param key           Key to be used for encryption.
 * @param ciphertext    Pointer to a block of memory which >= in size to the plaintext block. The result will be written here.
 * @warning plaintext_len must be a multiple of 16.
 */
void OQS_AES256_ECB_enc(const uint8_t *plaintext, const size_t plaintext_len, const uint8_t *key, uint8_t *ciphertext);

/**
 * Same as OQS_AES256_ECB_enc() except a schedule generated by
 * OQS_AES256_ECB_load_schedule() is passed rather then a key. This is faster
 * if the same schedule is used for multiple encryptions since it does
 * not have to be regenerated from the key.
 */
void OQS_AES256_ECB_enc_sch(const uint8_t *plaintext, const size_t plaintext_len, const void *schedule, uint8_t *ciphertext);

/**
 * AES counter mode keystream generator.  A context generated by
 * OQS_AES256_CTR_inc_init() is passed rather then a key.
 *
 * Handles a 12- or 16-byte IV.  If a 12-byte IV is given, then 4 counter
 * bytes are initialized to all zeros.
 *
 * @param iv       12- or 16-byte initialization vector.
 * @param iv_len   Lengh of IV in bytes.
 * @param ctx      Abstract data structure for a key schedule.
 * @param out      Pointer to a block of memory which is big enough to contain out_len bytes; the result will be written here.
 * @param out_len  Length of output bytes to generate.
 */
void OQS_AES256_CTR_inc_stream_iv(const uint8_t *iv, size_t iv_len, const void *ctx, uint8_t *out, size_t out_len);

/**
 * AES counter mode keystream generator. A context generated by
 * OQS_AES256_CTR_inc_init() and OQS_AES256_CTR_inc_iv() is passed
 * rather than a key and an IV. The counter is internally updated, which allows
 * the function to be called multiple times.
 *
 * @param ctx         Abstract data structure for key schedule and IV.
 * @param out         Pointer to a block of memory which is big enough to contain out_blks*16 bytes; the result will be written here.
 * @param out_blks    Length of output blocks to generate, where one block is 16 bytes.
 */
void OQS_AES256_CTR_inc_stream_blks(void *ctx, uint8_t *out, size_t out_blks);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // OQS_AES_H
