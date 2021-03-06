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
//****m* SAM_div/operator/
//    NAME
//      operator/
//    SYNOPSIS
//      res = a / b 
//    FUNCTION  
//    Define all the functions involving at least one argument
//    of stochastic type which overload the "/" operator
//    in a statement such as "a/b". 
//      
//      
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

mp_st& mp_st::operator/=(const double& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_d (x, x, a, MPFR_RNDU);
	else mpfr_div_d (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_d (y, y, a, MPFR_RNDU);
		mpfr_div_d (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_div_d (y, y, a, MPFR_RNDD);
		mpfr_div_d (z, z, a, MPFR_RNDU);
	}
	return *this;
}


mp_st& mp_st::operator/=(const float& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_d (x, x, a, MPFR_RNDU);
	else mpfr_div_d (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_d (y, y, a, MPFR_RNDU);
		mpfr_div_d (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_div_d (y, y, a, MPFR_RNDD);
		mpfr_div_d (z, z, a, MPFR_RNDU);
	}
	return *this;
}



mp_st& mp_st::operator/=(const unsigned long& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_ui (x, x, a, MPFR_RNDU);
	else mpfr_div_ui (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_ui (y, y, a, MPFR_RNDU);
		mpfr_div_ui (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_div_ui (y, y, a, MPFR_RNDD);
		mpfr_div_ui (z, z, a, MPFR_RNDU);
	}
	return *this;
}


mp_st& mp_st::operator/=(const long& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_si (x, x, a, MPFR_RNDU);
	else mpfr_div_si (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_si (y, y, a, MPFR_RNDU);
		mpfr_div_si (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_div_si (y, y, a, MPFR_RNDD);
		mpfr_div_si (z, z, a, MPFR_RNDU);
	}
	return *this;
}


mp_st& mp_st::operator/=(const unsigned int& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_ui (x, x, a, MPFR_RNDU);
	else mpfr_div_ui (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_ui (y, y, a, MPFR_RNDU);
		mpfr_div_ui (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_div_ui (y, y, a, MPFR_RNDD);
		mpfr_div_ui (z, z, a, MPFR_RNDU);
	}
	return *this;
}


mp_st& mp_st::operator/=(const int& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_si (x, x, a, MPFR_RNDU);
	else mpfr_div_si (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_si (y, y, a, MPFR_RNDU);
		mpfr_div_si (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_div_si (y, y, a, MPFR_RNDD);
		mpfr_div_si (z, z, a, MPFR_RNDU);
	}
	return *this;
}




///////////////////////////////////////////////////////////////////////////////////////////


mp_st& mp_st::operator/=(const mpfr_t& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div (x, x, a, MPFR_RNDU);
	else mpfr_div (x, x, a, MPFR_RNDD);
	if (RANDOM){
		mpfr_div (y, y, a, MPFR_RNDU);
		mpfr_div (z, z, a, MPFR_RNDD);
	}
	else {
		mpfr_div (y, y, a, MPFR_RNDD);
		mpfr_div (z, z, a, MPFR_RNDU);
	}
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////


mp_st& mp_st::operator/=(const mp_st& a)
{
	accuracy=DIGIT_NOT_COMPUTED;
	if(_SAM_div_tag) {
		if (a.accuracy==DIGIT_NOT_COMPUTED) a.nb_significant_digit();
		if (a.accuracy==0)
			instability(&_SAM_div_count);
	}
	
	if (RANDOM) mpfr_div (x, x, a.x, MPFR_RNDU);
	else mpfr_div (x, x, a.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_div (y, y, a.y, MPFR_RNDU);
		mpfr_div (z, z, a.z, MPFR_RNDD);
	}
	else {
		mpfr_div (y, y, a.y, MPFR_RNDD);
		mpfr_div (z, z, a.z, MPFR_RNDU);
	}
	return *this;
}



///////////////////////////////////////////////////////////////////////////////////////////


mp_st operator/(const double& a, const mp_st& b)
{
	mp_st res;
	
	if(_SAM_div_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_d_div (res.x, a, b.x, MPFR_RNDU);
	else mpfr_d_div (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_d_div (res.y, a, b.y, MPFR_RNDU);
		mpfr_d_div (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_d_div (res.y, a, b.y, MPFR_RNDD);
		mpfr_d_div (res.z, a, b.z, MPFR_RNDU);
	}
	
	return res;
}


mp_st operator/(const float& a, const mp_st& b)
{
	mp_st res;
	
	if(_SAM_div_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_d_div (res.x, a, b.x, MPFR_RNDU);
	else mpfr_d_div (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_d_div (res.y, a, b.y, MPFR_RNDU);
		mpfr_d_div (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_d_div (res.y, a, b.y, MPFR_RNDD);
		mpfr_d_div (res.z, a, b.z, MPFR_RNDU);
	}
	
	return res;
}


mp_st operator/(const unsigned long& a, const mp_st& b)
{
	mp_st res;
	
	if(_SAM_div_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_ui_div (res.x, a, b.x, MPFR_RNDU);
	else mpfr_ui_div (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_ui_div (res.y, a, b.y, MPFR_RNDU);
		mpfr_ui_div (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_ui_div (res.y, a, b.y, MPFR_RNDD);
		mpfr_ui_div (res.z, a, b.z, MPFR_RNDU);
	}
	
	return res;
}


mp_st operator/(const long& a, const mp_st& b)
{
	mp_st res;

	if(_SAM_div_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_si_div (res.x, a, b.x, MPFR_RNDU);
	else mpfr_si_div (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_si_div (res.y, a, b.y, MPFR_RNDU);
		mpfr_si_div (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_si_div (res.y, a, b.y, MPFR_RNDD);
		mpfr_si_div (res.z, a, b.z, MPFR_RNDU);
	}
	
	return res;
}



mp_st operator/(const unsigned int& a, const mp_st& b)
{
	mp_st res;
	
	if(_SAM_div_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_ui_div (res.x, a, b.x, MPFR_RNDU);
	else mpfr_ui_div (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_ui_div (res.y, a, b.y, MPFR_RNDU);
		mpfr_ui_div (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_ui_div (res.y, a, b.y, MPFR_RNDD);
		mpfr_ui_div (res.z, a, b.z, MPFR_RNDU);
	}
	
	return res;
}


mp_st operator/(const int& a, const mp_st& b)
{
	mp_st res;

	if(_SAM_div_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_si_div (res.x, a, b.x, MPFR_RNDU);
	else mpfr_si_div (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_si_div (res.y, a, b.y, MPFR_RNDU);
		mpfr_si_div (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_si_div (res.y, a, b.y, MPFR_RNDD);
		mpfr_si_div (res.z, a, b.z, MPFR_RNDU);
	}
	
	return res;
}



///////////////////////////////////////////////////////////////////////////////////////////


mp_st operator/(const mpfr_t& a, const mp_st& b)
{
	mp_st res;
	if(_SAM_div_tag){
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div (res.x, a, b.x, MPFR_RNDU);
	else mpfr_div (res.x, a, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_div (res.y, a, b.y, MPFR_RNDU);
		mpfr_div (res.z, a, b.z, MPFR_RNDD);
	}
	else {
		mpfr_div (res.y, a, b.y, MPFR_RNDD);
		mpfr_div (res.z, a, b.z, MPFR_RNDU);
	}
	
	return res;
}


///////////////////////////////////////////////////////////////////////////////////////////

mp_st operator/(const mp_st& a, const double& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_div_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_div_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_div_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_div_d (res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}


mp_st operator/(const mp_st& a, const float& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_d (res.x, a.x, b, MPFR_RNDU);
	else mpfr_div_d (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_d (res.y, a.y, b, MPFR_RNDU);
		mpfr_div_d (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_div_d (res.y, a.y, b, MPFR_RNDD);
		mpfr_div_d (res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}


mp_st operator/(const mp_st& a, const unsigned long& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_div_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_div_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_div_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_div_ui (res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}



mp_st operator/(const mp_st& a, const long& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_div_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_div_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_div_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_div_si (res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}



mp_st operator/(const mp_st& a, const unsigned int& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_ui (res.x, a.x, b, MPFR_RNDU);
	else mpfr_div_ui (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_ui (res.y, a.y, b, MPFR_RNDU);
		mpfr_div_ui (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_div_ui (res.y, a.y, b, MPFR_RNDD);
		mpfr_div_ui (res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}



mp_st operator/(const mp_st& a, const int& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div_si (res.x, a.x, b, MPFR_RNDU);
	else mpfr_div_si (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_div_si (res.y, a.y, b, MPFR_RNDU);
		mpfr_div_si (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_div_si (res.y, a.y, b, MPFR_RNDD);
		mpfr_div_si (res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}





///////////////////////////////////////////////////////////////////////////////////////////


mp_st operator/(const mp_st& a, const mpfr_t& b)
{
	mp_st res;
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div (res.x, a.x, b, MPFR_RNDU);
	else mpfr_div (res.x, a.x, b, MPFR_RNDD);
	if (RANDOM){
		mpfr_div (res.y, a.y, b, MPFR_RNDU);
		mpfr_div (res.z, a.z, b, MPFR_RNDD);
	}
	else {
		mpfr_div (res.y, a.y, b, MPFR_RNDD);
		mpfr_div (res.z, a.z, b, MPFR_RNDU);
	}
	return res;
}

///////////////////////////////////////////////////////////////////////////////////////////

mp_st operator/(const mp_st& a, const mp_st& b)
{
	mp_st res;
	if(_SAM_div_tag) {
		if (b.accuracy==DIGIT_NOT_COMPUTED) b.nb_significant_digit();
		if (b.accuracy==0)
			instability(&_SAM_div_count);
	}
	res.accuracy=DIGIT_NOT_COMPUTED;
	
	if (RANDOM) mpfr_div (res.x, a.x, b.x, MPFR_RNDU);
	else mpfr_div (res.x, a.x, b.x, MPFR_RNDD);
	if (RANDOM){
		mpfr_div (res.y, a.y, b.y, MPFR_RNDU);
		mpfr_div (res.z, a.z, b.z, MPFR_RNDD);
	}
	else {
		mpfr_div (res.y, a.y, b.y, MPFR_RNDD);
		mpfr_div (res.z, a.z, b.z, MPFR_RNDU);
	}
	
	return res;
}















