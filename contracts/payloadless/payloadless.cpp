#include <iwilliolib/iwillio.hpp>
#include <iwilliolib/print.hpp>
using namespace iwillio;

class payloadless : public iwillio::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

IWILLIO_ABI( payloadless, (doit) )
