/**
 *  @file
 *  @copyright defined in iwill/LICENSE.txt
 */

#include <iwillio/utilities/tempdir.hpp>

#include <cstdlib>

namespace iwillio { namespace utilities {

fc::path temp_directory_path()
{
   const char* iwill_tempdir = getenv("IWILL_TEMPDIR");
   if( iwill_tempdir != nullptr )
      return fc::path( iwill_tempdir );
   return fc::temp_directory_path() / "iwill-tmp";
}

} } // iwillio::utilities
