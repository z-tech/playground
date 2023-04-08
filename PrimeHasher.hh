class PrimeHasher {
  public:
    static BIGNUM * bn_to_prime(const BIGNUM * bn);
    static std::vector<BIGNUM*> &bn_vec_to_primes(std::vector<BIGNUM*> const &src);
    static std::vector<BIGNUM*> &bn_vec_to_primes_pl(std::vector<BIGNUM*> const &src);
};
