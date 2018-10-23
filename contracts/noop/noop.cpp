/**
 *  @file
 *  @copyright defined in iwill/LICENSE.txt
 */

#include <iwilliolib/iwillio.hpp>

namespace iwillio {

   class noop: public contract {
      public:
         noop( account_name self ): contract( self ) { }
         void anyaction( account_name from,
                         const std::string& /*type*/,
                         const std::string& /*data*/ )
         {
            require_auth( from );
         }
   };

   IWILLIO_ABI( noop, ( anyaction ) )

} /// iwillio     
