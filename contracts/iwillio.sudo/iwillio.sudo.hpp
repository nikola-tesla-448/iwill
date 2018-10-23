#pragma once

#include <iwilliolib/iwillio.hpp>

namespace iwillio {

   class sudo : public contract {
      public:
         sudo( account_name self ):contract(self){}

         void exec();

   };

} /// namespace iwillio
