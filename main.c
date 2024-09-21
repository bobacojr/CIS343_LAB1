#include <stdio.h>

#include <limits.h>

#include <stdint.h>

#include "lite_vector.h"



int main(int argc, char** argv){

	printf("Size max is %lu.\n", SIZE_MAX);

	lite_vector * lv = lv_new_vec(sizeof(int*));

	int x[32767];

	for(int i=0; i<32767; ++i) {

		x[i] = i;

		size_t first = lv->max_capacity;

		lv_append(lv, &(x[i]));

		size_t second = lv->max_capacity;

		if(first != second){

			printf("Max: %lu.  Current: %lu.\n", lv->max_capacity, lv->length);

		}

	};



	for(int i=0; i<32767; ++i){

		int * p = lv_get(lv, i);

		int val = *p;

	}



	lite_vector * lv2 = lv_new_vec(sizeof(char*));

	lv_append(lv2, "Dr. ");

	lv_append(lv2, "L. ");

	lv_append(lv2, "says ");

	lv_append(lv2, "hi!");

	for(size_t i=0; i<lv2->length; ++i){

		printf("%s\n", (char*)lv_get(lv2, i));

	}

}

