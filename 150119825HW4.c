// Merve Rana Kýzýl
// 150119825
// Homework 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <Math.h>
#define SIZE 10

typedef struct {

	char name[20];
	double x;
	double y;

} MetroStation;

typedef struct {

	char color[20];
	MetroStation MetroStations[SIZE];

} MetroLine;

typedef struct {

	char name[20];
	MetroLine MetroLines[SIZE];

} MetroSystem;

//Declare a MetroSystem with the name of istanbul and an empty content.
MetroSystem istanbul = { "istanbul", '\0' };


// Compare metro stations
int equals(MetroStation s1, MetroStation s2) {
	if (!strcmp(s1.name, s2.name))
		return 1;
	return 0;
}

// Add the given metro station MetroStations[] 
void addStation(MetroLine *l, MetroStation s) {

	for (int i = 0; i < SIZE; i++) {

		if (*(l->MetroStations + i)->name == '\0' ){
			*(l->MetroStations + i) = s;
			break;
		}
	}
}

// Check if the given MetroLine has the given MetroStation
int hasStation(MetroLine l, MetroStation s) {

	for (int i = 0; i < SIZE; i++) {

		if (equals(l.MetroStations[i], s))
			return 1;
		else
			return 0;
	}
}

// Find the first station of a MetroLine
MetroStation getFirstStop(MetroLine l) {
	MetroStation s = { '\0' };

	if (l.MetroStations[0].name[0] != '\0')
		return l.MetroStations[0];

	return s;
}


// Find the previous station
MetroStation getPreviousStop(MetroLine l, MetroStation s) {

	MetroStation station = { '\0' };

	for (int i = 0; i < SIZE; i++) {
		if (equals(l.MetroStations[i], s))
			return station;
		else if(equals(l.MetroStations[i], s))
			return l.MetroStations[i - 1];
	}

}

// Find the next station
MetroStation getNextStop(MetroLine l, MetroStation s) {

	MetroStation station = { '\0' };

	for (int i = 0; i < SIZE; i++) {

		if (equals(l.MetroStations[SIZE - 1], s))
			return station;
		else if(equals(l.MetroStations[i], s))
			return l.MetroStations[i + 1];
	}
}

// Add the given metro line to MetroLines[] 
void addLine(MetroSystem *s, MetroLine l) {
	for (int i = 0; i < SIZE; i++) {

		if (*(s->MetroLines + i)->color == '\0') {
			*(s->MetroLines + i) = l;
			break;
		}

	}
}

// Print the metro stations of the given metro line
void printLine(MetroLine l) {

	printf("MetroLine %s: ", l.color);

	for (int i = 0; i < SIZE; i++) {
		if (strlen(l.MetroStations[i].name) != 0)
			printf("%s, ", l.MetroStations[i].name);
	}

	printf("\n");
}

// Print the metro stations in the given array
void printPath(MetroStation s[]) {
	for (int i = 0; i < SIZE; i++) {

		if(s[i].name[0] != '\0')
			printf("%d.%s\n",i + 1, s[i].name);
	}
}

// Find the total distance travelled along a path
double getDistanceTravelled(MetroStation s[]) {
	double distance = 0;
	double sum = 0;

	for(int i = 0; i < SIZE - 1; i++){

		if(s[i].name[0] != '\0'){

			distance = sqrt(pow(s[i + 1].x - s[i].x, 2) + pow(s[i + 1].y - s[i].y, 2));
			sum = distance + sum;
		}

	}

	return sum;
}

// Find the nearest station
MetroStation findNearestStation(MetroSystem s, double x, double y) {

	double distance1 = 0;
	double distance2 = 0;
	double nearest = DBL_MAX;
	MetroStation firstStation;
	MetroStation nextStation;
	MetroStation nearestStation;

	for(int i = 0; i < SIZE; i++){

		for(int j = 0; j < SIZE; j++){

			if(s.MetroLines[i].color[0] != '\0' && s.MetroLines[i].MetroStations[j].name[0] != '\0') {
				
				nextStation = getNextStop(s.MetroLines[i], s.MetroLines[i].MetroStations[j]);
				distance1 = sqrt(pow((nextStation.x - x), 2) + pow((nextStation.y - y), 2));
				firstStation = getFirstStop(s.MetroLines[i]);
				distance2 = sqrt(pow((firstStation.x - x), 2) + pow((firstStation.y - y), 2));
			
				if (distance1 < nearest){
					
					nearest = distance1;
					nearestStation = nextStation;
				}

				if (distance2 < nearest){

					nearest = distance2;
					nearestStation = firstStation;
				}

			}

		}

	}

	return nearestStation;

}

// Find the neighboring stations using the given station
void getNeighboringStations(MetroSystem system, MetroStation station,  MetroStation neighboringStations[]) {

	MetroStation previousNeighbor;
	MetroStation nextNeighbor;
	MetroLine line;
	int k = 0;
	MetroStation s;

	for(int i = 0; i < SIZE; i++){


		for(int j = 0; j < SIZE; j++){

			s = system.MetroLines[i].MetroStations[j];

			if(equals(s, station)){

				previousNeighbor = system.MetroLines[i].MetroStations[j -1];
				nextNeighbor = system.MetroLines[i].MetroStations[j  + 1];

					if(k < SIZE){

						if(previousNeighbor.name[0] != '\0'){
							neighboringStations[k] = previousNeighbor;
							k++;
						}
						if(nextNeighbor.name[0] != '\0'){
							neighboringStations[k] = nextNeighbor;
							k++;
						}

					}

			}
		}
	}

 }

