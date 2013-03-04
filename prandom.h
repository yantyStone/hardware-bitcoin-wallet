/** \file prandom.h
  *
  * \brief Describes functions exported by prandom.c.
  *
  * This file is licensed as described by the file LICENCE.
  */

#ifndef PRANDOM_H_INCLUDED
#define PRANDOM_H_INCLUDED

#include "common.h"
#include "bignum256.h"
#include "storage_common.h"

#ifdef TEST
#include "ecdsa.h"
#endif // #ifdef TEST

/** Length, in bytes, of the seed that generateDeterministic256() requires.
  * \warning This must be a multiple of 16 in order for backupWallet() to work
  *          properly.
  */
#define SEED_LENGTH				64
/** Length, in bytes, of the persistent entropy pool. This should be at least
  * 32 to ensure that even in the event of complete undetected failure of the
  * HWRNG, the outputs of getRandom256() still have nearly 256 bits of
  * entropy.
  */
#define ENTROPY_POOL_LENGTH		32
/** Length, in bytes, of the persistent entropy pool checksum. This can be
  * less than 32 because the checksum is only used to detect modification to
  * the persistent entropy pool.
  */
#define POOL_CHECKSUM_LENGTH	16

// Some sanity checks.
#if ENTROPY_POOL_LENGTH > (ADDRESS_POOL_CHECKSUM - ADDRESS_ENTROPY_POOL)
#error ENTROPY_POOL_LENGTH is too big
#endif
#if POOL_CHECKSUM_LENGTH > (ADDRESS_DEVICE_UUID - ADDRESS_POOL_CHECKSUM)
#error POOL_CHECKSUM_LENGTH is too big
#endif

extern void clearParentPublicKeyCache(void);
extern bool setEntropyPool(uint8_t *in_pool_state);
extern bool getEntropyPool(uint8_t *out_pool_state);
extern bool initialiseEntropyPool(uint8_t *initial_pool_state);
extern bool getRandom256(BigNum256 n);
extern bool getRandom256TemporaryPool(BigNum256 n, uint8_t *pool_state);
extern bool generateDeterministic256(BigNum256 out, const uint8_t *seed, const uint32_t num);
#ifdef TEST
extern void initialiseDefaultEntropyPool(void);
extern void corruptEntropyPool(void);
extern void generateDeterministicPublicKey(PointAffine *out_public_key, PointAffine *in_parent_public_key, const uint8_t *chain_code, const uint32_t num);
#endif // #ifdef TEST

#endif // #ifndef PRANDOM_H_INCLUDED
