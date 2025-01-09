/*

printf format specifiers:
%[flags][width][.percision][length]specifier

specifier:
d or i signed int
u unsigned int
o unsigned octal
x or X Unsigned Hexadecimal (lower/ upper case)
e or E Floating point
g or G shortest Representation
a or A Hexadecimal Floating Point (lower/upper case)
c character
s string of charaters
p pointer address

width:
(number) Minimum number of characters to pring
.        Not spcified in cstring, additional INT value given

flag:
-   Left-justify(default: right)
+   Force print + sign with positives
(space) Add space, if not sign before value
#   Precede o, x, or X with 0
0   left pad number with zeros

.percision:
.number     specifies number of digits to write
.*          not specified in cstring, additional INT value given


    printf("This is how to split lines in c. "
           "This is another line\n");


*/