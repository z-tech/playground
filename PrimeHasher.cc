#include <iostream>
#include <vector>
#include <omp.h>
#include <openssl/bn.h>

#include "PrimeHasher.hh"

BIGNUM * PrimeHasher::bn_to_prime(const BIGNUM * bn) {
  BIGNUM *prime = BN_dup(bn);
  BN_CTX *ctx = BN_CTX_new();
  const BIGNUM * ONE = BN_value_one();
  while(!BN_check_prime(prime, ctx, NULL)) {
    BN_add(prime, prime, ONE);
  }
  return prime;
}

std::vector<BIGNUM*> &PrimeHasher::bn_vec_to_primes(std::vector<BIGNUM*> const &src) {
  std::vector<BIGNUM*>* primes = new std::vector<BIGNUM*>(src.size());
  for(size_t i = 0; i < src.size(); ++i){
    primes->at(i) = PrimeHasher::bn_to_prime(src[i]);
  }
  return *primes;
}

std::vector<BIGNUM*> &PrimeHasher::bn_vec_to_primes_pl(std::vector<BIGNUM*> const &src) {
  std::vector<BIGNUM*>* primes = new std::vector<BIGNUM*>(src.size());
  omp_set_num_threads(omp_get_num_procs());
  #pragma omp parallel
  {
    #pragma omp for
    {
      for(size_t i = 0; i < src.size(); ++i){
        primes->at(i) = PrimeHasher::bn_to_prime(src[i]);
      }
    }
  }
  return *primes;
}
