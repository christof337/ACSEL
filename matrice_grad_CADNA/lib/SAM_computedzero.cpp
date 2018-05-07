/*-----------------------------------------------------------------------
Copyright 2013 S. GRAILLAT, F. JEZEQUEL, S. WANG, Y. ZHU

This file is part of SAM.

    SAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    SAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
    Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with SAM. If not, see
    <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------*/
///////////////////////////////////////////////////
//
// SAM SOFTWARE
//
///////////////////////////////////////////////////
// Last Modifications
// 
//
///////////////////////////////////////////////////

#include "SAM.h"
#include "SAM_private.h"

// save the rounding mode to compute the number of significant digits
// always with the same rounding mode

//****m* SAM_computedzero/computedzero
//    NAME
//      computedzero
//    SYNOPSIS
//      res = computedzero(x) 
//    FUNCTION
//      The computedzero() function returns 1 if x is a stochastic
//      zero, O otherwise.
//      
//      
//    INPUTS
//      x           - a stochastic number
//    RESULT
//      res         - an integer value
//             
//*****
//   You can use this space for remarks that should not be included
//   in the documentation.
//    EXAMPLE
//      
//  
//    NOTES
//  
//  
//    BUGS
//  
//  
//    SEE ALSO
//      
//      
//  /

int mp_st::computedzero() const
{
	int res;
	mpfr_t x0,x1,x2,xx,tmp;
	
	mp_rnd_t default_rnd = mpfr_get_default_rounding_mode();
	mpfr_init2 (x0,DEFAULT_PREC);
	mpfr_init2 (x1,DEFAULT_PREC);
	mpfr_init2 (x2,DEFAULT_PREC);
	mpfr_init2 (xx,DEFAULT_PREC);
	mpfr_init2 (tmp,DEFAULT_PREC);
	mpfr_set_default_rounding_mode(MPFR_RNDN);
	mp_rnd_t tmp_rnd = mpfr_get_default_rounding_mode();
	mpfr_add(xx,x,y,tmp_rnd);
	mpfr_add(xx,xx,z,tmp_rnd);
	
	if (mpfr_cmp_d (xx, 0.0)==0) res=1;
	else {
		mpfr_d_div(xx, 3.0, xx, tmp_rnd);
		mpfr_mul(x0, x, xx, tmp_rnd);
		mpfr_sub_d(x0, x0, 1.0, tmp_rnd);
		mpfr_mul(x1, y, xx, tmp_rnd);
		mpfr_sub_d(x1, x1, 1.0, tmp_rnd);
		mpfr_mul(x2, z, xx, tmp_rnd);
		mpfr_sub_d(x2, x2, 1.0, tmp_rnd);
		mpfr_sqr(x0, x0, tmp_rnd);
		mpfr_sqr(x1, x1, tmp_rnd);
		mpfr_sqr(x2, x2, tmp_rnd);
		mpfr_add(xx, x0, x1, tmp_rnd);
		mpfr_add(xx, xx, x2, tmp_rnd);
		mpfr_mul_d(xx, xx, 3.0854661704166664, tmp_rnd);
		res=(mpfr_cmp_d(xx, 0.1)>0);
	}
	mpfr_set_default_rounding_mode(default_rnd);
	
	mpfr_clears(x0,x1,x2,xx,tmp, (mpfr_ptr) 0);
	return res; 
} 
