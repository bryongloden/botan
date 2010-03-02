/*
* GOST 34.10-2001
* (C) 2007 Falko Strenzke, FlexSecure GmbH
*          Manuel Hartl, FlexSecure GmbH
* (C) 2008-2009 Jack Lloyd
*
* Distributed under the terms of the Botan license
*/

#ifndef BOTAN_GOST_3410_KEY_H__
#define BOTAN_GOST_3410_KEY_H__

#include <botan/ecc_key.h>

namespace Botan {

/**
* This class represents GOST_3410 Public Keys.
*/
class BOTAN_DLL GOST_3410_PublicKey : public virtual EC_PublicKey,
                                      public PK_Verifying_wo_MR_Key
   {
   public:

      /**
      * Get this keys algorithm name.
      * @result this keys algorithm name
      */
      std::string algo_name() const { return "GOST-34.10"; }

      /**
      * Get the maximum number of bits allowed to be fed to this key.
      * This is the bitlength of the order of the base point.

      * @result the maximum number of input bits
      */
      u32bit max_input_bits() const;

      u32bit message_parts() const { return 2; }

      u32bit message_part_size() const
         { return mp_dom_pars->get_order().bytes(); }

      /**
      * Verify a message with this key.
      * @param message the byte array containing the message
      * @param mess_len the number of bytes in the message byte array
      * @param signature the byte array containing the signature
      * @param sig_len the number of bytes in the signature byte array
      */
      bool verify(const byte message[], u32bit mess_len,
                  const byte signature[], u32bit sig_len) const;

      /**
      * Default constructor. Use this one if you want to later fill
      * this object with data from an encoded key.
      */
      GOST_3410_PublicKey() {}

      /**
      * Construct a public key from a given public point.
      * @param dom_par the domain parameters associated with this key
      * @param public_point the public point defining this key
      */
      GOST_3410_PublicKey(const EC_Domain_Params& dom_par,
                          const PointGFp& public_point); // sets core

      GOST_3410_PublicKey const& operator=(const GOST_3410_PublicKey& rhs);

      GOST_3410_PublicKey(const GOST_3410_PublicKey& other);

      /**
      * Ensure that the public point and domain parameters of this key are set.
      * @throw Invalid_State if either of the two data members is not set
      */
      virtual void affirm_init() const;

      /**
      * Get an x509_encoder that can be used to encode this key.
      * @result an x509_encoder for this key
      */
      X509_Encoder* x509_encoder() const;

      /**
      * Get an x509_decoder that can be used to decode a stored key into
      * this key.
      * @result an x509_decoder for this key
      */
      X509_Decoder* x509_decoder();

   protected:
      void X509_load_hook();
      void set_all_values(const GOST_3410_PublicKey& other);
   };

/**
* This class represents GOST_3410 Private Keys
*/
class BOTAN_DLL GOST_3410_PrivateKey : public GOST_3410_PublicKey,
                                       public EC_PrivateKey,
                                       public PK_Signing_Key
   {
   public:
      /**
      * Default constructor. Use this one if you want to later fill
      * this object with data from an encoded key.
      */
      GOST_3410_PrivateKey() {}

      /**
      * Generate a new private key
      * @param the domain parameters to used for this key
      */
      GOST_3410_PrivateKey(RandomNumberGenerator& rng,
                           const EC_Domain_Params& domain);

      /**
      * Load a private key
      * @param domain parameters
      * @param x the private key
      */
      GOST_3410_PrivateKey(const EC_Domain_Params& domain, const BigInt& x);

      GOST_3410_PrivateKey(const GOST_3410_PrivateKey& other);
      GOST_3410_PrivateKey const& operator=(const GOST_3410_PrivateKey& rhs);

      /**
      * Sign a message with this key.
      * @param message the byte array representing the message to be signed
      * @param mess_len the length of the message byte array
      * @result the signature
      */

      SecureVector<byte> sign(const byte message[], u32bit mess_len,
                              RandomNumberGenerator& rng) const;

      /**
      * Make sure that the public key parts of this object are set
      * (calls EC_PublicKey::affirm_init()) as well as the private key
      * value.
      * @throw Invalid_State if the above conditions are not satisfied
      */
      virtual void affirm_init() const;

   private:
      void set_all_values(const GOST_3410_PrivateKey& other);
      void PKCS8_load_hook(bool = false);
   };

}

#endif
