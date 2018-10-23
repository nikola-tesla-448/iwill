/**
 *  @file
 *  @copyright defined in iwill/LICENSE.txt
 */
#pragma once

#include <iwillio/chain/types.hpp>
#include <iwillio/chain/contract_types.hpp>

namespace iwillio { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_iwillio_newaccount(apply_context&);
   void apply_iwillio_updateauth(apply_context&);
   void apply_iwillio_deleteauth(apply_context&);
   void apply_iwillio_linkauth(apply_context&);
   void apply_iwillio_unlinkauth(apply_context&);

   /*
   void apply_iwillio_postrecovery(apply_context&);
   void apply_iwillio_passrecovery(apply_context&);
   void apply_iwillio_vetorecovery(apply_context&);
   */

   void apply_iwillio_setcode(apply_context&);
   void apply_iwillio_setabi(apply_context&);

   void apply_iwillio_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace iwillio::chain
