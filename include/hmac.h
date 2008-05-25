/*************************************************
* HMAC Header File                               *
* (C) 1999-2007 The Botan Project                *
*************************************************/

#ifndef BOTAN_HMAC_H__
#define BOTAN_HMAC_H__

#include <botan/base.h>
#include <botan/pointers.h>

namespace Botan {

/*************************************************
* HMAC                                           *
*************************************************/
class HMAC : public MessageAuthenticationCode
   {
   public:
      void clear() throw();
      std::string name() const;
      MessageAuthenticationCode::AutoMACPtr clone() const;
      HMAC(const std::string&);
      ~HMAC() { } 
   private:
      void add_data(const byte[], u32bit);
      void final_result(byte[]);
      void key(const byte[], u32bit);
      std::tr1::shared_ptr<HashFunction> hash;
      SecureVector<byte> i_key, o_key;
   };

}

#endif