// Check if the given path has the given station
 int contains(MetroStation duplicatePath[], MetroStation s){
	for(int i = 0; i < SIZE; i++){

		if(duplicatePath[i].name[0] != '\0') {

			if(equals(duplicatePath[i], s)){

				return 0;
			}
		}
	}
	return 1;
 }

 void copyArray(MetroStation copy[], MetroStation original[]){

	for(int i = 0; i < SIZE; i++)

		copy[i] = original[i];
 }
 
 void recursiveFindPath(MetroStation start, MetroStation finish,  MetroStation partialPath[], MetroStation bestPath[]);
 
 MetroStation path2[SIZE];
 void findPath(MetroStation start, MetroStation finish, MetroStation path[]){
	
	MetroStation partialPath [SIZE];
	recursiveFindPath(start, finish, path, partialPath);
	copyArray(path, path2);
	
 }
 
 void information(MetroStation start, MetroStation finish){
 	
 	MetroStation current = findNearestStation(istanbul, start.x, start.y);
	MetroStation target = findNearestStation(istanbul, finish.x, finish.y);
	
	printf("\nThe nearest metro station to the current location is %s (since myX = %.2f and myY = %.2f).\n", current.name, start.x, start.y);
	printf("\nThe nearest metro station to the target location is %s (since goalX = %.2f and goalY = %.2f).\n", target.name, finish.x, finish.y);
		
	MetroLine line;
	int flag = 0;
	for(int i = 0; i < SIZE; i++) {
		
		line = istanbul.MetroLines[i];
		if(!(hasStation(line, start) && hasStation(line, finish))){
			flag = 1;
		}	
	}
	
	if(flag){
			
		printf("\nBoth %s and %s stations are not located in a single metro line. The best path(with minimum distance traveled) is given as:\n", current.name, target.name);					
	}
	
	printPath(path2);	
 }
 
// Find a path from one MetroStation to another MetroStation
  void recursiveFindPath(MetroStation start, MetroStation finish,  MetroStation partialPath[], MetroStation bestPath[]) {

	static double distance = 0;
	static double smallest = DBL_MAX;

	for(int i = 0; i < SIZE; i++) {

		if(equals(partialPath[i], start)){
			return;
		}
	}

	if(equals(start, finish)) {

		for(int i = 0; i < SIZE; i++){

			if(partialPath[i].name[0] == '\0') {
				partialPath[i] = finish;
				break;
			}
		}

	distance = getDistanceTravelled(partialPath);

	if(distance < smallest){

		smallest = distance;
		copyArray(bestPath, partialPath);
	}
	copyArray(path2, bestPath);
	return;
}

	MetroStation neighbors[SIZE] = {0};
	getNeighboringStations(istanbul, start, neighbors);
	MetroStation duplicatePath[SIZE];
	copyArray(duplicatePath, partialPath);
	

	int i = 0;

	while(1) {

		if(duplicatePath[i].name[0] == '\0'){

			duplicatePath[i] = start;
			break;
		}

		i++;
	}

	for(int i = 0; i < SIZE; i++){

		if(neighbors[i].name[0] != '\0' && contains(duplicatePath, neighbors[i])){

			recursiveFindPath(neighbors[i], finish, duplicatePath, bestPath);

		}
	}
	
}


int main()
{
	int i;
	double myX=1, myY=2;
	double goalX=62, goalY=45;

	// define 3 metro lines, 9 metro stations, and an empty myPath
	MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
	MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
	MetroStation myPath[SIZE]={'\0'};

	strcpy(red.color, "red");
	strcpy(blue.color, "blue");
	strcpy(green.color, "green");


	strcpy(s1.name, "Haydarpasa"); 		s1.x=0; 	s1.y=0;
	strcpy(s2.name, "Sogutlucesme"); 	s2.x=10; 	s2.y=5;
	strcpy(s3.name, "Goztepe"); 		s3.x=20; 	s3.y=10;
	strcpy(s4.name, "Kozyatagi"); 		s4.x=30; 	s4.y=35;
	strcpy(s5.name, "Bostanci"); 		s5.x=45; 	s5.y=20;
	strcpy(s6.name, "Kartal"); 			s6.x=55; 	s6.y=20;
	strcpy(s7.name, "Samandira"); 		s7.x=60; 	s7.y=40;
	strcpy(s8.name, "Icmeler"); 		s8.x=70; 	s8.y=15;

	//Add several metro stations to the given metro lines.
	addStation(&red, s1); addStation(&red, s2); addStation(&red, s3); addStation(&red, s4); addStation(&red, s5); addStation(&red, s8);

	addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);

	addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);

	// Add red, blue, green metro lines to the Istanbul metro system.
	addLine(&istanbul, red);
	addLine(&istanbul, blue);
	addLine(&istanbul, green);

	// print the content of the red, blue, green metro lines
	printLine(red);
	printLine(blue);
	printLine(green);


	// find the nearest stations to the current and target locations
	MetroStation nearMe = findNearestStation(istanbul, myX, myY);
	MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);

	printf("\n");

	printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);

	// if the nearest current and target stations are the same, then print a message and exit.
	if(equals(nearMe, nearGoal)){
		printf("It is better to walk!\n");
		return 0;
	}

	// Calculate and print the myPath with the minimum distance travelled from start to target stations.
	findPath(nearMe, nearGoal, myPath);

	if(strlen(myPath[0].name) == 0)
		printf("There is no path on the metro!\n");
	else{
		printPath(myPath);
		information(nearMe, nearGoal);
	}

	return 0;

}
