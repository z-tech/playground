#include <openssl/bn.h>
#include <omp.h>

#include "PrimeHasher.h"

BIGNUM * PH_bn_to_prime(const BIGNUM * bn) {
  BIGNUM *prime = BN_dup(bn);
  BN_CTX *ctx = BN_CTX_new();
  const BIGNUM * ONE = BN_value_one();
  while(!BN_check_prime(prime, ctx, NULL)) {
    BN_add(prime, prime, ONE);
  }
  return prime;
}

BIGNUM ** PH_bn_arr_to_primes(int src_len, const BIGNUM *const src[]) {
  BIGNUM ** primes = calloc(src_len, sizeof(BIGNUM *));
  for(int i = 0; i < src_len; ++i){
    primes[i] = PH_bn_to_prime(src[i]);
  }
  return primes;
}

// BIGNUM ** PH_bn_arr_to_primes_pl(int src_len, const BIGNUM *const src[]) {
//   BIGNUM ** primes = calloc(src_len, sizeof(BIGNUM *));
//   #pragma omp parallel
//   {
//     #pragma omp for
//     {
//       for(int i = 0; i < src_len; ++i){
//         primes[i] = PH_bn_to_prime(src[i]);
//       }
//     }
//   }
//   return primes;
// }

// Just some notes:
//   BIGNUM * src[] is same as BIGNUM ** src (array of pointers to BIGNUM)
//   const BIGNUM *src[] is read-only array of pointers to BIGNUM (can modify array elements but not what they point to)
//   BIGNUM *const src[] is array of read-only pointers to BIGNUM (cannot modify array elements but can modify what they point to)
//   const BIGNUM *const src[] cannot modify array or what the pointers point
