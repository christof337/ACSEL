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

#ifndef __SAM_PRIVATE__
#define __SAM_PRIVATE__

extern int _SAM_max_instability, _SAM_instability_detected;

// global variables 

// INSTABILITIES MANAGEMENT

extern unsigned long _SAM_div_count;
extern unsigned long _SAM_mul_count;  
extern unsigned long _SAM_power_count;  
extern unsigned long _SAM_math_count; 
extern unsigned long _SAM_intrinsic_count;  
extern unsigned long _SAM_cancel_count;  
extern unsigned long _SAM_branching_count; 

extern unsigned int _SAM_div_tag; 
extern unsigned int _SAM_mul_tag;  
extern unsigned int _SAM_power_tag;  
extern unsigned int _SAM_math_tag; 
extern unsigned int _SAM_intrinsic_tag; 
extern unsigned int _SAM_cancel_tag; 
extern unsigned int _SAM_branching_tag;

extern unsigned int _SAM_div_change; 
extern unsigned int _SAM_mul_change;  
extern unsigned int _SAM_power_change;  
extern unsigned int _SAM_math_change; 
extern unsigned int _SAM_intrinsic_change; 
extern unsigned int _SAM_cancel_change; 
extern unsigned int _SAM_branching_change;

extern int _SAM_cancel_value;
void  instability(unsigned long*);


// The RANDOM BIT GENERATOR
extern unsigned short  _SAM_random_table[];
extern unsigned int _SAM_table_counter;

void _SAM_init_table(unsigned int);

#define RANDOM_BIT_NUMBER 0x0000000F
#define RANDOM_ELEMENT_NUMBER 0x003FFFF0
#define RANDOM_ELEMENT_SHIFT 4

#define RANDOM (_SAM_random_table[(_SAM_table_counter&RANDOM_ELEMENT_NUMBER)>>RANDOM_ELEMENT_SHIFT] & (1<<((_SAM_table_counter++)&RANDOM_BIT_NUMBER)))


#define DIGIT_NOT_COMPUTED -1


#endif
