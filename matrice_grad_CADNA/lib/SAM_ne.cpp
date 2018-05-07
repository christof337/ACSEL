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
//****m* SAM_ne/operator!=
//    NAME
//      operator!=
//    SYNOPSIS
//      res = a != b 
//    FUNCTION
//      Define all the functions involving at least one argument
//      of stochastic type which overload the "!=" operator.
//      
//    INPUTS
//      a           - an integer, a float, a double, an mpfr_t object or a stochastic number
//      b           - an integer, a float, a double, an mpfr_t object or a stochastic number
//      At least one argument must be of stochastic type.
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
//      The return value takes into account the stochastic definition of
//      the "!=" operator (see the documentation). 
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

int operator!=(const double& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}



int operator!=(const float& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}


int operator!=(const unsigned long& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}



int operator!=(const long& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}



int operator!=(const unsigned int& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}



int operator!=(const int& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}



///////////////////////////////////////////////////////////////////////////////////////////



int operator!=(const mpfr_t& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}



///////////////////////////////////////////////////////////////////////////////////////////


int operator!=(const mp_st& a, const double& b)
{
	mp_st res;
	
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
	return !(res.computedzero());	
}



int operator!=(const mp_st& a, const float& b)
{
	mp_st res;

	
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
	return !(res.computedzero());	
}


int operator!=(const mp_st& a, const unsigned long& b)
{
	mp_st res;
	
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
	
	return !(res.computedzero());	
}



int operator!=(const mp_st& a, const long& b)
{
	mp_st res;
	
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
		
	return !(res.computedzero());	
}



int operator!=(const mp_st& a, const unsigned int& b)
{
	mp_st res;
	
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
	return !(res.computedzero());	
}



int operator!=(const mp_st& a, const int& b)
{
	mp_st res;
	
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
	return !(res.computedzero());	
}


///////////////////////////////////////////////////////////////////////////////////////////


int operator!=(const mp_st& a, const mpfr_t& b)
{
	mp_st res;
	
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
	return !(res.computedzero());	
}


///////////////////////////////////////////////////////////////////////////////////////////


int operator!=(const mp_st& a, const mp_st& b)
{
	mp_st res;
	
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
	return !(res.computedzero());
}















