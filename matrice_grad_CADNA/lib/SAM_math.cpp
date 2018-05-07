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
/////////////////////////////////////////////////////
// SAM SOFTWARE
//
///////////////////////////////////////////////////
// Last Modifications
//
//
///////////////////////////////////////////////////

#include "SAM.h"
#include "SAM_private.h"

//****f* SAM_math/pow
//    NAME
//      pow
//    SYNOPSIS
//      res = pow(x,y) 
//    FUNCTION
//      The pow() function computes x raised to the power y.
//      
//      
//    INPUTS
//      a           - mp_st
//      b           - mp_st
//    RESULT
//      res         - mp_st
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



mp_st pow(const double& a, const mp_st& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_d (d, a, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, d, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, d, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, d, b.y, MPFR_RNDU);
		mpfr_pow(res.z, d, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, d, b.y, MPFR_RNDD);
		mpfr_pow(res.z, d, b.z, MPFR_RNDU);
	}
	
	mpfr_clear(d);
	return res;
}



mp_st pow(const float& a, const mp_st& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_d (d, a, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, d, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, d, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, d, b.y, MPFR_RNDU);
		mpfr_pow(res.z, d, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, d, b.y, MPFR_RNDD);
		mpfr_pow(res.z, d, b.z, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}





mp_st pow(const unsigned long& a, const mp_st& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_ui (d, a, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, d, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, d, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, d, b.y, MPFR_RNDU);
		mpfr_pow(res.z, d, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, d, b.y, MPFR_RNDD);
		mpfr_pow(res.z, d, b.z, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}



mp_st pow(const long& a, const mp_st& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_si (d, a, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, d, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, d, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, d, b.y, MPFR_RNDU);
		mpfr_pow(res.z, d, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, d, b.y, MPFR_RNDD);
		mpfr_pow(res.z, d, b.z, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}



mp_st pow(const unsigned int& a, const mp_st& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_ui (d, a, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, d, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, d, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, d, b.y, MPFR_RNDU);
		mpfr_pow(res.z, d, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, d, b.y, MPFR_RNDD);
		mpfr_pow(res.z, d, b.z, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}



mp_st pow(const int& a, const mp_st& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_si (d, a, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, d, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, d, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, d, b.y, MPFR_RNDU);
		mpfr_pow(res.z, d, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, d, b.y, MPFR_RNDD);
		mpfr_pow(res.z, d, b.z, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}





/////////////////////////////////////////

mp_st pow(const mpfr_t& a, const mp_st& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_pow(res.x, a, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a, b.y, MPFR_RNDU);
		mpfr_pow(res.z, a, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a, b.y, MPFR_RNDD);
		mpfr_pow(res.z, a, b.z, MPFR_RNDU);
	}
	return res;
}



/////////////////////////////////////////


mp_st pow(const mp_st& a, const double& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_d (d, b, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, a.x, d, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, d, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, d, MPFR_RNDU);
		mpfr_pow(res.z, a.z, d, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, d, MPFR_RNDD);
		mpfr_pow(res.z, a.z, d, MPFR_RNDU);
	}
	
	mpfr_clear(d);
	return res;
}



mp_st pow(const mp_st& a, const float& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_d (d, b, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, a.x, d, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, d, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, d, MPFR_RNDU);
		mpfr_pow(res.z, a.z, d, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, d, MPFR_RNDD);
		mpfr_pow(res.z, a.z, d, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}





mp_st pow(const mp_st& a, const unsigned long& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_ui (d, b, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, a.x, d, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, d, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, d, MPFR_RNDU);
		mpfr_pow(res.z, a.z, d, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, d, MPFR_RNDD);
		mpfr_pow(res.z, a.z, d, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}



mp_st pow(const mp_st& a, const long& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_si (d, b, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, a.x, d, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, d, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, d, MPFR_RNDU);
		mpfr_pow(res.z, a.z, d, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, d, MPFR_RNDD);
		mpfr_pow(res.z, a.z, d, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}



mp_st pow(const mp_st& a, const unsigned int& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_ui (d, b, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, a.x, d, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, d, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, d, MPFR_RNDU);
		mpfr_pow(res.z, a.z, d, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, d, MPFR_RNDD);
		mpfr_pow(res.z, a.z, d, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}



mp_st pow(const mp_st& a, const int& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	mpfr_t d;
	mpfr_init2 (d, DEFAULT_PREC);
	mpfr_set_si (d, b, MPFR_RNDN);
	
	if (RANDOM) mpfr_pow(res.x, a.x, d, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, d, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, d, MPFR_RNDU);
		mpfr_pow(res.z, a.z, d, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, d, MPFR_RNDD);
		mpfr_pow(res.z, a.z, d, MPFR_RNDU);
	}
	mpfr_clear(d);
	return res;
}






/////////////////////////////////////////////////////////////////////////



mp_st pow(const mp_st& a, const mpfr_t& b)
{
	mp_st res; 
	if(_SAM_power_tag!=0){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_power_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_pow(res.x, a.x, b, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, b, MPFR_RNDU);
		mpfr_pow(res.z, a.z, b, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, b, MPFR_RNDD);
		mpfr_pow(res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}


/////////////////////////////////////////


mp_st pow(const mp_st& a, const mp_st& b)
{
	mp_st res;
	if(_SAM_power_tag!=0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (a.accuracy==0 || b.accuracy==0) instability(&_SAM_power_count);
	} 
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_pow(res.x, a.x, b.x, MPFR_RNDU); 
	else mpfr_pow(res.x, a.x, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_pow(res.y, a.y, b.y, MPFR_RNDU);
		mpfr_pow(res.z, a.z, b.z, MPFR_RNDD);
	}
	else{
		mpfr_pow(res.y, a.y, b.y, MPFR_RNDD);
		mpfr_pow(res.z, a.z, b.z, MPFR_RNDU);
	}
	return res; 
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/log
//    NAME
//      log
//
//    SYNOPSIS
//      res = log(x) 
//
//    FUNCTION
//       The log() function computes the value of the natural
//       logarithm of argument x.
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      log2() , log10() , log1p(), exp(3), exp2(3), expm1(3), pow(3)       
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


mp_st  log(const mp_st& a)
{
	mp_st res; 
	if(_SAM_math_tag!=0 || mpfr_cmp_ui(a.x, 0)<0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_log(res.x, a.x, MPFR_RNDU); 
	else mpfr_log(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_log(res.y, a.y, MPFR_RNDU);
		mpfr_log(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_log(res.y, a.y, MPFR_RNDD);
		mpfr_log(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/log2
//    NAME
//      log2
//    SYNOPSIS
//      res = log2(x) 
//    FUNCTION
//      The log2() function computes the value of the logarithm of
//      argument x to base 2.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      log() , log10() , log1p(), exp(3), exp2(3), expm1(3), pow(3)             
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


mp_st  log2(const mp_st& a)
{
	mp_st res;
	if(_SAM_math_tag!=0 || mpfr_cmp_ui(a.x, 0)<0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_log2(res.x, a.x, MPFR_RNDU); 
	else mpfr_log2(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_log2(res.y, a.y, MPFR_RNDU);
		mpfr_log2(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_log2(res.y, a.y, MPFR_RNDD);
		mpfr_log2(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/log10
//    NAME
//       log10
//    SYNOPSIS
//      res =  log10(x) 
//    FUNCTION
//      The log10() function computes the value of the logarithm of
//      argument x to base 10.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      log() , log2() , log1p(), exp(3), exp2(3), expm1(3), pow(3)
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


mp_st  log10(const mp_st& a)
{
	mp_st res;
	if(_SAM_math_tag!=0 || mpfr_cmp_ui(a.x, 0)<0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_log10(res.x, a.x, MPFR_RNDU); 
	else mpfr_log10(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_log10(res.y, a.y, MPFR_RNDU);
		mpfr_log10(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_log10(res.y, a.y, MPFR_RNDD);
		mpfr_log10(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/log1p
//    NAME
//       log1p
//    SYNOPSIS
//      res =  log1p(x) 
//    FUNCTION
//      The log1p() function computes the value of log(1+x) accurately
//      even for very small values of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      log() , log2() , log10(), exp(3), exp2(3), expm1(3), pow(3)
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


mp_st  log1p(const mp_st& a)
{
	mp_st res;
	if(_SAM_math_tag!=0 || mpfr_cmp_ui(a.x, -1)<=0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_log1p(res.x, a.x, MPFR_RNDU); 
	else mpfr_log1p(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_log1p(res.y, a.y, MPFR_RNDU);
		mpfr_log1p(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_log1p(res.y, a.y, MPFR_RNDD);
		mpfr_log1p(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/exp
//    NAME
//       exp
//    SYNOPSIS
//      res =  exp(x) 
//    FUNCTION
//      The exp() function computes e**x, the base-e exponential of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//       log() , log2() , log10() , log1p(), exp2(3), expm1(3), pow(3)
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


mp_st  exp(const mp_st& a)
{
	mp_st res;
	
	if(_SAM_math_tag!=0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_exp(res.x, a.x, MPFR_RNDU); 
	else mpfr_exp(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_exp(res.y, a.y, MPFR_RNDU);
		mpfr_exp(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_exp(res.y, a.y, MPFR_RNDD);
		mpfr_exp(res.z, a.z, MPFR_RNDU);
	}
	return res;
} 

//////////////////////////////////////////////////////////////////////////////
//****f* SAM_math/exp2
//    NAME
//       exp2
//    SYNOPSIS
//      res = exp2(x) 
//    FUNCTION
//      The exp2() function computes 2**x, the base-2 exponential of
//      x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      log() , log2() , log10() , log1p(), exp(3), expm1(3), pow(3)
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

mp_st  exp2(const mp_st& a)
{
	mp_st res;
	
	if(_SAM_math_tag!=0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_exp2(res.x, a.x, MPFR_RNDU); 
	else mpfr_exp2(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_exp2(res.y, a.y, MPFR_RNDU);
		mpfr_exp2(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_exp2(res.y, a.y, MPFR_RNDD);
		mpfr_exp2(res.z, a.z, MPFR_RNDU);
	}
	return res;
} 

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/expm1
//    NAME
//       expm1
//    SYNOPSIS
//      res =  expm1(x) 
//    FUNCTION
//      The expm1() function computes the base-e exponential of x ,
//      minus 1 accurately even for very small values of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      log() , log2() , log10() , log1p(), exp(3), exp2(3), pow(3)
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

mp_st  expm1(const mp_st& a)
{
	mp_st res;
	
	if(_SAM_math_tag!=0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_expm1(res.x, a.x, MPFR_RNDU); 
	else mpfr_expm1(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_expm1(res.y, a.y, MPFR_RNDU);
		mpfr_expm1(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_expm1(res.y, a.y, MPFR_RNDD);
		mpfr_expm1(res.z, a.z, MPFR_RNDU);
	}
	return res;
} 

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/sqrt
//    NAME
//      sqrt
//    SYNOPSIS
//      res = sqrt(x) 
//    FUNCTION
//      The sqrt() function compute the non-negative square root of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      cbrt(3)
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
//      
//  /


mp_st  sqrt(const mp_st& a)
{
	mp_st res;
	if(_SAM_math_tag!=0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_sqrt(res.x, a.x, MPFR_RNDU); 
	else mpfr_sqrt(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sqrt(res.y, a.y, MPFR_RNDU);
		mpfr_sqrt(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_sqrt(res.y, a.y, MPFR_RNDD);
		mpfr_sqrt(res.z, a.z, MPFR_RNDU);
	}
	return res;
} 

//////////////////////////////////////////////////////////////////////////////


//****f* SAM_math/cbrt
//    NAME
//      cbrt
//    SYNOPSIS
//      res = cbrt(x) 
//    FUNCTION
//      The cbrt() function computes the cube root of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      sqrt(3)
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

mp_st  cbrt(const mp_st& a)
{
	mp_st res;
	if(_SAM_math_tag!=0){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0) instability(&_SAM_math_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_cbrt(res.x, a.x, MPFR_RNDU); 
	else mpfr_cbrt(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_cbrt(res.y, a.y, MPFR_RNDU);
		mpfr_cbrt(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_cbrt(res.y, a.y, MPFR_RNDD);
		mpfr_cbrt(res.z, a.z, MPFR_RNDU);
	}
	return res;
} 

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/sin
//    NAME
//      sin
//    SYNOPSIS
//      res = sin(x) 
//    FUNCTION
//      The sin() function computes the sine of x (measured in
//      radians).
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
//      
//  /

mp_st  sin(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_sin(res.x, a.x, MPFR_RNDU); 
	else mpfr_sin(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sin(res.y, a.y, MPFR_RNDU);
		mpfr_sin(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_sin(res.y, a.y, MPFR_RNDD);
		mpfr_sin(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/cos
//    NAME
//      cos
//    SYNOPSIS
//      res = cos(x) 
//    FUNCTION
//      The cos() function computes the cosine of x (measured in
//      radians).
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), sin(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  cos(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_cos(res.x, a.x, MPFR_RNDU); 
	else mpfr_cos(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_cos(res.y, a.y, MPFR_RNDU);
		mpfr_cos(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_cos(res.y, a.y, MPFR_RNDD);
		mpfr_cos(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/tan
//    NAME
//      tan
//    SYNOPSIS
//      res = tan(x) 
//    FUNCTION
//      The tan() function computes the tangent of x (measured in
//      radians).
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      sin(3), tanh(3)
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


mp_st  tan(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_tan(res.x, a.x, MPFR_RNDU); 
	else mpfr_tan(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_tan(res.y, a.y, MPFR_RNDU);
		mpfr_tan(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_tan(res.y, a.y, MPFR_RNDD);
		mpfr_tan(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/asin
//    NAME
//      asin
//    SYNOPSIS
//      res = asin(x) 
//    FUNCTION
//      The asin() function computes the principal value of the arc
//      sine of x.  The result is in the range [-pi/2, +pi/2].
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), sin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  asin(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_asin(res.x, a.x, MPFR_RNDU); 
	else mpfr_asin(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_asin(res.y, a.y, MPFR_RNDU);
		mpfr_asin(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_asin(res.y, a.y, MPFR_RNDD);
		mpfr_asin(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/acos
//    NAME
//      acos
//    SYNOPSIS
//      res = acos(x) 
//    FUNCTION
//      The acos() function computes the principle value of the arc
//      cosine of x.  The result is in the range [0, pi].
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      sin(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  acos(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_acos(res.x, a.x, MPFR_RNDU); 
	else mpfr_acos(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_acos(res.y, a.y, MPFR_RNDU);
		mpfr_acos(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_acos(res.y, a.y, MPFR_RNDD);
		mpfr_acos(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/atan
//    NAME
//      atan
//    SYNOPSIS
//      res = atan(x) 
//    FUNCTION
//      The atan() function computes the principal value of the arc
//      tangent of x.  The result is in the range [-pi/2, +pi/2].
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), sin(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  atan(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_atan(res.x, a.x, MPFR_RNDU); 
	else mpfr_atan(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_atan(res.y, a.y, MPFR_RNDU);
		mpfr_atan(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_atan(res.y, a.y, MPFR_RNDD);
		mpfr_atan(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////



//****f* SAM_math/atan2
//    NAME
//      atan2
//    SYNOPSIS
//      res = atan2(x,y) 
//    FUNCTION
//      The atan2() function computes the principal value of the arc
//      tangent of y/x, using the signs of both arguments to determine
//      the quadrant of the return value.
//      
//      
//    INPUTS
//      x           - mp_st 
//      y           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), sin(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  atan2(const mp_st& a, const mp_st& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_atan2(res.x, a.x, b.x, MPFR_RNDU); 
	else mpfr_atan2(res.x, a.x, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_atan2(res.y, a.y, b.y, MPFR_RNDU);
		mpfr_atan2(res.z, a.z, b.z, MPFR_RNDD);
	}
	else{
		mpfr_atan2(res.y, a.y, b.y, MPFR_RNDD);
		mpfr_atan2(res.z, a.z, b.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/sinh
//    NAME
//      sinh
//    SYNOPSIS
//      res = sinh(x) 
//    FUNCTION
//      The sinh() function computes the hyperbolic sine of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sin(3),
//      tan(3), tanh(3)
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

mp_st  sinh(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_sinh(res.x, a.x, MPFR_RNDU); 
	else mpfr_sinh(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sinh(res.y, a.y, MPFR_RNDU);
		mpfr_sinh(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_sinh(res.y, a.y, MPFR_RNDD);
		mpfr_sinh(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/cosh
//    NAME
//      cosh
//    SYNOPSIS
//      res = cosh(x) 
//    FUNCTION
//      The cosh() function computes the hyperbolic cosine of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), sin(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  cosh(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_cosh(res.x, a.x, MPFR_RNDU); 
	else mpfr_cosh(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_cosh(res.y, a.y, MPFR_RNDU);
		mpfr_cosh(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_cosh(res.y, a.y, MPFR_RNDD);
		mpfr_cosh(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/tanh
//    NAME
//      tanh
//    SYNOPSIS
//      res = tanh(x) 
//    FUNCTION
//      The tanh() function computes the hyperbolic tangent of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), sin(3)
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

mp_st  tanh(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_tanh(res.x, a.x, MPFR_RNDU); 
	else mpfr_tanh(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_tanh(res.y, a.y, MPFR_RNDU);
		mpfr_tanh(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_tanh(res.y, a.y, MPFR_RNDD);
		mpfr_tanh(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/asinh
//    NAME
//      asinh
//    SYNOPSIS
//      res = asinh(x) 
//    FUNCTION
//      The asinh() function computes the inverse hyperbolic sine of x.
//     
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  asinh(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_asinh(res.x, a.x, MPFR_RNDU); 
	else mpfr_asinh(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_asinh(res.y, a.y, MPFR_RNDU);
		mpfr_asinh(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_asinh(res.y, a.y, MPFR_RNDD);
		mpfr_asinh(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/acosh
//    NAME
//      acosh
//    SYNOPSIS
//      res = acosh(x) 
//    FUNCTION
//      The acosh() function computes the inverse hyperbolic cosine of x.
//      
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  acosh(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_acosh(res.x, a.x, MPFR_RNDU); 
	else mpfr_acosh(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_acosh(res.y, a.y, MPFR_RNDU);
		mpfr_acosh(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_acosh(res.y, a.y, MPFR_RNDD);
		mpfr_acosh(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////

//****f* SAM_math/atanh
//    NAME
//      atanh
//    SYNOPSIS
//      res = atanh(x) 
//    FUNCTION
//      The atanh() function computes the inverse hyperbolic tangent
//      of x.
//      
//      
//    INPUTS
//      a           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      acos(3), asin(3), atan(3), atan2(3), cos(3), cosh(3), sinh(3),
//      tan(3), tanh(3)
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

mp_st  atanh(const mp_st& a)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_atanh(res.x, a.x, MPFR_RNDU); 
	else mpfr_atanh(res.x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_atanh(res.y, a.y, MPFR_RNDU);
		mpfr_atanh(res.z, a.z, MPFR_RNDD);
	}
	else{
		mpfr_atanh(res.y, a.y, MPFR_RNDD);
		mpfr_atanh(res.z, a.z, MPFR_RNDU);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////////////
//****f* SAM_math/hypot
//    NAME
//      hypot
//    SYNOPSIS
//      res = hypot(x,y) 
//    FUNCTION
//      The hypot() function computes the sqrt(x*x+y*y) without undue
//      overflow or underflow.
//      
//      
//    INPUTS
//      a           - mp_st
//      b           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      sqrtf(3)
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
// /

mp_st  hypot(const mp_st& a, const mp_st& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_hypot(res.x, a.x, b.x, MPFR_RNDU); 
	else mpfr_hypot(res.x, a.x, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_hypot(res.y, a.y, b.y, MPFR_RNDU);
		mpfr_hypot(res.z, a.z, b.z, MPFR_RNDD);
	}
	else{
		mpfr_hypot(res.y, a.y, b.y, MPFR_RNDD);
		mpfr_hypot(res.z, a.z, b.z, MPFR_RNDU);
	}
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////


//****f* SAM_math/fmax
//    NAME
//      fmax
//    SYNOPSIS
//      res = fmax(x,y) 
//    FUNCTION
//      The fmax() functions return x or y, whichever is larger.
//      
//      
//    INPUTS
//      a           - mp_st 
//      b           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      fmin(3)
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
//      
//  /


mp_st fmax(const double& a, const mp_st& b)
{
	mp_st res;
	double f = 3*a;
	
	if (RANDOM) mpfr_d_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_d_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)<0)
			res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}



mp_st fmax(const float& a, const mp_st& b)
{
	mp_st res;
	double f = 3*a;
	
	if (RANDOM) mpfr_d_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_d_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)<0)
			 res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}






mp_st fmax(const unsigned long& a, const mp_st& b)
{
	mp_st res;
	unsigned long f = 3*a;
	
	if (RANDOM) mpfr_ui_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_ui_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)<0)
			 res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}



mp_st fmax(const long& a, const mp_st& b)
{
	mp_st res;
	long f = 3*a;
	
	if (RANDOM) mpfr_si_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_si_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)<0)
			 res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}



mp_st fmax(const unsigned int& a, const mp_st& b)
{
	mp_st res;
	unsigned int f = 3*a;
	
	if (RANDOM) mpfr_ui_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_ui_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)<0)
			 res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}



mp_st fmax(const int& a, const mp_st& b)
{
	mp_st res;
	int f = 3*a;
	
	if (RANDOM) mpfr_si_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_si_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)<0)
			 res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}








///////////////////////////////////////////////


mp_st fmax(const mpfr_t& a, const mp_st& b)
{
	mp_st res;
	mpfr_t c;
	mpfr_init2 (c, mpfr_get_default_prec());
	
	if (RANDOM) mpfr_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_sub (res.z, a, b.z, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		mpfr_mul_ui (c, a, 3, MPFR_RNDN);
		if ( mpfr_cmp(res.x, c)<0)
		 res=mp_st(a);
		else 
			 res=b;
	}
	mpfr_clear(c);
	return res; 
	
}


///////////////////////////////////////////////


mp_st fmax(const mp_st& a, const double& b)
{
	mp_st res;
	double f = 3*b;
	
	if (RANDOM) mpfr_sub_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)>0)
			 res=a;
		else 
		 res=mp_st(b);
	}
	return res; 
}



mp_st fmax(const mp_st& a, const float& b)
{
	mp_st res;
	float f = 3*b;
	
	if (RANDOM) mpfr_sub_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)>0)
			 res=a;
		else 
			 res=mp_st(b);
	}
	return res; 
}






mp_st fmax(const mp_st& a, const unsigned long& b)
{
	mp_st res;
	unsigned long f = 3*b;
	
	if (RANDOM) mpfr_sub_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)>0)
			 res=a;
		else 
			res=mp_st(b);
	}
	return res; 
}



mp_st fmax(const mp_st& a, const long& b)
{
	mp_st res;
	long f = 3*b;
	
	if (RANDOM) mpfr_sub_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)>0)
			res=a;
		else 
			 res=mp_st(b);
	}
	return res; 
}




mp_st fmax(const mp_st& a, const unsigned int& b)
{
	mp_st res;
	unsigned int f = 3*b;
	
	if (RANDOM) mpfr_sub_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)>0)
		 res=a;
		else 
		 res=mp_st(b);
	}
	return res; 
}




mp_st fmax(const mp_st& a, const int& b)
{
	mp_st res;
	int f = 3*b;
	
	if (RANDOM) mpfr_sub_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)>0)
			 res=a;
		else 
		 res=mp_st(b);
	}
	return res; 
}








///////////////////////////////////////////////



mp_st fmax(const mp_st& a, const mpfr_t& b)
{
	mp_st res;
	mpfr_t c;
	mpfr_init2 (c, mpfr_get_default_prec());
	
	if (RANDOM) mpfr_sub (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		mpfr_mul_ui (c, b, 3, MPFR_RNDN);
		if ( mpfr_cmp(res.x, c)>0)
			res=a;
		else 
			res=mp_st(b);
	}
	mpfr_clear(c);
	return res; 
	
}



///////////////////////////////////////////////



mp_st fmax(const mp_st& a, const mp_st& b)
{
	mp_st res,res1,res2;
	
	if (RANDOM) mpfr_sub (res.x, a.x, b.x, MPFR_RNDU);
	else mpfr_sub (res.x, a.x, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (res.y, a.y, b.y, MPFR_RNDU);
		mpfr_sub (res.z, a.z, b.z, MPFR_RNDD);
	}
	else {
		mpfr_sub (res.y, a.y, b.y, MPFR_RNDD);
		mpfr_sub (res.z, a.z, b.z, MPFR_RNDU);
	}
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r)
		instability(&_SAM_branching_count);
	
	if (r){
		if (a.nb_significant_digit()>b.nb_significant_digit())
			res=a;
		else 
			res=b;
	}
	else {
		mpfr_add(res1.x, a.x, a.y, MPFR_RNDN);
		mpfr_add(res1.x, res1.x, a.z, MPFR_RNDN);
		mpfr_add(res2.x, a.x, a.y, MPFR_RNDN);
		mpfr_add(res2.x, res2.x, a.z, MPFR_RNDN);
		if ( mpfr_greater_p (res1.x, res2.x))
			res=a;
		else
			res=b;
	}
	return res; 
}



///////////////////////////////////


//****f* SAM_math/fmin
//    NAME
//      fmin
//    SYNOPSIS
//      res = fmin(x,y) 
//    FUNCTION
//      The fmin() functions return x or y, whichever is smaller.
//      
//      
//    INPUTS
//      a           - mp_st 
//      b           - mp_st
//    RESULT
//      res         - mp_st
//    SEE ALSO
//      fmax(3)
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


mp_st fmin(const double& a, const mp_st& b)
{
	mp_st res;
	double f = 3*a;
	
	if (RANDOM) mpfr_d_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_d_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)>0)
			res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}



mp_st fmin(const float& a, const mp_st& b)
{
	mp_st res;
	float f = 3*a;
	
	if (RANDOM) mpfr_d_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_d_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_d_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_d_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)>0)
			 res=mp_st(a);
		else 
		 res=b;
	}
	return res; 
}






mp_st fmin(const unsigned long& a, const mp_st& b)
{
	mp_st res;
	unsigned long f = 3*a;
	
	if (RANDOM) mpfr_ui_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_ui_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)>0)
		 res=mp_st(a);
		else 
		 res=b;
	}
	return res; 
}



mp_st fmin(const long& a, const mp_st& b)
{
	mp_st res;
	long f = 3*a;
	
	if (RANDOM) mpfr_si_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_si_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)>0)
		 res=mp_st(a);
		else 
		 res=b;
	}
	return res; 
}



mp_st fmin(const unsigned int& a, const mp_st& b)
{
	mp_st res;
	unsigned int f = 3*a;
	
	if (RANDOM) mpfr_ui_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_ui_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_ui_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_ui_sub (res.z, a, b.z, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)>0)
		 res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}



mp_st fmin(const int& a, const mp_st& b)
{
	mp_st res;
	int f = 3*a;
	
	if (RANDOM) mpfr_si_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_si_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_si_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_si_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)>0)
			 res=mp_st(a);
		else 
			 res=b;
	}
	return res; 
}





///////////////////////////////////////////////



mp_st fmin(const mpfr_t& a, const mp_st& b)
{
	mp_st res;
	mpfr_t c;
	mpfr_init2 (c, mpfr_get_default_prec());
	
	if (RANDOM) mpfr_sub (res.x, a, b.x, MPFR_RNDU);
	else mpfr_sub (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (res.y, a, b.y, MPFR_RNDU);
		mpfr_sub (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_sub (res.y, a, b.y, MPFR_RNDD);
		mpfr_sub (res.z, a, b.z, MPFR_RNDU);
	} 
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r){
		 res = mp_st(a);
	}
	else {
		mpfr_add (res.x, b.x, b.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, b.z, MPFR_RNDN);
		mpfr_mul_ui (c, a, 3, MPFR_RNDN);
		if ( mpfr_cmp(res.x, c)>0)
			res=mp_st(a);
		else 
			 res=b;
	}
	mpfr_clear(c);
	return res; 
	
}


///////////////////////////////////////////////



mp_st fmin(const mp_st& a, const double& b)
{
	mp_st res;
	double f = 3*b;
	
	if (RANDOM) mpfr_sub_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)<0)
			 res=a;
		else 
		 res=b;
	}
	return res; 
}


mp_st fmin(const mp_st& a, const float& b)
{
	mp_st res;
	float f = 3*b;
	
	if (RANDOM) mpfr_sub_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_d (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_d(res.x, f)<0)
			 res=a;
		else 
			 res=b;
	}
	return res; 
}







mp_st fmin(const mp_st& a, const unsigned long& b)
{
	mp_st res;
	unsigned long f = 3*b;
	
	if (RANDOM) mpfr_sub_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)<0)
			 res=a;
		else 
			 res=b;
	}
	return res; 
}



mp_st fmin(const mp_st& a, const long& b)
{
	mp_st res;
	long f = 3*b;
	
	if (RANDOM) mpfr_sub_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)<0)
			 res=a;
		else 
			 res=b;
	}
	return res; 
}



mp_st fmin(const mp_st& a, const unsigned int& b)
{
	mp_st res;
	unsigned int f = 3*b;
	
	if (RANDOM) mpfr_sub_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_ui (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_ui(res.x, f)<0)
			 res=a;
		else 
			 res=b;
	}
	return res; 
}




mp_st fmin(const mp_st& a, const int& b)
{
	mp_st res;
	int f = 3*b;
	
	if (RANDOM) mpfr_sub_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub_si (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r) 
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		if ( mpfr_cmp_si(res.x, f)<0)
			 res=a;
		else 
			 res=b;
	}
	return res; 
}




///////////////////////////////////////////////


mp_st fmin(const mp_st& a, const mpfr_t& b)
{
	mp_st res;
	mpfr_t c;
	mpfr_init2 (c, mpfr_get_default_prec());
	
	if (RANDOM) mpfr_sub (res.x, a.x, b, MPFR_RNDU);
	else mpfr_sub (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (res.y, a.y, b, MPFR_RNDU);
		mpfr_sub (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_sub (res.y, a.y, b, MPFR_RNDD);
		mpfr_sub (res.z, a.z, b, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r)
		instability(&_SAM_branching_count);
	if (r) {
		 res=mp_st(b);
	}
	else {
		mpfr_add (res.x, a.x, a.y, MPFR_RNDN);
		mpfr_add (res.x, res.x, a.z, MPFR_RNDN);
		mpfr_mul_ui (c, b, 3, MPFR_RNDN);
		if ( mpfr_cmp(res.x, c)<0)
			 res=a;
		else 
			 res=mp_st(b);
	}
	mpfr_clear(c);
	return res;
	
}

///////////////////////////////////////////////




mp_st fmin(const mp_st& a, const mp_st& b)
{
	mp_st res,res1,res2;
	
	if (RANDOM) mpfr_sub (res.x, a.x, b.x, MPFR_RNDU);
	else mpfr_sub (res.x, a.x, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (res.y, a.y, b.y, MPFR_RNDU);
		mpfr_sub (res.z, a.z, b.z, MPFR_RNDD);
	}
	else {
		mpfr_sub (res.y, a.y, b.y, MPFR_RNDD);
		mpfr_sub (res.z, a.z, b.z, MPFR_RNDU);
	}
	
	int r=res.computedzero();
	
	if (_SAM_branching_tag && r)
		instability(&_SAM_branching_count);
	
	if (r){
		if (a.nb_significant_digit()>b.nb_significant_digit())
			 res=a;
		else 
			 res=b;
	}
	else {
		mpfr_add(res1.x, a.x, a.y, MPFR_RNDN);
		mpfr_add(res1.x, res1.x, a.z, MPFR_RNDN);
		mpfr_add(res2.x, a.x, a.y, MPFR_RNDN);
		mpfr_add(res2.x, res2.x, a.z, MPFR_RNDN);
		if ( mpfr_greater_p (res2.x, res1.x))
			 res=a;
		else 
			 res=b;
	}
	return res; 
}













