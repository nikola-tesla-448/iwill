/**
 *  @file
 *  @copyright defined in iwill/LICENSE.txt
 */
#include <iwilliolib/iwillio.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   iwillio_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   iwillio_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   iwillio_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   iwillio_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   iwillio_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   iwillio_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   iwillio_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   iwillio_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   iwillio_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   iwillio_assert( sizeof(time) ==  4, "time size !=  4");
   iwillio_assert( sizeof(iwillio::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   iwillio_assert( iwillio::char_to_symbol('1') ==  1, "iwillio::char_to_symbol('1') !=  1");
   iwillio_assert( iwillio::char_to_symbol('2') ==  2, "iwillio::char_to_symbol('2') !=  2");
   iwillio_assert( iwillio::char_to_symbol('3') ==  3, "iwillio::char_to_symbol('3') !=  3");
   iwillio_assert( iwillio::char_to_symbol('4') ==  4, "iwillio::char_to_symbol('4') !=  4");
   iwillio_assert( iwillio::char_to_symbol('5') ==  5, "iwillio::char_to_symbol('5') !=  5");
   iwillio_assert( iwillio::char_to_symbol('a') ==  6, "iwillio::char_to_symbol('a') !=  6");
   iwillio_assert( iwillio::char_to_symbol('b') ==  7, "iwillio::char_to_symbol('b') !=  7");
   iwillio_assert( iwillio::char_to_symbol('c') ==  8, "iwillio::char_to_symbol('c') !=  8");
   iwillio_assert( iwillio::char_to_symbol('d') ==  9, "iwillio::char_to_symbol('d') !=  9");
   iwillio_assert( iwillio::char_to_symbol('e') == 10, "iwillio::char_to_symbol('e') != 10");
   iwillio_assert( iwillio::char_to_symbol('f') == 11, "iwillio::char_to_symbol('f') != 11");
   iwillio_assert( iwillio::char_to_symbol('g') == 12, "iwillio::char_to_symbol('g') != 12");
   iwillio_assert( iwillio::char_to_symbol('h') == 13, "iwillio::char_to_symbol('h') != 13");
   iwillio_assert( iwillio::char_to_symbol('i') == 14, "iwillio::char_to_symbol('i') != 14");
   iwillio_assert( iwillio::char_to_symbol('j') == 15, "iwillio::char_to_symbol('j') != 15");
   iwillio_assert( iwillio::char_to_symbol('k') == 16, "iwillio::char_to_symbol('k') != 16");
   iwillio_assert( iwillio::char_to_symbol('l') == 17, "iwillio::char_to_symbol('l') != 17");
   iwillio_assert( iwillio::char_to_symbol('m') == 18, "iwillio::char_to_symbol('m') != 18");
   iwillio_assert( iwillio::char_to_symbol('n') == 19, "iwillio::char_to_symbol('n') != 19");
   iwillio_assert( iwillio::char_to_symbol('o') == 20, "iwillio::char_to_symbol('o') != 20");
   iwillio_assert( iwillio::char_to_symbol('p') == 21, "iwillio::char_to_symbol('p') != 21");
   iwillio_assert( iwillio::char_to_symbol('q') == 22, "iwillio::char_to_symbol('q') != 22");
   iwillio_assert( iwillio::char_to_symbol('r') == 23, "iwillio::char_to_symbol('r') != 23");
   iwillio_assert( iwillio::char_to_symbol('s') == 24, "iwillio::char_to_symbol('s') != 24");
   iwillio_assert( iwillio::char_to_symbol('t') == 25, "iwillio::char_to_symbol('t') != 25");
   iwillio_assert( iwillio::char_to_symbol('u') == 26, "iwillio::char_to_symbol('u') != 26");
   iwillio_assert( iwillio::char_to_symbol('v') == 27, "iwillio::char_to_symbol('v') != 27");
   iwillio_assert( iwillio::char_to_symbol('w') == 28, "iwillio::char_to_symbol('w') != 28");
   iwillio_assert( iwillio::char_to_symbol('x') == 29, "iwillio::char_to_symbol('x') != 29");
   iwillio_assert( iwillio::char_to_symbol('y') == 30, "iwillio::char_to_symbol('y') != 30");
   iwillio_assert( iwillio::char_to_symbol('z') == 31, "iwillio::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      iwillio_assert( iwillio::char_to_symbol((char)i) == 0, "iwillio::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   iwillio_assert( iwillio::string_to_name("a") == N(a) , "iwillio::string_to_name(a)" );
   iwillio_assert( iwillio::string_to_name("ba") == N(ba) , "iwillio::string_to_name(ba)" );
   iwillio_assert( iwillio::string_to_name("cba") == N(cba) , "iwillio::string_to_name(cba)" );
   iwillio_assert( iwillio::string_to_name("dcba") == N(dcba) , "iwillio::string_to_name(dcba)" );
   iwillio_assert( iwillio::string_to_name("edcba") == N(edcba) , "iwillio::string_to_name(edcba)" );
   iwillio_assert( iwillio::string_to_name("fedcba") == N(fedcba) , "iwillio::string_to_name(fedcba)" );
   iwillio_assert( iwillio::string_to_name("gfedcba") == N(gfedcba) , "iwillio::string_to_name(gfedcba)" );
   iwillio_assert( iwillio::string_to_name("hgfedcba") == N(hgfedcba) , "iwillio::string_to_name(hgfedcba)" );
   iwillio_assert( iwillio::string_to_name("ihgfedcba") == N(ihgfedcba) , "iwillio::string_to_name(ihgfedcba)" );
   iwillio_assert( iwillio::string_to_name("jihgfedcba") == N(jihgfedcba) , "iwillio::string_to_name(jihgfedcba)" );
   iwillio_assert( iwillio::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "iwillio::string_to_name(kjihgfedcba)" );
   iwillio_assert( iwillio::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "iwillio::string_to_name(lkjihgfedcba)" );
   iwillio_assert( iwillio::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "iwillio::string_to_name(mlkjihgfedcba)" );
   iwillio_assert( iwillio::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "iwillio::string_to_name(mlkjihgfedcba2)" );
   iwillio_assert( iwillio::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "iwillio::string_to_name(mlkjihgfedcba14)" );

   iwillio_assert( iwillio::string_to_name("azAA34") == N(azBB34) , "iwillio::string_to_name N(azBB34)" );
   iwillio_assert( iwillio::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "iwillio::string_to_name AZaz12Bc34" );
   iwillio_assert( iwillio::string_to_name("AAAAAAAAAAAAAAA") == iwillio::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "iwillio::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   iwillio_assert( iwillio::name{iwillio::string_to_name("azAA34")}.value == N(azAA34), "iwillio::name != N(azAA34)" );
   iwillio_assert( iwillio::name{iwillio::string_to_name("AABBCC")}.value == 0, "iwillio::name != N(0)" );
   iwillio_assert( iwillio::name{iwillio::string_to_name("AA11")}.value == N(AA11), "iwillio::name != N(AA11)" );
   iwillio_assert( iwillio::name{iwillio::string_to_name("11AA")}.value == N(11), "iwillio::name != N(11)" );
   iwillio_assert( iwillio::name{iwillio::string_to_name("22BBCCXXAA")}.value == N(22), "iwillio::name != N(22)" );
   iwillio_assert( iwillio::name{iwillio::string_to_name("AAAbbcccdd")} == iwillio::name{iwillio::string_to_name("AAAbbcccdd")}, "iwillio::name == iwillio::name" );

   uint64_t tmp = iwillio::name{iwillio::string_to_name("11bbcccdd")};
   iwillio_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
