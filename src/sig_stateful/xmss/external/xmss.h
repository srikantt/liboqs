#ifndef XMSS_H
#define XMSS_H

#include <stdint.h>
#include <oqs/oqs.h>

#include "xmss_namespace.h"


/**
 * @brief Populates a subkey object with a key that is valid for a certain number of signatures.
 * @attention The caller is responsible for allocating memory and freeing the subkey object.
 * @param master the master key
 * @param subkey the derived key for n signatures
 * @param number_of_sigs the number of signatures that are needed
 * @return int - Returns 0 on success, -1 on failure.
 */
int xmss_derive_subkey(OQS_SECRET_KEY *master, OQS_SECRET_KEY *subkey, unsigned long long number_of_sigs);

/**
 * @brief Populates a subkey object with a key that is valid for a certain number of signatures.
 * @attention The caller is responsible for allocating memory and freeing the subkey object.
 * @param master the master key
 * @param subkey the derived key for n signatures
 * @param number_of_sigs the number of signatures that are needed
 * @return int - Returns 0 on success, -1 on failure.
 */
int xmssmt_derive_subkey(OQS_SECRET_KEY *master, OQS_SECRET_KEY *subkey, unsigned long long number_of_sigs);


#ifdef MAX_MOD

int xmss_modify_maximum(OQS_SECRET_KEY *sk, unsigned long long new_max);

#endif

/**
 * Generates a XMSS key pair for a given parameter set.
 * Format sk: [OID || (32bit) idx || SK_SEED || SK_PRF || PUB_SEED || root]
 * Format pk: [OID || root || PUB_SEED]
 */
int xmss_keypair(uint8_t *pk, OQS_SECRET_KEY *sk, const uint32_t oid);

/**
 * Signs a message using an XMSS secret key.
 * Returns
 * 1. an array containing the signature followed by the message AND
 * 2. an updated secret key!
 */
int xmss_sign(OQS_SECRET_KEY *sk,
              uint8_t *sm, unsigned long long *smlen,
              const uint8_t *m, unsigned long long mlen);

/**
 * Verifies a given message signature pair using a given public key.
 *
 * Note: m and mlen are pure outputs which carry the message in case
 * verification succeeds. The (input) message is assumed to be contained in sm
 * which has the form [signature || message].
 */
int xmss_verify(const uint8_t *m, unsigned long long *mlen,
                   const uint8_t *sm, unsigned long long smlen,
                   const uint8_t *pk);

/*
 * Generates a XMSSMT key pair for a given parameter set.
 * Format sk: [OID || (ceil(h/8) bit) idx || SK_SEED || SK_PRF || PUB_SEED || root]
 * Format pk: [OID || root || PUB_SEED]
 */
int xmssmt_keypair(uint8_t *pk, OQS_SECRET_KEY *sk, const uint32_t oid);

/**
 * Signs a message using an XMSSMT secret key.
 * Returns
 * 1. an array containing the signature followed by the message AND
 * 2. an updated secret key!
 */
int xmssmt_sign(OQS_SECRET_KEY *sk,
                uint8_t *sm, unsigned long long *smlen,
                const uint8_t *m, unsigned long long mlen);

/**
 * Verifies a given message signature pair using a given public key.
 *
 * Note: m and mlen are pure outputs which carry the message in case
 * verification succeeds. The (input) message is assumed to be contained in sm
 * which has the form [signature || message].
 */
int xmssmt_verify(const uint8_t *m, unsigned long long *mlen,
                     const uint8_t *sm, unsigned long long smlen,
                     const uint8_t *pk);
#endif