/* Solution to comp20005 Assignment 1, 2019 semester 1.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Tuan Khoi Nguyen - 1025294
   Dated:     5/5/2019

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X0 0 /*default centroid location*/
#define Y0 0

#define MAX_LINE 999 /*at most 999 data lines will occur in any input file*/

/*function prototypes*/
int throw_n(float x_val[], float y_val[], float kg_val[]);
float total_weight(float kg_val[], int count);
void print_stage_one(int count, float M, float x_val[], float y_val[],
	float kg_val[]);
float compute_distance(float x1, float y1, float x2, float y2);
float battery_cost(int i,float x_val[],float y_val[],float kg_val[]);
float battery_ret(int i,float x_val[],float y_val[],float kg_val[]);
void printer(int stage, int i, float x_val[], float y_val[], float kg_val[]);
void print_stage_two(int count, float x_val[], float y_val[], float kg_val[]);
void print_stage_three(int count, float x_val[], float y_val[], float kg_val[]);
float cent_x(float x_val[], int count);
float cent_y(float y_val[], int count);
float battgo_s4(int i, int count,float x_val[],float y_val[],float kg_val[]);
float battret_s4(int i, int count,float x_val[],float y_val[],float kg_val[]);
void printer_s4(int i, int count, float x_val[], float y_val[], float kg_val[]);
void print_stage_four(int count, float x_val[], float y_val[], float kg_val[]);

/* main program binds all together*/
int
main(int argc, char *argv[]) {
	/*storage for all input data*/
	float x_val[MAX_LINE], y_val[MAX_LINE], kg_val[MAX_LINE];
	int count;
	float M;
	count = throw_n(x_val, y_val, kg_val);
	M = total_weight(kg_val, count);
	print_stage_one(count, M, x_val,y_val, kg_val);
	printf("\n");
	print_stage_two(count, x_val, y_val, kg_val);
	printf("\n");
	print_stage_three(count, x_val, y_val, kg_val);
	printf("\n");
	print_stage_four(count,x_val,y_val,kg_val);
	printf("\nTa daa!");
	return 0;
}

/*speficic coding of the functions*/

/*throwing away the header line and counting the number of lines*/
int throw_n(float x_val[], float y_val[], float kg_val[]){
	int i, count;
	char throw_away;
	/*scanning and putting the header away*/
	/*header has 7 characters in total*/
	for (i=1;i<=7;i++){
		scanf("%c", &throw_away);
	}
	/*counting number of lines using while loop*/
	while(scanf("%f%f%f", &*(x_val+count), &*(y_val+count), &*(kg_val+count))==3
		&& count <= MAX_LINE){
		count++;
	}
	return count;
}

/*calculate total weight using loops*/
float total_weight(float kg_val[], int count){
	int i;
	float M=0.0;
	for (i=1;i<=count;i++){
		M+=kg_val[i-1];
	}
	return M;
}

/*printing the value lines*/
void print_stage_one(int count, float M, float x_val[], float y_val[],
	float kg_val[]){
	printf("S1, total data lines:%3d \n", count);
	printf("S1, first data line :  x=%6.1f, y=%6.1f, kg=%4.2f \n", 
		x_val[0], y_val[0], kg_val[0]); /*array starts at 0*/
	printf("S1, final data line :  x=%6.1f, y=%6.1f, kg=%4.2f \n", 
		x_val[count-1], y_val[count-1], kg_val[count-1]);
	printf("S1, total to deliver:%6.2f kg \n", M);
}

/*stage 2*/

