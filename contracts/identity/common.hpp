#pragma once

#include <iwilliolib/singleton.hpp>
#include <iwilliolib/multi_index.hpp>

namespace identity {

   typedef uint64_t identity_name;
   typedef uint64_t property_name;
   typedef uint64_t property_type_name;

   struct certvalue {
      property_name     property; ///< name of property, base32 encoded i64
      std::string       type; ///< defines type serialized in data
      std::vector<char> data; ///<
      std::string       memo; ///< meta data documenting basis of certification
      uint8_t           confidence = 1; ///< used to define liability for lies,
      /// 0 to delete

      IWILLLIB_SERIALIZE( certvalue, (property)(type)(data)(memo)(confidence) )
   };

   struct certrow {
      uint64_t            id;
      property_name       property;
      uint64_t            trusted;
      account_name        certifier;
      uint8_t             confidence = 0;
      std::string         type;
      std::vector<char>   data;
      uint64_t primary_key() const { return id; }
      /* constexpr */ static iwillio::key256 key(uint64_t property, uint64_t trusted, uint64_t certifier) {
         /*
           key256 key;
           key.uint64s[0] = property;
           key.uint64s[1] = trusted;
           key.uint64s[2] = certifier;
           key.uint64s[3] = 0;
         */
         return iwillio::key256::make_from_word_sequence<uint64_t>(property, trusted, certifier);
      }
      iwillio::key256 get_key() const { return key(property, trusted, certifier); }

      IWILLLIB_SERIALIZE( certrow , (property)(trusted)(certifier)(confidence)(type)(data)(id) )
   };

   struct identrow {
      uint64_t     identity;
      account_name creator;

      uint64_t primary_key() const { return identity; }

      IWILLLIB_SERIALIZE( identrow , (identity)(creator) )
   };

   struct trustrow {
      account_name account;

      uint64_t primary_key() const { return account; }

      IWILLLIB_SERIALIZE( trustrow, (account) )
   };

   typedef iwillio::multi_index<N(certs), certrow,
                              iwillio::indexed_by< N(bytuple), iwillio::const_mem_fun<certrow, iwillio::key256, &certrow::get_key> >
                              > certs_table;
   typedef iwillio::multi_index<N(ident), identrow> idents_table;
   typedef iwillio::singleton<N(account), identity_name>  accounts_table;
   typedef iwillio::multi_index<N(trust), trustrow> trust_table;

   class identity_base {
      public:
         identity_base( account_name acnt) : _self( acnt ) {}

         bool is_trusted_by( account_name trusted, account_name by );

         bool is_trusted( account_name acnt );

      protected:
         account_name _self;
   };

}
