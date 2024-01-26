#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 7
#define MONTH 10
#define TIMES 13

typedef struct {
	//Data members/ attributes
	int day, times[TIMES], month; 
} Date;

int getDaysInMonth(int month, int year) {
	int days_in_month;
	
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
  		return days_in_month = 31;
  	} else if(month == 4 || month == 6 || month == 9 || month == 11) {
  		return days_in_month = 30;
  	} else if(month == 2 && year % 4 == 0){
  		return days_in_month = 29;
  	} else if (month == 2 && year % 4 != 0){
  		return days_in_month = 28;  	
  	}
}

Date** getDates() {
	int year, monthNum, dayNum, days_in_month, size;
	Date date;
	int time_values[TIMES] = {1000, 1030, 1100, 1130, 1200, 1230, 1300, 1330, 1400, 1430, 1500, 1530, 1600};
	//Allocate the memory for the array of pointers to Date structs
	Date** dates = (Date**)malloc(ROW * sizeof(Date*));
    	
    	if (dates == NULL) {
    		printf("Memory allocation failed!\n");
    		return NULL;
    	}
    	
	time_t t = time(NULL);
  	struct tm *current_time = localtime(&t);
  	char weekday_buffer[MONTH], day_buffer[3], month_buffer[MONTH];
  	
  	// Get the number of days in the month
  	year = current_time->tm_year + 1900;
  	monthNum = current_time->tm_mon + 2;
  	days_in_month = getDaysInMonth(monthNum, year);

  	// Print the month of the first day
  	t += 86400; // Add 24 hours in seconds (86400 seconds)
  	current_time = localtime(&t);
	strftime(month_buffer, sizeof(month_buffer), "%B", current_time);
	printf("		      %s-", month_buffer);  	
	
	// Print the month of the last day
	t += 86400 * 30;
  	current_time = localtime(&t);
	strftime(month_buffer, sizeof(month_buffer), "%B", current_time);
	printf("%s\n", month_buffer);

	//Equate the time to point back to the next day
	t -= 86400 * 31;
  	current_time = localtime(&t);
  	
  	for (int i = 0; i < 7; i++) {
 		// Print the next day
  		t += 86400;
  		current_time = localtime(&t);
  		strftime(weekday_buffer, sizeof(weekday_buffer), "%A", current_time);
		printf("%s ", weekday_buffer);
  	}
  	printf("\n");
  	t -= 86400 * 7; 
  	current_time = localtime(&t);
  	dayNum = current_time->tm_mday;
  	size = 0;
  	
  	for (int i = 0; i < ROW; i++) {
  		dates[i] = (Date*)malloc(COL * sizeof(Date));
  		if (dates[i] == NULL) {
  			printf("Memory allocation failed!\n");
  			return NULL;
  		}
  		
  		//Initialize each date in the row
		for (int j = 0; j < COL; j++) {
			if (size < 31) {
				dayNum++;
				if (dayNum >= days_in_month) {
  					dayNum = 1;
  					if (monthNum == 12) {
  						monthNum = 1;
  						year++;
  					}
  					days_in_month = getDaysInMonth(monthNum, year);	
  				}
  				
				t += 86400;
				current_time = localtime(&t);
				strftime(month_buffer, sizeof(month_buffer), "%B", current_time);
  				dates[i][j].day = dayNum;
				dates[i][j].month = monthNum;
				for (int l = 0; l < 13; l++) {
					dates[i][j].times[l] = time_values[l];
				}
  				strftime(day_buffer, sizeof(day_buffer), "%d", current_time);
  				printf("%s	", day_buffer);
  				size++;
  			} else {
  				break;
  			}
		}	
		printf("\n");
  	}
  	return dates;
}

int** getTimeSlots(int day, int month, Date** dates) {
	int dayNum, listPosition = 0, dayParam, monthParam;
	int** times_list = (int**)malloc(TIMES * sizeof(int*));
	bool found = false;
	Date date;
	
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (listPosition < 31 || !found) {
				dayParam = dates[i][j].day;
				monthParam = dates[i][j].month;
				if (day == dayParam && month == monthParam) {
					found = true;
					printf("			%d/%d\n", dayParam, dates[i][j].month);
					
					for (int k = 0; k < TIMES; k++) {
						times_list[k] = (int*)malloc(sizeof(int));
						*times_list[k] = dates[i][j].times[k];
						printf("%d |", *(times_list[k]));
					}		
				} else {
				listPosition++;
				}
			} else {
				break;
			}
		}
	}
	
	if (!found) {
        	printf("No time slots available for the specified day and month.\n");
        	exit(0);
    	} else {
    		printf("\nPick a time slot: ");
    		return times_list;
    	}
    	
}

void makeTicket(int day, int month, int** timeSlots, int time) {
	bool found = false;
	for (int k = 0; k < TIMES; k++) {
		if (time == *timeSlots[k]) {
			found = true;
			break;
		}
	}
	
	if (found) {
		FILE* fpointer = fopen("ticket.txt", "a");
	fprintf(fpointer, "| ---------WATER PARK TICKET--------- |\nMonth: %d\nDay: %d\nTime: %d\nEndeavour to bring this ticket with you or you will be denied entry.\n\n", month, day, time);
	
	fclose(fpointer);
	printf("Congrats. The ticket has been printed.\n");
	} else {
		printf("The selected time slot is not available.\n");
	}
}

int main(int argc, char **argv) 
{
	int day, time, month;
	int** timeSlots;
	Date** dates;
	printf("| ------------------------- WATER PARK TICKET SYSTEM ------------------------- |\n\n");
	dates = getDates();
	printf("\nPick a day from the following (Format: DD): ");
	scanf("%d", &day);
	
	printf("Pick a day from the following (Format: MM): ");
	scanf("%d", &month);
	
	timeSlots = getTimeSlots(day, month, dates);
	
	scanf("%d", &time);
	makeTicket(day, month, timeSlots, time);
	
	return 0;
}
