#ifndef __INCLUDED_E2FCA35C298611E7AA6EA088B4D1658C
#define __INCLUDED_E2FCA35C298611E7AA6EA088B4D1658C

#include <boost/preprocessor.hpp>

/// Enhanced BOOST_PP_EMPTY that supported variable macro arguments
#define RPP_EMPTY(...) BOOST_PP_EMPTY()

/// Enhanced BOOST_PP_COMMA that supported variable macro arguments
#define RPP_COMMA(...) BOOST_PP_COMMA()

#define RPP_COLON(...) :

#define RPP_IF_ARGS_EMPTY_MAIN(trueMacro, falseMacro, ...) \
  BOOST_PP_IF(BOOST_PP_IS_EMPTY(__VA_ARGS__), trueMacro, falseMacro)

#define RPP_IF_ARGS_EMPTY(macro, ...) \
  RPP_IF_ARGS_EMPTY_MAIN(macro, RPP_EMPTY, __VA_ARGS__)

#define RPP_IF_ARGS_NOT_EMPTY(macro, ...) \
  RPP_IF_ARGS_EMPTY_MAIN(RPP_EMPTY, macro, __VA_ARGS__)

#define RPP_CLASS_MEMBER(r, data, elem) \
  BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_CAT(a, BOOST_PP_TUPLE_ELEM(1, elem));

#define RPP_FUNC_ARGUMENT(r, data, elem) \
  BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_CAT(in, BOOST_PP_TUPLE_ELEM(1, elem)) \
  BOOST_PP_COMMA_IF(BOOST_PP_SUB(data, BOOST_PP_DEC(r)))

#define RPP_FUNC_INIT_LIST(r, data, elem) \
  BOOST_PP_CAT(a, BOOST_PP_TUPLE_ELEM(1, elem))( \
    BOOST_PP_CAT(in, BOOST_PP_TUPLE_ELEM(1, elem))) \
  BOOST_PP_COMMA_IF(BOOST_PP_SUB(data, BOOST_PP_DEC(r)))

#define RPP_ARGUMENTS_EXTRACT(macro, ...) \
  BOOST_PP_IF( \
    BOOST_PP_IS_EMPTY(__VA_ARGS__), \
    RPP_EMPTY, \
    BOOST_PP_SEQ_FOR_EACH)(macro, \
                           BOOST_PP_TUPLE_SIZE((__VA_ARGS__)), \
                           BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))

#endif // __INCLUDED_E2FCA35C298611E7AA6EA088B4D1658C
