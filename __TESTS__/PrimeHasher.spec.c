#include "../PrimeHasher.h"

void test_PH_bn_to_prime() {
  // Used this to get random BN:
  //  BIGNUM *b = BN_new();
  //  BN_rand(b, 1024, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY);

  // Load into BN:
  const char bn_rand_dec[] = "77728531348129034983974467072116624635402970881828592987391241438326088241400919233807631936222117822874591962040900395028592224719588739987806722540992579917735365656312235377912029956504172868924068795481811504700758703553469530508476273190236419245066988776481021363203642622172897415912108116908026161411";
  BIGNUM *bn = BN_new();
  BN_dec2bn(&bn, bn_rand_dec);

  // Hash to prime:
  BIGNUM *prime = PH_bn_to_prime(bn);
  //  BN_CTX *ctx = BN_CTX_new();
  //  int isPrime = BN_check_prime(prime, ctx, NULL);
  //  printf("isPrime: %i\n", isPrime);
  //  char * number_str = BN_bn2dec(prime);
  //  printf("%s\n", number_str);

  const char bn_prime_expct_dec[] = "77728531348129034983974467072116624635402970881828592987391241438326088241400919233807631936222117822874591962040900395028592224719588739987806722540992579917735365656312235377912029956504172868924068795481811504700758703553469530508476273190236419245066988776481021363203642622172897415912108116908026161633";
  BIGNUM *bn_expct = BN_new();
  BN_dec2bn(&bn_expct, bn_prime_expct_dec);

  printf("PH_bn_to_prime\n  - it should hash deterministically to a prime");
  if (!BN_cmp(prime, bn_expct)) {
    printf(" PASS\n");
  } else {
    printf(" FAIL\n");
  }

  BN_free(bn);
  BN_free(prime);
  BN_free(bn_expct);
}

int main (int argc, char * argv []) {
  (void) argc;
  (void) argv;
  test_PH_bn_to_prime();
  return 1;
}
