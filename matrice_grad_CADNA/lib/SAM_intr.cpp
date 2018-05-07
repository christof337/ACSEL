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

////////////////////////////////////


//****f* SAM_intr/fabs
//    NAME
//      fabs
//
//    SYNOPSIS
//      res = fabs(x) 
//
//    FUNCTION
//       The fabs() functions compute the absolute value of a
//       stochastic number x.
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /

mp_st fabs(const mp_st& a)
{
	if (_SAM_intrinsic_tag){
		int sum=(mpfr_sgn(a.x)>0)+(mpfr_sgn(a.y)>0)+(mpfr_sgn(a.z)>0);
		if ( sum==1 || sum==2)
			instability(&_SAM_intrinsic_count);
	}
	if (mpfr_sgn(a.x)>=0) return(a);
	else {
		mp_st res;
		res.accuracy=DIGIT_NOT_COMPUTED;
		mpfr_neg(res.x, a.x, MPFR_RNDN);
		mpfr_neg(res.y, a.y, MPFR_RNDN);
		mpfr_neg(res.z, a.z, MPFR_RNDN);
		return(res);
	}
}


////////////////////////////////////////////////////////////////////////

//****f* SAM_intr/floor
//    NAME
//      floor
//
//    SYNOPSIS
//      res = floor(x) 
//
//    FUNCTION
//       The floor() functions return the largest integral value less
//       than or equal to x.
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /

mp_st floor(const mp_st& a)
{
    mp_st res;
    mpfr_floor (res.x, a.x);
    mpfr_floor (res.y, a.y);
    mpfr_floor (res.z, a.z);
    res.accuracy=DIGIT_NOT_COMPUTED;
    if (_SAM_intrinsic_tag)
		if (mpfr_equal_p(res.x, res.y)==0 || mpfr_equal_p(res.z, res.y)==0) 
			instability(&_SAM_intrinsic_count);
	return(res);
}

////////////////////////////////////////////////////////////////////////


//****f* SAM_intr/ceil
//    NAME
//      ceil
//
//    SYNOPSIS
//      res = ceil(x) 
//
//    FUNCTION
//       The ceil() functions return the smallest integral value
//       greater than or equal to x.
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /


mp_st ceil(const mp_st& a)
{
    mp_st res;
    mpfr_ceil (res.x, a.x);
    mpfr_ceil (res.y, a.y);
    mpfr_ceil (res.z, a.z);
    res.accuracy=DIGIT_NOT_COMPUTED;
    if (_SAM_intrinsic_tag)
		if (mpfr_equal_p(res.x, res.y)==0 || mpfr_equal_p(res.z, res.y)==0)
			instability(&_SAM_intrinsic_count);
	return(res);
}


////////////////////////////////////////////////////////////////////////


//****f* SAM_intr/trunc
//    NAME
//      trunc
//
//    SYNOPSIS
//      res = trunc(x) 
//
//    FUNCTION
//       The trunc() functions return the integral value nearest to
//       but no larger in magnitude than x.
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /

mp_st trunc(const mp_st& a)
{ 
    mp_st res;
    mpfr_trunc (res.x, a.x);
    mpfr_trunc (res.y, a.y);
    mpfr_trunc (res.z, a.z);
    res.accuracy=DIGIT_NOT_COMPUTED;
    if (_SAM_intrinsic_tag)
		if (mpfr_equal_p(res.x, res.y)==0 || mpfr_equal_p(res.z, res.y)==0) 
			instability(&_SAM_intrinsic_count);
	return(res);
}


////////////////////////////////////////////////////////////////////////

//****f* SAM_intr/nearbyint
//    NAME
//      nearbyint
//
//    SYNOPSIS
//      res = nearbyint(x) 
//
//    FUNCTION
//      The nearbyint() functions return the integral value
//      (represented as a double precision number) nearest to x
//      according to the prevailing rounding mode.
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /


