#!/bin/bash
try() {
  expected="$1"
  input="$2"

  echo "test for ${1} ${2}"

  ./9cc "$input" > tmp.s
  file_size_kb=`du -k tmp.s | cut -f1`
  if [ "0" = ${file_size_kb} ]; then
    exit
  fi
  gcc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" != "$expected" ]; then
    echo "$input expected, but got $actual"
    exit 1
  fi
}

try 0 0
try 42 42
try 2 '1+1'
try 20 '10+10'
try 7 '1+2*3'
try 7 '2*3+1'
try 21 '5+20-4'
try 41 ' 12 + 34 - 5 '
try 2 '4 / 2'
try 6 '1 + 2 + 3'
try 26 '2 * 3 + 4 * 5'
try 47 "5+6*7"
try 1 "(1)"
try 15 "5*(9-6)"
try 4 "(3+5)/2"

