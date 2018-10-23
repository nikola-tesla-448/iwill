/**
 *  @file
 *  @copyright defined in iwill/LICENSE.txt
 */

#include <iwillio/chain/chain_id_type.hpp>
#include <iwillio/chain/exceptions.hpp>

namespace iwillio { namespace chain {

   void chain_id_type::reflector_verify()const {
      IWILL_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), chain_id_type_exception, "chain_id_type cannot be zero" );
   }

} }  // namespace iwillio::chain

namespace fc {

   void to_variant(const iwillio::chain::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, iwillio::chain::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
