#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sort.h"
#define LINESIZE 1024

typedef void writeFunc(struct listing line, FILE *fp);

void writeHostListing(struct listing line, FILE *fp){
	fprintf(fp,"%s,%d,%d,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",
	line.host_name, 
	line.id,
	line.host_id, 
	line.neighbourhood_group, 
	line.neighbourhood,
	line.latitude,
	line.longitude,
	line.room_type,
	line.price,
	line.minimum_nights,
	line.number_of_reviews,
	line.calculated_host_listings_count,
	line.availability_365);
}

void writePriceListing(struct listing line, FILE *fp){
	fprintf(fp,"%f,%d,%d,%s,%s,%s,%f,%f,%s,%d,%d,%d,%d\n",
	line.price, 
	line.id,
	line.host_id, 
	line.host_name, 
	line.neighbourhood_group, 
	line.neighbourhood,
	line.latitude,
	line.longitude,
	line.room_type,
	line.minimum_nights,
	line.number_of_reviews,
	line.calculated_host_listings_count,
	line.availability_365);
}

void writeArray(struct listing list_items[], int count, FILE *fp, writeFunc f){
	int i;
	for (i=0; i<count; i++){
		f(list_items[i], fp);
	}
}

int main(int argc, char* args[]){
	struct listing list_items[22555];
	char line[LINESIZE];
	int count;
	//Exercise Step 3
	FILE *fptr = fopen("listings.csv", "r");
	//Exercise Step 4
	count = 0;
	while (fgets(line, LINESIZE, fptr) != NULL){
		list_items[count++] = getfields(line);
	}
	//Exercise Step 5
	fclose(fptr);
	//HW exclusive work
	char* hname = "HostSortedListings.csv";
	FILE *fhptr = fopen(hname, "w+");
	printf("Created/Wiped the %s file\n",hname);
	printf("Sorting the Array by host_name\n");
	InsertSort(list_items, count, sortHost);
	printf("Finished Sorting\n");
	writeArray(list_items, count, fhptr, writeHostListing);
	printf("Writing sort result to %s\n",hname);
	fclose(fhptr);
	
	char* pname = "PriceSortedListings.csv";
	FILE *fpptr = fopen(pname, "w+");
	printf("Created/Wiped the %s file\n",pname);
	printf("Sorting the Array by host_name\n");
	InsertSort(list_items, count, sortPrice);
	printf("Writing sort result to %s\n",pname);
	writeArray(list_items, count, fpptr, writePriceListing);
	fclose(fpptr);
}