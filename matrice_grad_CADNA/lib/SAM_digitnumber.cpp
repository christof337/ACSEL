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
#include <math.h>

// ----------------------------------------


// save the rounding mode to compute the number of significant digits
// always with the same rounding mode


//****f* SAM_digitnumber/digitnumber
//    NAME
//      digitnumber
//    SYNOPSIS
//      res = digitnumber(x) 
//      res = x.digitnumber() 
//    FUNCTION
//      The digitnumber() function returns the number of significant
//      digits of a stochastic x
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

int mp_st::nb_significant_digit() const
{
	mp_rnd_t tmp_rnd= mpfr_get_default_rounding_mode();
	mpfr_set_default_rounding_mode(MPFR_RNDN);
	mp_rnd_t default_rnd =mpfr_get_default_rounding_mode();
	
	mpfr_t EPS;
	mpfr_init2 ( EPS, DEFAULT_PREC);
	mpfr_set_d ( EPS, 10.0, default_rnd);
	mpfr_pow_si ( EPS, EPS, -(int)((DEFAULT_PREC*LOG)), default_rnd);
	
	
	mpfr_t x0,x1,x2,xx,yy,tmp,zero;
	mpfr_init2 (x0,DEFAULT_PREC);
	mpfr_init2 (x1,DEFAULT_PREC);
	mpfr_init2 (x2,DEFAULT_PREC);
	mpfr_init2 (xx,DEFAULT_PREC);
	mpfr_init2 (yy,DEFAULT_PREC);
	mpfr_init2 (tmp,DEFAULT_PREC);
	mpfr_init2 (zero,DEFAULT_PREC);

	mpfr_add (xx, x, y, default_rnd);
	mpfr_add (xx, xx, z, default_rnd);  
	mpfr_set_d(zero,0,default_rnd);
	accuracy=0;
	
	if (mpfr_cmp (xx, zero)==0){
        if ( (mpfr_equal_p(x,y)!=0) &&(mpfr_equal_p(x,z)!=0) ) accuracy=(int)(DEFAULT_PREC*LOG); 
		
	}
	else {
        mpfr_ui_div (xx, 3, xx, default_rnd); 
        mpfr_mul (x0, x, xx, default_rnd);
		mpfr_sub_ui (x0, x0, 1, default_rnd); 
        mpfr_mul (x1, y, xx, default_rnd);
		mpfr_sub_ui (x1, x1, 1, default_rnd); 
        mpfr_mul (x2, z, xx, default_rnd);
		mpfr_sub_ui (x2, x2, 1, default_rnd); 
		
        mpfr_sqr (x0, x0, default_rnd);
		mpfr_sqr (x1, x1, default_rnd);
		mpfr_sqr (x2, x2, default_rnd);
		mpfr_add (yy, x0, x1, default_rnd);
		mpfr_add (yy, yy, x2, default_rnd); 
		mpfr_sqrt (yy, yy, default_rnd);
		mpfr_mul_d (yy, yy, 1.7565495069643402, default_rnd);
		if (mpfr_number_p(yy)==0) accuracy=0;
		else {
			
			if (mpfr_cmp(yy, EPS)<=0) {
				accuracy=(int)(DEFAULT_PREC*LOG); 
			}
			else {
				int e = (int)mpfr_get_exp(yy);
				if (e<=0)
					accuracy= (int)(-e*LOG);
			}	
		}
	}
	
	mpfr_set_default_rounding_mode(tmp_rnd);
	
	mpfr_clears(EPS,x0,x1,x2,xx,yy,tmp,(mpfr_ptr) 0);

	return accuracy; 
} 


