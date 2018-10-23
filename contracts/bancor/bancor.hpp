/**
 *  @file
 *  @copyright defined in iwill/LICENSE.txt
 */
#pragma once

#include <iwilliolib/iwillio.hpp>
#include <iwilliolib/token.hpp>
#include <iwilliolib/reflect.hpp>
#include <iwilliolib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef iwillio::generic_currency< iwillio::token<N(other),S(4,OTHER)> >  other_currency;
   typedef iwillio::generic_currency< iwillio::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef iwillio::generic_currency< iwillio::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

