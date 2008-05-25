/*************************************************
* PBE Retrieval Source File                      *
* (C) 1999-2007 The Botan Project                *
*************************************************/

#include <botan/oids.h>
#include <botan/lookup.h>
#include <botan/pbe_pkcs.h>
#include <botan/parsing.h>
#include <iostream>

namespace Botan {

/*************************************************
* Get an encryption PBE, set new parameters      *
*************************************************/
std::tr1::shared_ptr<PBE> get_pbe(const std::string& pbe_name)
   {
   std::vector<std::string> algo_name;
   algo_name = parse_algorithm_name(pbe_name);

   if(algo_name.size() != 3)
      throw Invalid_Algorithm_Name(pbe_name);

   const std::string pbe = algo_name[0];
   const std::string digest = algo_name[1];
   const std::string cipher = algo_name[2];

   std::tr1::shared_ptr<PBE> pbe_obj;

   if(pbe == "PBE-PKCS5v15")
      pbe_obj = create_shared_ptr<PBE_PKCS5v15>(digest, cipher, ENCRYPTION);
   else if(pbe == "PBE-PKCS5v20") {
      pbe_obj = create_shared_ptr<PBE_PKCS5v20>(digest, cipher);
   }
   if(!pbe_obj.get())
      throw Algorithm_Not_Found(pbe_name);

   pbe_obj->new_params();

   return pbe_obj;
   }



/*************************************************
* Get a decryption PBE, decode parameters        *
*************************************************/
std::tr1::shared_ptr<PBE> get_pbe(const OID& pbe_oid, SharedPtrConverter<DataSource> params)
   {
   std::vector<std::string> algo_name;
   algo_name = parse_algorithm_name(OIDS::lookup(pbe_oid));

   if(algo_name.size() < 1)
      throw Invalid_Algorithm_Name(pbe_oid.as_string());
   const std::string pbe_algo = algo_name[0];

   if(pbe_algo == "PBE-PKCS5v15")
      {
      if(algo_name.size() != 3)
         throw Invalid_Algorithm_Name(pbe_oid.as_string());
      const std::string digest = algo_name[1];
      const std::string cipher = algo_name[2];
      std::tr1::shared_ptr<PBE> pbe = create_shared_ptr<PBE_PKCS5v15>(digest, cipher, DECRYPTION);
      pbe->decode_params(params.get_shared());
      return pbe;
      }
   else if(pbe_algo == "PBE-PKCS5v20")
      {
        return create_shared_ptr<PBE_PKCS5v20>(params.get_shared());
      }

   throw Algorithm_Not_Found(pbe_oid.as_string());
   }

}
