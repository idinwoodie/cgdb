#include <stdio.h>
#include <unistd.h>

int two(int a){
   return a*a;
}

int one(int a, int b){
   return two(a) + two(b);
}

void short_func(void){
   int i = 0;
   sleep(0);
   i = 1;
   i = 2;
}

void long_func(void){
   int k = 0;
   sleep(0);
   k = 1;
   k = 2;
}

#define SIZE 100000

struct test {
   int a;
   int b;
   int c;  
} a = { 1, 2, 3 };

int main(int argc, char **argv){
   int i = 3;
   int j = 4;
   char temp[SIZE];

   fprintf(stderr, "HAHAAHA\n");
   fprintf(stderr, "AHAAHA\n");
   fprintf(stderr, "HAAHA\n");
   fprintf(stderr, "AAHA\n");
   fprintf(stderr, "AHA\n");
   fprintf(stderr, "HA\n");
   fprintf(stderr, "A\n");

   long_func();

   short_func();
   short_func();
   short_func();

   for(i = 0; i < 100000; ++i)
      j++;

   i = one(i, j);
   j = two(i);

   for(i = 0; i < 6; ++i)
      fprintf(stderr, "returned from init\n");

   for(i = 0; i < SIZE; ++i)
      temp[i] = (i % 40) + 40;

   i += j;
   
   return 0;
}

