#ifndef _SORT_H_  
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listing.h"
typedef int MYFUNC(struct listing a1, struct listing a2);
void InsertSort(struct listing li[], int count, MYFUNC *f);
void swap(struct listing li[], int currloc);
int sortHost(struct listing a1, struct listing a2);
int sortPrice(struct listing a1, struct listing a2);
#endif 