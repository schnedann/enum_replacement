enum_replacement

enum classes in C++ are their own type, so you can't use e.g. logical operators on enum values. This prevents usage as bitwise options, which is a efficient way to pass several options to a function at once. A trick often used in embedded programming. OK, you can of course do this, with several casts included... which results in working but ugly code.

Also One might want to check inputs to an function: is a supplied value a valid value defined by the enum? You can trick this with a range check, as long the enum has consecutive values. 

So what is the Advice of the Internet? there are some interesting discussions, but none is providing an sufficient solution:  
https://stackoverflow.com/questions/4969233/how-to-check-if-enum-value-is-valid

so here Member PTrenholme suggested to use a struct instead of an enum:  
https://www.linuxquestions.org/questions/programming-9/check-if-an-int-value-is-within-valid-range-of-enum-417500/

$ cat test5.c  
#include <stdio.h>  
static struct myEnum {  
  int A;  
  int B;  
  int C;  
  int D;  
  int E;  
  int F;  
} Val = {0, 2, 10, 12, 25, 30};  

int main(int argc, char ** argv)  
{  
  int test;  
  printf("sizeof(Val)=%d\nsizeof(Val.A)=%d\n", sizeof(Val), sizeof(Val.A));  
  for (test = 0; test < sizeof(Val)/sizeof(Val.A); ++test) {  
    printf("test %d Val = %d\n",test, *(&Val.A+test));  
  }  
}  
$ ./test5  
sizeof(Val)=24  
sizeof(Val.A)=4  
test 0 Val = 0  
test 1 Val = 2  
test 2 Val = 10  
test 3 Val = 12  
test 4 Val = 25  
test 5 Val = 30  

And this post leads the right way!:  

The solution to both problems: use a const struct variable as an enum: now every enum-value has the normal integer Type (if you are using integers) and all operations on Integers work as expected.

Using const Values causes the compiler to directly inline values in code - even with no optimization switched on (at least this was the case with the testcode provided here)... so the solution is at least as efficient in the machine code as the normal enum classes.

Using normal integer Types for the "enum values" also causes the compiler to treat the struct like an array with all values directly placed one to another. Also we can easly retrieve the pointers to the "enum values". This allows for iterating over all "enum values". Searching inside all "enum values" if a given value matches one of them now is pretty easy.

Let's summarize:
* use structs, not enums
* syntax is compareable, just a small fraction more worse
* compiler warns if more values than defined are supplied
* Only source of error is when less than defined values are supplied
* prevents ugly casts
* utilizing normal Integers as base type you can do all normal operations for integers
* is_value_in_enum() is now easy to implement