mp_st nearbyint(const mp_st& a)
{ 
    mp_st res;
    double x_d, y_d, z_d;
    cerr << "SAM WARNING: the nearbyint function is not SAM compatible" << endl;
    x_d = mpfr_get_d (a.x, MPFR_RNDN);
    y_d = mpfr_get_d (a.y, MPFR_RNDN);
    z_d = mpfr_get_d (a.z, MPFR_RNDN);
    mpfr_set_d (res.x, nearbyint(x_d), MPFR_RNDN);
    mpfr_set_d (res.y, nearbyint(y_d), MPFR_RNDN);
    mpfr_set_d (res.z, nearbyint(z_d), MPFR_RNDN);
    res.accuracy=DIGIT_NOT_COMPUTED;
    if (_SAM_intrinsic_tag)
		if (mpfr_equal_p(res.x, res.y)==0 || mpfr_equal_p(res.z, res.y)==0) 
			instability(&_SAM_intrinsic_count);
    return(res);
}


////////////////////////////////////////////////////////////////////////

//****f* SAM_intr/rint
//    NAME
//      rint
//
//    SYNOPSIS
//      res = rint(x) 
//
//    FUNCTION
//       The rint() functions return the integral value nearest to x
//       (according to the prevailing rounding mode) in floating-point
//       format.
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /


mp_st rint(const mp_st& a)
{ 
    mp_st res;
    cerr << "SAM WARNING: the rint function is not SAM compatible" << endl;
    mpfr_rint (res.x, a.x, MPFR_RNDN);
    mpfr_rint (res.y, a.y, MPFR_RNDN);
    mpfr_rint (res.z, a.z, MPFR_RNDN);
    res.accuracy=DIGIT_NOT_COMPUTED;
    if (_SAM_intrinsic_tag)
		if (mpfr_equal_p(res.x, res.y)==0 || mpfr_equal_p(res.z, res.y)==0) 
			instability(&_SAM_intrinsic_count);
    return(res);
}


////////////////////////////////////////////////////////////////////////


//****f* SAM_intr/lrint
//    NAME
//      lrint
//
//    SYNOPSIS
//      res = lrint(x) 
//
//    FUNCTION
//      The lrint() functions return the integral value nearest to x
//      (according to the prevailing rounding mode) in the return
//      formats specified.  If the rounded value is outside the range
//      of the return type, the numeric result is unspecified and the
//      "invalid" floating-point exception is raised. A range error
//      may occur if the magnitude of x is too large.

//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - long int
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /



long int lrint(const mp_st& a)
{ 
	long int res1, res2,res3;
	double x_d, y_d, z_d;
	cerr << "SAM WARNING: the rint function is not SAM compatible" << endl;
	x_d = mpfr_get_d (a.x, MPFR_RNDN);
	y_d = mpfr_get_d (a.y, MPFR_RNDN);
	z_d = mpfr_get_d (a.z, MPFR_RNDN);
	res1 = lrint(x_d);
	res2 = lrint(y_d);
	res3 = lrint(z_d);
	if (_SAM_intrinsic_tag)
		if (res1 != res2 || res2!=res3) 
			instability(&_SAM_intrinsic_count);
	return(res1);
}


////////////////////////////////////////////////////////////////////////

//****f* SAM_intr/llrint
//    NAME
//      llrint
//
//    SYNOPSIS
//      res = llrint(x) 
//
//    FUNCTION 
//
//      The llrint() functions return the integral value nearest to x
//      (according to the prevailing rounding mode) in the return
//      formats specified.  If the rounded value is outside the range
//      of the return type, the numeric result is unspecified and the
//      "invalid" floating-point exception is raised. A range error
//      may occur if the magnitude of x is too large.
//
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - long long int
//    SEE ALSO
//      abs(3), ceil(3), floor(3), rint(3)
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
//      
//      
//  /

long long int llrint(const mp_st& a)
{ 
	long long int res1, res2,res3;
	double x_d, y_d, z_d;
	cerr << "SAM WARNING: the rint function is not SAM compatible" << endl;
	x_d = mpfr_get_d (a.x, MPFR_RNDN);
	y_d = mpfr_get_d (a.y, MPFR_RNDN);
	z_d = mpfr_get_d (a.z, MPFR_RNDN);
	res1 = llrint(x_d);
	res2 = llrint(y_d);
	res3 = llrint(z_d);
	if (_SAM_intrinsic_tag)
		if (res1 != res2 || res2!=res3) 
			instability(&_SAM_intrinsic_count);
	return(res1);
}


////////////////////////////////////








