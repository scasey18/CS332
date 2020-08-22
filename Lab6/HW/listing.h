#ifndef _LISTING_H_  
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// Exercise Step 1
struct listing { 
	int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count, availability_365;
	char *host_name, *neighbourhood_group, *neighbourhood, *room_type; 
	float latitude, longitude, price; 
};
struct listing getfields(char* line);
void displayStruct(struct listing item);
#endif 