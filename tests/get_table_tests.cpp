#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <iwillio/testing/tester.hpp>
#include <iwillio/chain/abi_serializer.hpp>
#include <iwillio/chain/wasm_iwillio_constraints.hpp>
#include <iwillio/chain/resource_limits.hpp>
#include <iwillio/chain/exceptions.hpp>
#include <iwillio/chain/wast_to_wasm.hpp>
#include <iwillio/chain_plugin/chain_plugin.hpp>

#include <asserter/asserter.wast.hpp>
#include <asserter/asserter.abi.hpp>

#include <stltest/stltest.wast.hpp>
#include <stltest/stltest.abi.hpp>

#include <iwillio.system/iwillio.system.wast.hpp>
#include <iwillio.system/iwillio.system.abi.hpp>

#include <iwillio.token/iwillio.token.wast.hpp>
#include <iwillio.token/iwillio.token.abi.hpp>

#include <fc/io/fstream.hpp>

#include <Runtime/Runtime.h>

#include <fc/variant_object.hpp>
#include <fc/io/json.hpp>

#include <array>
#include <utility>

#ifdef NON_VALIDATING_TEST
#define TESTER tester
#else
#define TESTER validating_tester
#endif

using namespace iwillio;
using namespace iwillio::chain;
using namespace iwillio::testing;
using namespace fc;

BOOST_AUTO_TEST_SUITE(get_table_tests)

BOOST_FIXTURE_TEST_CASE( get_scope_test, TESTER ) try {
   produce_blocks(2);

   create_accounts({ N(iwillio.token), N(iwillio.ram), N(iwillio.ramfee), N(iwillio.stake),
      N(iwillio.bpay), N(iwillio.vpay), N(iwillio.saving), N(iwillio.names) });

   std::vector<account_name> accs{N(inita), N(initb), N(initc), N(initd)};
   create_accounts(accs);
   produce_block();

   set_code( N(iwillio.token), iwillio_token_wast );
   set_abi( N(iwillio.token), iwillio_token_abi );
   produce_blocks(1);

   // create currency 
   auto act = mutable_variant_object()
         ("issuer",       "iwillio")
         ("maximum_supply", iwillio::chain::asset::from_string("1000000000.0000 SYS"));
   push_action(N(iwillio.token), N(create), N(iwillio.token), act );

   // issue
   for (account_name a: accs) {
      push_action( N(iwillio.token), N(issue), "iwillio", mutable_variant_object()
                  ("to",      name(a) )
                  ("quantity", iwillio::chain::asset::from_string("999.0000 SYS") )
                  ("memo", "")
                  );
   }
   produce_blocks(1);

   // iterate over scope
   iwillio::chain_apis::read_only plugin(*(this->control), fc::microseconds(INT_MAX));
   iwillio::chain_apis::read_only::get_table_by_scope_params param{N(iwillio.token), N(accounts), "inita", "", 10};
   iwillio::chain_apis::read_only::get_table_by_scope_result result = plugin.read_only::get_table_by_scope(param);

   BOOST_REQUIRE_EQUAL(4, result.rows.size());
   BOOST_REQUIRE_EQUAL("", result.more);
   if (result.rows.size() >= 4) {
      BOOST_REQUIRE_EQUAL(name(N(iwillio.token)), result.rows[0].code);
      BOOST_REQUIRE_EQUAL(name(N(inita)), result.rows[0].scope);
      BOOST_REQUIRE_EQUAL(name(N(accounts)), result.rows[0].table);
      BOOST_REQUIRE_EQUAL(name(N(iwillio)), result.rows[0].payer);
      BOOST_REQUIRE_EQUAL(1, result.rows[0].count);

      BOOST_REQUIRE_EQUAL(name(N(initb)), result.rows[1].scope);
      BOOST_REQUIRE_EQUAL(name(N(initc)), result.rows[2].scope);
      BOOST_REQUIRE_EQUAL(name(N(initd)), result.rows[3].scope);
   }

   param.lower_bound = "initb";
   param.upper_bound = "initd";
   result = plugin.read_only::get_table_by_scope(param);
   BOOST_REQUIRE_EQUAL(2, result.rows.size());
   BOOST_REQUIRE_EQUAL("", result.more);
   if (result.rows.size() >= 2) {
      BOOST_REQUIRE_EQUAL(name(N(initb)), result.rows[0].scope);
      BOOST_REQUIRE_EQUAL(name(N(initc)), result.rows[1].scope);      
   }

   param.limit = 1;
   result = plugin.read_only::get_table_by_scope(param);
   BOOST_REQUIRE_EQUAL(1, result.rows.size());
   BOOST_REQUIRE_EQUAL("initc", result.more);

   param.table = name(0);
   result = plugin.read_only::get_table_by_scope(param);
   BOOST_REQUIRE_EQUAL(1, result.rows.size());
   BOOST_REQUIRE_EQUAL("initc", result.more);

   param.table = N(invalid);
   result = plugin.read_only::get_table_by_scope(param);
   BOOST_REQUIRE_EQUAL(0, result.rows.size());
   BOOST_REQUIRE_EQUAL("", result.more); 

} FC_LOG_AND_RETHROW() /// get_scope_test

BOOST_AUTO_TEST_SUITE_END()

