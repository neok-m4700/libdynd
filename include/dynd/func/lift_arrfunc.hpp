//
// Copyright (C) 2011-14 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DYND__LIFT_ARRFUNC_HPP_
#define _DYND__LIFT_ARRFUNC_HPP_

#include <dynd/config.hpp>
#include <dynd/array.hpp>
#include <dynd/func/arrfunc.hpp>

namespace dynd {

/**
 * Lifts the provided arrfunc, so it broadcasts all the arguments.
 *
 * \param out_af  The output arrfunc which is filled.
 * \param af  The arrfunc to be lifted.
 */
void lift_arrfunc(arrfunc_type_data *out_af, const nd::arrfunc &af);

} // namespace dynd

#endif // _DYND__LIFT_ARRFUNC_HPP_
