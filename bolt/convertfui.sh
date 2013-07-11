#!/bin/bash
#
#{GRl, 1, "", 0x00130040, 0x40000006, 0},

# fucking gawk. 
awk -F : -F ' '  \
	'/outl/{print "{GWl, 1, \"\",  ", $1, ", 0x", $3, ", 0},"} \
	/inl/{print "{GRl, 1, \"\",  ", $1, ", 0x", $3, ", 0},"}' \
	  | tr '\r' ' ' | sed s/:// |sed 's/0x /0x/'
