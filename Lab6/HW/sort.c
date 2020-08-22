#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listing.h"

typedef int MYFUNC(struct listing a1, struct listing a2);

void swap(struct listing li[], int currloc){
	struct listing temp;
	temp = li[currloc];
	li[currloc] = li[currloc-1];
	li[currloc-1] = temp;
}

void InsertSort(struct listing li[], int count, MYFUNC *f){
	int currLoc, i;
	//struct listing temp;
	for (i = 1; i < count; i++){
		currLoc = i;
		while (currLoc > 0 && f(li[currLoc], li[currLoc-1]) < 0 ){
			swap(li, currLoc);
			currLoc = currLoc -1;
		}
	}
}

int sortHost(struct listing a1, struct listing a2){
	return strcmp(a1.host_name, a2.host_name);
}

int sortPrice(struct listing a1, struct listing a2){
	return a1.price - a2.price;
}