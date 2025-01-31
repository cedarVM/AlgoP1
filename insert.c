/*
 * Author: Matthew Louden
 *
 * Date: January 30th 2025
 *
 * Description: Performs a simple insertion sort pass on
 * sample sets of random integers (valued 0-4095) of sizes
 * powers of 10 up to 1 million.
 *
 * On my system a clock_t is (from bits/time.h):
 * #define CLOCKS_PER_SEC  ((__clock_t) 1000000)
 *
 * If I make reference to a clock cycle later it is
 * with this information in mind
 *
 * */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(int argc, char **argv) {

  srand(time(0));

  int *arr, *ins;
  clock_t init, end;

  int k;

  for (int i = 1; i < 10000; i+=5) {
  arr = malloc(i * 4);
  ins = malloc(i * 4);
    for (int j = 0; j < i; j++) {
    arr[j] = rand()&0b111111111111;
    }
  init = clock();

    ins[0] = arr[0];

    for (int j = 1; j < i; j++) {
      for (int k = j; k >= 0; k--) {
        if (arr[j] > ins[k - 1]) {
        ins[k] = arr[j];
        break;
        } else {
        ins[k] = ins[k - 1];
        }
      }
    }

  end = clock();
  printf("%d %d\n", end - init, i);


  }

}
