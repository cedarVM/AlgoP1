#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef PRE
#include "presort.h"
#endif

#ifdef INV
#include "invsort.h"
#endif

/*
 * Author: Matthew Louden
 *
 * Date: January 30th 2025
 *
 * Description: Performs quicksort on integers valued 0-4095
 * in batches of increments of 5 for 2000 iterations. The timing
 * mechanism for this algorithm is possibly unoptimally implemented.
 * A simple delta is taken from the start of the sort function till
 * its end. Overhead logic for getting samples is not considered,
 * however.
 *
 * In order for the in-place algorithm to work, the most convenient
 * pivot is chosen at the end of the sample. 
*/

int last(int size) {
return size - 1;
}

int middle(int size) {
return size / 2;
}

int first(int size) {
return 0;
}

void sort(int *arr, int *ins, int n) {

int pivot = arr[last(n)];

int first, last, temp;
int bottom_l, top_l;

first = 0;
last = n - 2;

  while (last > first) {
    if (arr[first] > pivot && arr[last] < pivot) {
    temp = arr[first];
    arr[first] = arr[last];
    arr[last]  = temp;
    last--;
    first++;
    }
    if (arr[last]  >= pivot) {
    last--;
    }
    if (arr[first] <= pivot) {
    first++;
    }

  }

  if (arr[last] < pivot) {
  last++;
  }

  bottom_l = last;
  top_l = n - last - 1;

  //printf("%d %d\n", bottom_l, top_l);
  //fgetc(stdin);


  ins[bottom_l] = pivot;

  if (bottom_l == 1) {
    ins[0] = arr[0];
  } else if (bottom_l == 0) {
    ;
  } else {
    sort(arr, ins, bottom_l); // bottom
  }

  if (top_l == 1) {
    ins[bottom_l + 1] = arr[bottom_l];
  } else if (top_l == 0) {
    ;
  } else {
    sort(arr + last, ins + last + 1, top_l); // top
  }

}

int main(int arg, char **argv) {

srand(time(0));

  int *sorted;

  clock_t init, end;

  #if !defined(PRE) && !defined(INV)
  for (int SIZE = 1; SIZE < 10000; SIZE+=5) {
  int *arr = malloc(SIZE * 4);
    for (int i = 0; i < SIZE; i++) {
    arr[i] = rand()&0b1111111111111;
    }
  #endif

  sorted = malloc(SIZE * 4);

    init = clock();
    sort(arr, sorted, SIZE);
    end = clock();

    printf("%d %d\n", end - init, SIZE);

  #if !defined(PRE) && !defined(INV)
  }
  #endif

}
