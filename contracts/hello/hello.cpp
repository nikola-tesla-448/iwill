#include <iwilliolib/iwillio.hpp>
using namespace iwillio;

class hello : public iwillio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

IWILLIO_ABI( hello, (hi) )
