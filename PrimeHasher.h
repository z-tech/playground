#include <openssl/bn.h>
#include <omp.h>

BIGNUM * PH_bn_to_prime(const BIGNUM * bn);
BIGNUM ** PH_bn_arr_to_primes(int src_len, const BIGNUM *const src[]);
BIGNUM ** PH_bn_arr_to_primes_pl(int src_len, const BIGNUM *const src[]);
