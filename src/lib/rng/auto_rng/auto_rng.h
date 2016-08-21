/*
* Auto Seeded RNG
* (C) 2008 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_AUTO_SEEDING_RNG_H__
#define BOTAN_AUTO_SEEDING_RNG_H__

#include <botan/rng.h>

namespace Botan {

class BOTAN_DLL AutoSeeded_RNG final : public RandomNumberGenerator
   {
   public:
      void randomize(byte out[], size_t len) override;

      void randomize_with_input(byte output[], size_t output_len,
                                const byte input[], size_t input_len) override;

      bool is_seeded() const override { return m_rng->is_seeded(); }

      void clear() override { m_rng->clear(); }

      std::string name() const override { return m_rng->name(); }

      size_t reseed(Entropy_Sources& srcs,
                    size_t poll_bits = BOTAN_RNG_RESEED_POLL_BITS,
                    std::chrono::milliseconds poll_timeout = BOTAN_RNG_RESEED_DEFAULT_TIMEOUT) override
         {
         return m_rng->reseed(srcs, poll_bits, poll_timeout);
         }

      void add_entropy(const byte in[], size_t len) override
         { m_rng->add_entropy(in, len); }

      AutoSeeded_RNG(size_t max_output_before_reseed = BOTAN_RNG_DEFAULT_MAX_OUTPUT_BEFORE_RESEED);
   private:
      std::unique_ptr<RandomNumberGenerator> m_rng;
   };

}

#endif
