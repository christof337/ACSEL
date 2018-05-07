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
#include "SAM.h"
#include "SAM_private.h"
#include <stdlib.h>

////////////////////////////////////////////////////////////////

// error_type=1  -> relative error
// error_type=0  -> absolute error


//****m* SAM_convert/data_st
//    NAME
//      data_st
//    SYNOPSIS
//      res = data_st()
//      res = data_st(x,y) 
//    FUNCTION
//      the data_st(x,y) method allows to take into account data 
//      uncertainty at the initialization of stochastic variables.
//      if y == 0, x is an absolute error
//      else x is a relative error
//
//      the data_st() method perturbs the last bit.
//      
//    INPUTS
//      x           - a double
//      y           - an integer
//    RESULT
//      res         - a stochastic number
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


void mp_st::data_st(const double& e, const int& error_type)
{
	
	if (error_type){
		mpfr_mul_d (x, x, ((double)1.0+(e*rand()/(double)RAND_MAX)), MPFR_RNDU);
		mpfr_mul_d (y, y, ((double)1.0-(e*rand()/(double)RAND_MAX)), MPFR_RNDD);
	}
	else {
		mpfr_add_d (x, x, (e*rand()/(double)RAND_MAX), MPFR_RNDU);
		mpfr_sub_d (y, y, (e*rand()/(double)RAND_MAX), MPFR_RNDD);
	}
	accuracy=DIGIT_NOT_COMPUTED;
	
}




void mp_st::data_st()
{
	
	mpfr_t m,tmp;
	mpfr_init2(m,DEFAULT_PREC);
	mpfr_init2(tmp,DEFAULT_PREC);
	
	
	if (mpfr_equal_p(x, y)){
		
		mpfr_set_si(m,10,MPFR_RNDU);
		mpfr_pow_si(m,m,(int)(DEFAULT_PREC*LOG),MPFR_RNDU);
		mpfr_set_si (tmp, 1, MPFR_RNDU);
		mpfr_add (tmp, tmp, m, MPFR_RNDU);
		mpfr_mul (x, x, tmp, MPFR_RNDU);
		mpfr_div (x, x, m,MPFR_RNDU);
		
		mpfr_set_si(m,10,MPFR_RNDD);
		mpfr_pow_si(m,m,(int)(DEFAULT_PREC*LOG),MPFR_RNDD);
		mpfr_set_si (tmp, -1, MPFR_RNDD);
		mpfr_add (tmp, tmp, m, MPFR_RNDD);
		mpfr_mul (y, y, tmp, MPFR_RNDD);
		mpfr_div (y, y, m,MPFR_RNDD);
	}
	
	
	accuracy=DIGIT_NOT_COMPUTED;
}


//****m* SAM_convert/float
//    NAME
//       float
//    SYNOPSIS
//      res = (float)x 
//    FUNCTION
//      
//      
//    INPUTS
//      x           - a stochastic
//    RESULT
//      res         - a float
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



//****m* SAM_convert/double
//    NAME
//       double
//    SYNOPSIS
//      res = (double)x 
//    FUNCTION
//      
//      
//    INPUTS
//      x           - a stochastic
//    RESULT
//      res         - a double
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
// /

//****m* SAM_convert/long
//    NAME
//       long
//    SYNOPSIS
//      res = (long)x 
//    FUNCTION
//      
//      
//    INPUTS
//      x           - a stochastic
//    RESULT
//      res         - a long
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

//****m* SAM_convert/unsigned long
//    NAME
//       unsigned long
//    SYNOPSIS
//      res = (unsigned long)x 
//    FUNCTION
//      
//      
//    INPUTS
//      x           - a stochastic
//    RESULT
//      res         - an unsigned long
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

//****m* SAM_convert/int
//    NAME
//       int
//    SYNOPSIS
//      res = (int)x 
//    FUNCTION
//      
//      
//    INPUTS
//      x           - a stochastic
//    RESULT
//      res         - an int
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

//****m* SAM_convert/unsigned int
//    NAME
//       unsigned int
//    SYNOPSIS
//      res = (unsigned int)x 
//    FUNCTION
//      
//      
//    INPUTS
//      x           - a stochastic
//    RESULT
//      res         - an unsigned int
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


mp_st::operator double()
{
    double x_c, y_c, z_c;
    x_c = mpfr_get_d (x, MPFR_RNDN);
    y_c = mpfr_get_d (y, MPFR_RNDN);
    z_c = mpfr_get_d (z, MPFR_RNDN);
	
    if (_SAM_intrinsic_tag)
    { 
       
        if (y_c!=x_c || z_c!=x_c) 
			instability(&_SAM_intrinsic_count); 
			} 
    return ((double)(x_c + y_c + z_c)/3.);	
}


mp_st::operator float()
{

    float x_c, y_c, z_c;
    x_c = mpfr_get_d (x, MPFR_RNDN);
    y_c = mpfr_get_d (y, MPFR_RNDN);
    z_c = mpfr_get_d (z, MPFR_RNDN);
	
    if (_SAM_intrinsic_tag)
    { 
        
        if (y_c!=x_c || z_c!=x_c) 
			instability(&_SAM_intrinsic_count); 
			} 
    return ((float)(x_c + y_c + z_c)/3.);	
}


mp_st::operator unsigned long()
{
   
    unsigned long x_c, y_c, z_c;
    x_c = mpfr_get_ui (x, MPFR_RNDN);
    y_c = mpfr_get_ui (y, MPFR_RNDN);
    z_c = mpfr_get_ui (z, MPFR_RNDN);
	
    if (_SAM_intrinsic_tag)
    { 
        
        if (y_c!=x_c || z_c!=x_c) 
			instability(&_SAM_intrinsic_count); 
			} 
    return ((unsigned long)(x_c + y_c + z_c)/3.);	
}


mp_st::operator long()
{
  
    long x_c, y_c, z_c;
    x_c = mpfr_get_si (x, MPFR_RNDN);
    y_c = mpfr_get_si (y, MPFR_RNDN);
    z_c = mpfr_get_si (z, MPFR_RNDN);
	
    if (_SAM_intrinsic_tag)
    { 
       
        if (y_c!=x_c || z_c!=x_c) 
			instability(&_SAM_intrinsic_count); 
			} 
    return ((long)(x_c + y_c + z_c)/3.);	
}


mp_st::operator unsigned int()
{
  
    unsigned int x_c, y_c, z_c;
    x_c = mpfr_get_ui (x, MPFR_RNDN);
    y_c = mpfr_get_ui (y, MPFR_RNDN);
    z_c = mpfr_get_ui (z, MPFR_RNDN);
	
    if (_SAM_intrinsic_tag)
    { 
        
        if (y_c!=x_c || z_c!=x_c) 
			instability(&_SAM_intrinsic_count); 
			} 
    return ((unsigned int)(x_c + y_c + z_c)/3.);	
}


mp_st::operator int()
{
    int x_c, y_c, z_c;
    x_c = mpfr_get_si (x, MPFR_RNDN);
    y_c = mpfr_get_si (y, MPFR_RNDN);
    z_c = mpfr_get_si (z, MPFR_RNDN);
	
    if (_SAM_intrinsic_tag)
    { 
       
        if (y_c!=x_c || z_c!=x_c) 
		instability(&_SAM_intrinsic_count);
			
			} 
    return ((int)(x_c + y_c + z_c)/3.);	
}






























