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
//
///////////////////////////////////////////////////
// Last Modification 
// 
//
///////////////////////////////////////////////////
//****m* SAM_sub/operator-
//    NAME
//      operator-
//    SYNOPSIS
//      res = a - b 
//    FUNCTION
//      Define all the functions involving at least one argument
//      of stochastic type which overload the "-" operator
//      in a statement such as "a-b".
//    INPUTS
//      a           - an integer, a float, a double, an mpfr_t object or a stochastic number
//      b           - an integer, a float, a double, an mpfr_t object or a stochastic number 
//      At least one argument must be of stochastic type.
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



#include "SAM.h"
#include "SAM_private.h"



mp_st mp_st::operator-() const 
{
	mp_st res;
	mpfr_d_sub (res.x, 0, x, MPFR_RNDU);
	mpfr_d_sub (res.y, 0, y, MPFR_RNDU);
	mpfr_d_sub (res.z, 0, z, MPFR_RNDU);
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////


mp_st mp_st::operator--()
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_ui (x, x, 1, MPFR_RNDU);
	else mpfr_sub_ui (x, x, 1, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (y, y, 1, MPFR_RNDU);
		mpfr_sub_ui (z, z, 1, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (y, y, 1, MPFR_RNDD);
		mpfr_sub_ui (z, z, 1, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////



mp_st mp_st::operator--(int)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_ui (x, x, 1, MPFR_RNDU);
	else mpfr_sub_ui (x, x, 1, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (y, y, 1, MPFR_RNDU);
		mpfr_sub_ui (z, z, 1, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (y, y, 1, MPFR_RNDD);
		mpfr_sub_ui (z, z, 1, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return initial;
}



///////////////////////////////////////////////////////////////////////////////////////////



mp_st& mp_st::operator-=(const double& a) 
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_d (x, x, a, MPFR_RNDU);
	else mpfr_sub_d (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_d (y, y, a, MPFR_RNDU);
		mpfr_sub_d (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_sub_d (y, y, a, MPFR_RNDD);
		mpfr_sub_d (z, z, a, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



mp_st& mp_st::operator-=(const float& a) 
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_d (x, x, a, MPFR_RNDU);
	else mpfr_sub_d (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_d (y, y, a, MPFR_RNDU);
		mpfr_sub_d (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_sub_d (y, y, a, MPFR_RNDD);
		mpfr_sub_d (z, z, a, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}




mp_st& mp_st::operator-=(const unsigned long& a) 
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_ui (x, x, a, MPFR_RNDU);
	else mpfr_sub_ui (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (y, y, a, MPFR_RNDU);
		mpfr_sub_ui (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (y, y, a, MPFR_RNDD);
		mpfr_sub_ui (z, z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



mp_st& mp_st::operator-=(const long& a) 
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_si (x, x, a, MPFR_RNDU);
	else mpfr_sub_si (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_si (y, y, a, MPFR_RNDU);
		mpfr_sub_si (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_sub_si (y, y, a, MPFR_RNDD);
		mpfr_sub_si (z, z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



mp_st& mp_st::operator-=(const unsigned int& a) 
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_ui (x, x, a, MPFR_RNDU);
	else mpfr_sub_ui (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_ui (y, y, a, MPFR_RNDU);
		mpfr_sub_ui (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_sub_ui (y, y, a, MPFR_RNDD);
		mpfr_sub_ui (z, z, a, MPFR_RNDU);
	}  
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



mp_st& mp_st::operator-=(const int& a) 
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub_si (x, x, a, MPFR_RNDU);
	else mpfr_sub_si (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub_si (y, y, a, MPFR_RNDU);
		mpfr_sub_si (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_sub_si (y, y, a, MPFR_RNDD);
		mpfr_sub_si (z, z, a, MPFR_RNDU);
	}  
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}


///////////////////////////////////////////////////////////////////////////////////////////


mp_st& mp_st::operator-=(const mp_st& a)	
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub (x, x, a.x, MPFR_RNDU);
	else mpfr_sub (x, x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (y, y, a.y, MPFR_RNDU);
		mpfr_sub (z, z, a.z, MPFR_RNDD);
	}
	else {
		mpfr_sub (y, y, a.y, MPFR_RNDD);
		mpfr_sub (z, z, a.z, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if ((initial.accuracy < a.accuracy ? initial.accuracy : a.accuracy) >= 
			nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////

mp_st& mp_st::operator-=(const mpfr_t& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_sub (x, x, a, MPFR_RNDU);
	else mpfr_sub (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_sub (y, y, a, MPFR_RNDU);
		mpfr_sub (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_sub (y, y, a, MPFR_RNDD);
		mpfr_sub (z, z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////



mp_st operator-(const double& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	
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
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
		{instability(&_SAM_cancel_count);
		}
	}
	return res;
}


mp_st operator-(const float& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
		{instability(&_SAM_cancel_count);
		}
	}
	return res;
}


mp_st operator-(const unsigned long& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
		{instability(&_SAM_cancel_count);
		}
	}
	return res;
}


mp_st operator-(const long& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	
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
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
		{instability(&_SAM_cancel_count);
		}
	}
	return res;
}


mp_st operator-(const unsigned int& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
		{instability(&_SAM_cancel_count);
		}
	}
	return res;
}


mp_st operator-(const int& a, const mp_st& b)
{
	mp_st res;
	

	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
		{instability(&_SAM_cancel_count);
		}
	}
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////


mp_st operator-(const mpfr_t& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


///////////////////////////////////////////////////////////////////////////////////////////



mp_st operator-(const mp_st& a, const double& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator-(const mp_st& a, const float& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator-(const mp_st& a, const unsigned long& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator-(const mp_st& a, const long& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator-(const mp_st& a, const unsigned int& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator-(const mp_st& a, const int& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////



mp_st operator-(const mp_st& a, const mpfr_t& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////


mp_st operator-(const mp_st& a, const mp_st& b)
{
	mp_st res;

	res.accuracy=DIGIT_NOT_COMPUTED;
	
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
	
	if (_SAM_cancel_tag){	
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if ((a.accuracy < b.accuracy ? a.accuracy: b.accuracy) >= 
			res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}