/*calculate distance between (x1,y1) and (x2,y2)*/
float compute_distance(float x1, float y1, float x2, float y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

/*battery out calculation*/
float battery_cost(int i,float x_val[],float y_val[],float kg_val[]){
	return 100*compute_distance(x_val[i],y_val[i],X0,Y0)/(6300/(3.8+kg_val[i]));
}

/*battery return calculation*/
float battery_ret(int i,float x_val[],float y_val[],float kg_val[]){
	return 100*compute_distance(x_val[i],y_val[i],X0,Y0)/(6300/3.8);
}

/*this function makes printing values more compact, minimizes long rewriting*/
void printer(int stage, int i, float x_val[], float y_val[], float kg_val[]){
	printf("S%d, ",stage);
	printf("package=%3d, ",i);
	printf("distance=%6.1fm, ",compute_distance(x_val[i],y_val[i],X0,Y0));
	printf("battery out=%4.1f%%, ",battery_cost(i,x_val,y_val,kg_val));
	printf("battery ret=%4.1f%%\n",battery_ret(i,x_val,y_val,kg_val));
}

/*main part of stage 2*/
void print_stage_two(int count, float x_val[], float y_val[], float kg_val[]){
	int i;
	float sum=0.0; 	/*total battery capcity used*/
	int batt=1; 	/*number of batteries*/
	float s[count]; /*battery capacity used for each package*/
	float dis=0.0; 	/*total distance traveled, one way*/
	
	for(i=0; i<=count-1; i++){
		s[i]=battery_cost(i,x_val,y_val,kg_val)+battery_ret(i,x_val,y_val,kg_val);
		sum+=s[i]; 	/*adding up the battery*/
		/*check if battery is all good for the next package*/
		if (sum<=100.0) {
			
			if (s[i]>100||kg_val[i]>5.8){ 
				/*in case of fail data*/
				printf("Insufficient data\n");
				exit(EXIT_FAILURE);
			}
			else{
				printer(2,i,x_val,y_val,kg_val);
				/*adding to total distance*/
				dis+=compute_distance(x_val[i],y_val[i],X0,Y0);
			}
		}
		
		else{
	
			if (s[i]>100||kg_val[i]>5.8){
				printf("Insufficient data\n");
				exit(EXIT_FAILURE);
			}
			else{
				/*changing battery, adding 1 more to the total number*/
				printf("S2, change the battery\n");
				sum=s[i];	/*restart the capacity, including current package*/
				batt++;
				/*then operate as normal*/
				printer(2,i,x_val,y_val,kg_val);
				dis+=compute_distance(x_val[i],y_val[i],X0,Y0);
			}
		}
	}
	printf("S2, total batteries required:%4d\n",batt);
	/*returning distance is the same as delivering...*/
	printf("S2, total flight distance=%6.1f meters, ", dis*2);
	/*and so is that of speed, which is 4.2km/h*/
	printf("total flight time=%4.0f seconds\n", dis*2/4.2);
}

/*stage 3*/ 

void print_stage_three(int count, float x_val[], float y_val[], float kg_val[]){
	int i,j,k;
	int n;			/*number of packages left in storage*/
	int t[count]; 	/*check if package is in strorage for delivery*/
	float sum=0.0;	/*these values have the same use as in stage 2*/
	int batt=1;
	float s[count];
	float dis=0.0;
	
	/*don't have to worry about failure data if it passes stage 2*/
	
	/*all packages are in the storage initially*/
	for (k=0; k<=count-1; k++) {
		t[k]=1;
		s[k]=battery_cost(k,x_val,y_val,kg_val)+battery_ret(k,x_val,y_val,kg_val);
	}
	
	n=count; /*number of packages*/
	
	/*first order priority: package number*/
	for (i=0; i<=count-1; i++) { 
		/*check if package is in storage*/
		if (t[i]==1){
			/*second order priority: use less battery capacity*/
			for (j=i;j<=count-1; j++) {
				/*once again, check if package it's in storage*/
				if (t[j]==1) {
					/*carry out the commands, similar to stage 2*/
					if (sum+s[j]<=100) {
						printer(3,j,x_val,y_val,kg_val);
						t[j]=0; /*package is delivered*/
						n--;	/*1 package left the storage*/
						sum+=s[j];
						dis+=compute_distance(x_val[j],y_val[j],X0,Y0);
					}
				}
			}
				/*if all packages are delivered*/			
				if (n==0){
					printf("S3, total batteries required:%4d\n",batt);
					printf("S3, total flight distance=%6.1f meters, ", dis*2);
					printf("total flight time=%4.0f seconds\n", dis*2/4.2);
				}
				/*if not, change battery and repeat the process*/
				else{
				batt++;
				printf("S3, change the battery\n");
				sum=0.0;
				}
		}
	}
}
				

/*stage 4*/

/*getting centroid of x*/
float cent_x(float x_val[], int count){
	float sum=0.0;
	int i;
	for (i=0;i<count;i++){
		sum+=x_val[i];
	}
	/*average of the values*/
	return sum/count;
}

/*getting centroid of y, same way as getting that of x*/
float cent_y(float y_val[], int count){
	float sum=0.0;
	int i;
	for (i=0;i<count;i++){
		sum+=y_val[i];
	}
	return sum/count;
}

/*"battery_cost" and "battery_ret", with storage location changed for stage 4*/
float battgo_s4(int i, int count,float x_val[],float y_val[],float kg_val[]){
	return 100*compute_distance(x_val[i],y_val[i],
		cent_x(x_val, count),cent_y(y_val,count))/(6300/(3.8+kg_val[i]));
}

float battret_s4(int i, int count,float x_val[],float y_val[],float kg_val[]){
	return 100*compute_distance(x_val[i],y_val[i],
		cent_x(x_val, count),cent_y(y_val,count))/(6300/3.8);
}

/*therefore, "printer" have function names and values changed for stage 4*/
void printer_s4(int i, int count, float x_val[], float y_val[], float kg_val[]){
	printf("S4, ");
	printf("package=%3d, ",i);
	printf("distance=%6.1fm, ",
	compute_distance(x_val[i],y_val[i],cent_x(x_val, count),cent_y(y_val,count)));
	printf("battery out=%4.1f%%, ",battgo_s4(i,count,x_val,y_val,kg_val));
	printf("battery ret=%4.1f%%\n",battret_s4(i,count,x_val,y_val,kg_val));
}

/*stage 4 is the same as stage 3, with the storage location changed*/
void print_stage_four(int count, float x_val[], float y_val[], float kg_val[]){
	int i,j,k,n;
	int t[count]; /*these values have same use as in stage 3*/
	float sum=0.0;
	int batt=1;
	float s[count];
	float dis=0.0;
	
	/*printing out centroid location*/
	printf("S4, centroid location x=%6.1fm, ", cent_x(x_val, count));
	printf("y=%6.1fm\n", cent_y(y_val, count));
	
	/*the rest is the same as in stage 3*/
	for (k=0; k<=count-1; k++) {
		t[k]=1;
		s[k]=battgo_s4(k,count,x_val,y_val,kg_val)+
		battret_s4(k,count,x_val,y_val,kg_val);
	}
	
	n=count;
	
	for (i=0; i<=count-1; i++) { 
		if (t[i]==1){
			for (j=i;j<=count-1; j++) {
				if (t[j]==1) {
					if (sum+s[j]<=100) {
						printer_s4(j,count,x_val,y_val,kg_val);
						t[j]=0;
						n--;
						sum+=s[j];
						dis+=compute_distance(x_val[j],y_val[j],
							cent_x(x_val, count),cent_y(y_val,count));
					}
				}
			}
				if (n==0){
					printf("S4, total batteries required:%4d\n",batt);
					printf("S4, total flight distance=%6.1f meters, ", dis*2);
					printf("total flight time=%4.0f seconds\n", dis*2/4.2);
				}
				else{
				batt++;
				printf("S4, change the battery\n");
				sum=0.0;
				}
			
		}
	}
}
/*Programming is fun!*/