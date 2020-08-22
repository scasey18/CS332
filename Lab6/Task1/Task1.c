#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 1024
// Exercise Step 1
struct listing { 
	int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;
	char *host_name, *neighbourhood_group, *neighbourhood, *room_type; 
	float latitude, longitude, price; 
}; 
//Exercise Step 2
struct listing getfields(char* line){ 
	struct listing item; 

	item.id = atoi(strtok(line, ",")); 
	item.host_id = atoi(strtok(NULL, ",")); 
	item.host_name = strdup(strtok(NULL, ",")); 
	item.neighbourhood_group = strdup(strtok(NULL, ",")); 
	item.neighbourhood = strdup(strtok(NULL, ",")); 
	item.latitude = atof(strtok(NULL, ",")); 
	item.longitude = atof(strtok(NULL, ",")); 
	item.room_type = strdup(strtok(NULL, ",")); 
	item.price = atof(strtok(NULL, ",")); 
	item.minimum_nights = atoi(strtok(NULL, ",")); 
	item.number_of_reviews = atoi(strtok(NULL, ",")); 
	item.calculated_host_listings_count = atoi(strtok(NULL, ",")); 
	item.availability_365 = atoi(strtok(NULL, ",")); 

	return item; 
} 

void displayStruct(struct listing item) {
	printf("ID : %d\n", item.id);
	printf("Host ID : %d\n", item.host_id);
	printf("Host Name : %s\n", item.host_name);
	printf("Neighbourhood Group : %s\n", item.neighbourhood_group);
	printf("Neighbourhood : %s\n", item.neighbourhood);
	printf("Latitude : %f\n", item.latitude);
	printf("Longitude : %f\n", item.longitude);
	printf("Room Type : %s\n", item.room_type);
	printf("Price : %f\n", item.price);
	printf("Minimum Nights : %d\n", item.minimum_nights);
	printf("Number of Reviews : %d\n", item.number_of_reviews);
	printf("Calculated Host Listings Count : %d\n", item.calculated_host_listings_count);
	printf("Availability_365 : %d\n\n", item.availability_365);
}

int main(int argc, char* args[]){
	struct listing list_items[22555];
	char line[LINESIZE];
	int i, count;
	//Exercise Step 3
	FILE *fptr = fopen("listings.csv", "r");
	//Exercise Step 4
	count = 0;
	while (fgets(line, LINESIZE, fptr) != NULL){
		list_items[count++] = getfields(line);
	}
	//Exercise Step 5
	for (i=0; i<count; i++){
		displayStruct(list_items[i]);
	}
	
	fclose(fptr);
	
}