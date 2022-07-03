#!/usr/bin/env bash

number_1=10
number_2=37
number_3=23
number_4=2

echo "NUMBER_1: $number_1"
echo "NUMBER_2: $number_2"
echo "NUMBER_3: $number_3"
echo -e "NUMBER_4: $number_4\n"

var_1=$(( 2 + 2 )) #4
var_2=$(( $number_1 * 10 )) #100
var_3=$(( $var_1 + $var_2 + $number_2 + $number_3 + 40 )) #204
var_4=$(( number_3 - number_1 - number_2 )) #-24
var_5=$(( number_4 ** number_1 )) #1024
var_6=$(( number_2 / number_4 )) #18

echo "VAR_1: $var_1"
echo "VAR_2: $var_2"
echo "VAR_3: $var_3"
echo "VAR_4: $var_4"
echo "VAR_5: $var_5"
echo "VAR_6: $var_6"

exit 0
