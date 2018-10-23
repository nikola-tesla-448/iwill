/**
 *  @file
 *  @copyright defined in iwill/LICENSE.txt
 */

#include <iwilliolib/iwillio.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      IWILLLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
