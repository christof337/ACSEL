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
// Last Modification 
//
//
///////////////////////////////////////////////////
//****m* SAM_add/operator+
//    NAME
//      operator+
//    SYNOPSIS
//      res = a + b 
//    FUNCTION
//    Defines all the functions involving at least one
//    stochastic argument which overload the  "+" operator 
//    in a statement such as "a+b" or "+a".      
//      
//      
//    INPUTS
//      a           - an integer, a float, a double, an mpfr_t object or a stochastic number
//      b           - an integer, a float, a double, an mpfr_t object or a stochastic number
//      At least one argument must be of stochastic type.
//     
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

mp_st mp_st::operator+() const
{
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////


mp_st mp_st::operator++()
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (x, x, 1, MPFR_RNDU);
	else mpfr_add_ui (x, x, 1, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (y, y, 1, MPFR_RNDU);
		mpfr_add_ui (z, z, 1, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (y, y, 1, MPFR_RNDD);
		mpfr_add_ui (z, z, 1, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////

mp_st mp_st::operator++(int)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (x, x, 1, MPFR_RNDU);
	else mpfr_add_ui (x, x, 1, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (y, y, 1, MPFR_RNDU);
		mpfr_add_ui (z, z, 1, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (y, y, 1, MPFR_RNDD);
		mpfr_add_ui (z, z, 1, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return initial;
}


///////////////////////////////////////////////////////////////////////////////////////////



mp_st& mp_st::operator+=(const float& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_d (x, x, a, MPFR_RNDU);
	else mpfr_add_d (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_d (y, y, a, MPFR_RNDU);
		mpfr_add_d (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_d (y, y, a, MPFR_RNDD);
		mpfr_add_d (z, z, a, MPFR_RNDU);
	}
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}


mp_st& mp_st::operator+=(const double& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_d (x, x, a, MPFR_RNDU);
	else mpfr_add_d (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_d (y, y, a, MPFR_RNDU);
		mpfr_add_d (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_d (y, y, a, MPFR_RNDD);
		mpfr_add_d (z, z, a, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



mp_st& mp_st::operator+=(const unsigned long& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (x, x, a, MPFR_RNDU);
	else mpfr_add_ui (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (y, y, a, MPFR_RNDU);
		mpfr_add_ui (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (y, y, a, MPFR_RNDD);
		mpfr_add_ui (z, z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}


mp_st& mp_st::operator+=(const long& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_si (x, x, a, MPFR_RNDU);
	else mpfr_add_si (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_si (y, y, a, MPFR_RNDU);
		mpfr_add_si (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_si (y, y, a, MPFR_RNDD);
		mpfr_add_si (z, z, a, MPFR_RNDU);
	}  
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}


mp_st& mp_st::operator+=(const unsigned int& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (x, x, a, MPFR_RNDU);
	else mpfr_add_ui (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (y, y, a, MPFR_RNDU);
		mpfr_add_ui (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (y, y, a, MPFR_RNDD);
		mpfr_add_ui (z, z, a, MPFR_RNDU);
	}  
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}


mp_st& mp_st::operator+=(const int& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_add_si (x, x, a, MPFR_RNDU);
	else mpfr_add_si (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_si (y, y, a, MPFR_RNDU);
		mpfr_add_si (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_si (y, y, a, MPFR_RNDD);
		mpfr_add_si (z, z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////

mp_st& mp_st::operator+=(const mpfr_t& a)	
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add (x, x, a, MPFR_RNDU);
	else mpfr_add (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add (y, y, a, MPFR_RNDU);
		mpfr_add (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_add (y, y, a, MPFR_RNDD);
		mpfr_add (z, z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (initial.accuracy==DIGIT_NOT_COMPUTED) initial.nb_significant_digit();
		if (initial.accuracy >=  this->nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////

mp_st& mp_st::operator+=(const mp_st& a)
{
	mp_st initial=*this;
	
	accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add (x, x, a.x, MPFR_RNDU);
	else mpfr_add (x, x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_add (y, y, a.y, MPFR_RNDU);
		mpfr_add (z, z, a.z, MPFR_RNDD);
	}
	else {
		mpfr_add (y, y, a.y, MPFR_RNDD);
		mpfr_add (z, z, a.z, MPFR_RNDU);
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


mp_st operator+(const float& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_d (res.x, b.x, a, MPFR_RNDU);
	else mpfr_add_d (res.x, b.x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_d (res.y, b.y, a, MPFR_RNDU);
		mpfr_add_d (res.z, b.z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_d (res.y, b.y, a, MPFR_RNDD);
		mpfr_add_d (res.z, b.z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const double& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_d (res.x, b.x, a, MPFR_RNDU);
	else mpfr_add_d (res.x, b.x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_d (res.y, b.y, a, MPFR_RNDU);
		mpfr_add_d (res.z, b.z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_d (res.y, b.y, a, MPFR_RNDD);
		mpfr_add_d (res.z, b.z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}



mp_st operator+(const unsigned long& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (res.x, b.x, a, MPFR_RNDU);
	else mpfr_add_ui (res.x, b.x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (res.y, b.y, a, MPFR_RNDU);
		mpfr_add_ui (res.z, b.z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (res.y, b.y, a, MPFR_RNDD);
		mpfr_add_ui (res.z, b.z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const long& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_si (res.x, b.x, a, MPFR_RNDU);
	else mpfr_add_si (res.x, b.x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_si (res.y, b.y, a, MPFR_RNDU);
		mpfr_add_si (res.z, b.z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_si (res.y, b.y, a, MPFR_RNDD);
		mpfr_add_si (res.z, b.z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const unsigned int& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (res.x, b.x, a, MPFR_RNDU);
	else mpfr_add_ui (res.x, b.x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (res.y, b.y, a, MPFR_RNDU);
		mpfr_add_ui (res.z, b.z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (res.y, b.y, a, MPFR_RNDD);
		mpfr_add_ui (res.z, b.z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const int& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_si (res.x, b.x, a, MPFR_RNDU);
	else mpfr_add_si (res.x, b.x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_si (res.y, b.y, a, MPFR_RNDU);
		mpfr_add_si (res.z, b.z, a, MPFR_RNDD);
	}
	else {
		mpfr_add_si (res.y, b.y, a, MPFR_RNDD);
		mpfr_add_si (res.z, b.z, a, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}




///////////////////////////////////////////////////////////////////////////////////////////


mp_st operator+(const mp_st& a, const float& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_add_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_add_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_add_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_add_d (res.z, a.z, b, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const mp_st& a, const double& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_add_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_add_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_add_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_add_d (res.z, a.z, b, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}



mp_st operator+(const mp_st& a, const unsigned long& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_add_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_add_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_add_ui (res.z, a.z, b, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const mp_st& a, const long& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_add_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_add_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_add_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_add_si (res.z, a.z, b, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const mp_st& a, const unsigned int& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_add_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_add_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_add_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_add_ui (res.z, a.z, b, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const mp_st& a, const int& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_add_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_add_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_add_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_add_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_add_si (res.z, a.z, b, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


///////////////////////////////////////////////////////////////////////////////////////////

mp_st operator+(const mpfr_t& a, const mp_st& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add (res.x, b.x, a, MPFR_RNDU);
	else mpfr_add (res.x, b.x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_add (res.y, b.y, a, MPFR_RNDU);
		mpfr_add (res.z, b.z, a, MPFR_RNDD);
	}
	else {
		mpfr_add (res.y, b.y, a, MPFR_RNDD);
		mpfr_add (res.z, b.z, a, MPFR_RNDU);
	}
	
	if (_SAM_cancel_tag){	
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}


mp_st operator+(const mp_st& a, const mpfr_t& b)
{
	mp_st res;
	
	res.accuracy=DIGIT_NOT_COMPUTED;
	if (RANDOM) mpfr_add (res.x, a.x, b, MPFR_RNDU);
	else mpfr_add (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_add (res.y, a.y, b, MPFR_RNDU);
		mpfr_add (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_add (res.y, a.y, b, MPFR_RNDD);
		mpfr_add (res.z, a.z, b, MPFR_RNDU);
	} 
	
	if (_SAM_cancel_tag){ 
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy >= 	res.nb_significant_digit()+_SAM_cancel_value)
			instability(&_SAM_cancel_count);
	}
	return res;
}



///////////////////////////////////////////////////////////////////////////////////////////

mp_st operator+(const mp_st& a, const mp_st& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_add (res.x, a.x, b.x, MPFR_RNDU);
	else mpfr_add (res.x, a.x, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_add (res.y, a.y, b.y, MPFR_RNDU);
		mpfr_add (res.z, a.z, b.z, MPFR_RNDD);
	}
	else {
		mpfr_add (res.y, a.y, b.y, MPFR_RNDD);
		mpfr_add (res.z, a.z, b.z, MPFR_RNDU);
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





