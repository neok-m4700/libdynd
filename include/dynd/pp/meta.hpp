//
// Copyright (C) 2011-14 Irwin Zaid, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DYND__PP_META_HPP_
#define _DYND__PP_META_HPP_

#define DYND_PP_META_ASGN(NAME, A) NAME = A

#define DYND_PP_META_DECL(TYPE, NAME) TYPE NAME
#define DYND_PP_META_DECL_ASGN(TYPE, NAME, A) DYND_PP_META_ASGN(DYND_PP_META_DECL(TYPE, NAME), A)

#define DYND_PP_META_PARENTHESIZE(A) (A)

#define DYND_PP_META_LT(A, B) A < B
#define DYND_PP_META_LE(A, B) A <= B
#define DYND_PP_META_EQ(A, B) A == B
#define DYND_PP_META_NE(A, B) A != B
#define DYND_PP_META_GE(A, B) A >= B
#define DYND_PP_META_GT(A, B) A > B

#define DYND_PP_META_NOT(A) !A
#define DYND_PP_META_AND(A, B) A && B
#define DYND_PP_META_PARENTHESIZED_AND(A, B) DYND_PP_META_PARENTHESIZE(DYND_PP_META_AND(A, B))
#define DYND_PP_META_OR(A, B) A || B
#define DYND_PP_META_PARENTHESIZED_OR(A, B) DYND_PP_META_PARENTHESIZE(DYND_PP_META_OR(A, B))

#define DYND_PP_META_ADD(A, B) A + B
#define DYND_PP_META_ADD_ASGN(A, B) A += B
#define DYND_PP_META_SUB(A, B) A - B
#define DYND_PP_META_SUB_ASGN(A, B) A -= B
#define DYND_PP_META_MUL(A, B) A * B
#define DYND_PP_META_MUL_ASGN(A, B) A *= B
#define DYND_PP_META_DIV(A, B) A / B
#define DYND_PP_META_DIV_ASGN(A, B) A /= B
#define DYND_PP_META_MOD(A, B) A % B
#define DYND_PP_META_MOD_ASGN(A, B) A %= B

#define DYND_PP_META_MAKE_CONST(TYPE) const TYPE

#define DYND_PP_META_MAKE_PTR(TYPE) TYPE *
#define DYND_PP_META_MAKE_CONST_PTR(TYPE) DYND_PP_META_MAKE_CONST(DYND_PP_META_MAKE_PTR(TYPE))

#define DYND_PP_META_MAKE_REF(TYPE) TYPE &
#define DYND_PP_META_MAKE_CONST_REF(TYPE) DYND_PP_META_MAKE_CONST(DYND_PP_META_MAKE_REF(TYPE))

#define DYND_PP_META_AT(NAME, INDEX) NAME[INDEX]
#define DYND_PP_META_DEREFERENCE(NAME) *NAME
#define DYND_PP_META_ADDRESS(NAME) &NAME

#define DYND_PP_META_IF(CONDITION, A) if (CONDITION) {A}
#define DYND_PP_META_IF_ELSE(CONDITION, A, B) if (CONDITION) {A} else {B}

#define DYND_PP_META_TYPEDEF(TYPE, NAME) typedef TYPE NAME
#define DYND_PP_META_TYPENAME(TYPE) typename TYPE
#define DYND_PP_META_TYPEDEF_TYPENAME(TYPE, NAME) typedef typename TYPE NAME

#define DYND_PP_META_TEMPLATE_INSTANTIATION(NAME, ARGS) NAME< ARGS >
#define DYND_PP_META_TEMPLATE_INSTANTIATION_SCOPE(NAME, ARGS, MEMBER) \
    DYND_PP_META_SCOPE(DYND_PP_META_TEMPLATE_INSTANTIATION(NAME, ARGS), MEMBER)
#define DYND_PP_META_TYPENAME_TEMPLATE_INSTANTIATION_SCOPE(NAME, ARGS, MEMBER) \
    DYND_PP_META_TYPENAME(DYND_PP_META_TEMPLATE_INSTANTIATION_SCOPE(NAME, ARGS, MEMBER))

#define DYND_PP_META_CALL(FUNC, ...) FUNC(__VA_ARGS__)

#define DYND_PP_META_DOT(OBJ, MEMBER) OBJ.MEMBER
#define DYND_PP_META_DOT_CALL(OBJ, METH, ...) DYND_PP_META_DOT(OBJ, DYND_PP_META_CALL(METH, __VA_ARGS__))

#define DYND_PP_META_SCOPE(CLS, MEMBER) CLS::MEMBER
#define DYND_PP_META_SCOPE_CALL(CLS, METH, ...) DYND_PP_META_SCOPE(CLS, DYND_PP_META_CALL(METH, __VA_ARGS__))

#define DYND_PP_META_STATIC_CAST(TYPE, NAME) static_cast<TYPE>(NAME)
#define DYND_PP_META_REINTERPRET_CAST(TYPE, NAME) reinterpret_cast<TYPE>(NAME)
#define DYND_PP_META_CONST_CAST(TYPE, NAME) const_cast<TYPE>(NAME)
#define DYND_PP_META_DYNAMIC_CAST(TYPE, NAME) dynamic_cast<TYPE>(NAME)

#define DYND_PP_META_STATIC_ASSERT(CONDITION, MESSAGE) DYND_STATIC_ASSERT(CONDITION, MESSAGE)

// Todo: Implement these in gen.cpp so they are independent of DYND_PP_OUTER
#define DYND_PP_META_NAME_RANGE(NAME, ...) DYND_PP_OUTER_1(DYND_PP_PASTE, (NAME), DYND_PP_RANGE(__VA_ARGS__))
#define DYND_PP_META_AT_RANGE(NAME, ...) DYND_PP_OUTER_1(DYND_PP_META_AT, (NAME), DYND_PP_RANGE(__VA_ARGS__))

// Todo: These need to be removed, and any usage of them needs to be simplified
#define DYND_PP_META_SEMICOLON(...) __VA_ARGS__;
#define DYND_PP_META_SEMI(A, B) A; B;
#define DYND_PP_META_STATEMENTS(A) (DYND_PP_JOIN_1((;), A);)
#define DYND_PP_META_FLAT_CALL(FUNC, ARGS) FUNC ARGS

#endif