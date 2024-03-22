#include <stdio.h>
#include <stdlib.h>

//define the three arrays
int buzzleBoard1[3][3];  //beginner array
int buzzleBoard2[4][4];	//intermediate array
int buzzleBoard3[5][5]; //advanced array

//location of a number in the array
struct location{
	int x;
	int y;
};


//print a welcome screen showing some information about the current game
void printWelcome(){
	printf("\t\t\t\t ============ Welcome to Sliding Puzzle	Game ===========\n");
	printf("\t\t\t\t you can play this game in three difficulty levels\n");
	printf("\t\t\t\t beginner,intermediate and advanced\n");
	printf("\t\t\t\t the winning condition is to arrange the numbers in ascending order\n");
	printf("\t\t\t\t use your keyboard numbers to type the next move\n");
	printf("================================================\n");
}

//print student information and their ids
void printTeamMembers(){
	printf("\t\t\t\t  _________________________\n");
	printf("\t\t\t\t |Student Name  | ID       |\n");
	printf("\t\t\t\t  -------------------------\n");
	printf("\t\t\t\t |Name1         | ID1      |\n");
	printf("\t\t\t\t |Name2         | ID2      |\n");
	printf("\t\t\t\t |Name3         | ID3      |\n");
	printf("\t\t\t\t |Name4         | ID4      |\n");
	printf("\t\t\t\t --------------------------\n");
}

//initializes  array to -1, before storing random numbers
//each level must be called with its size and level number, three levels only are allowed, however size can differ.
void initArray(int level,int size){
	//beginner level
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (level==1)
				buzzleBoard1[i][j] = -1;
			else
			if (level==2)
				buzzleBoard2[i][j] = -1;
			else
				buzzleBoard3[i][j] = -1;
		}
	}
}

//initialize the array to random distinct numbers
void constructGame(int level, int size){
	initArray(level,size); //set to -1

	//construct game
	for (int i = 0; i < size; i++){ //randomize each cell
		for (int j = 0; j < size; j++){
				while (1){
					int value = rand() % (size*size);
					int unique = 1; //0 means not, 1 means yes
					//now we add to current cell, if previous cells dont contain this number
					for (int subi = 0; subi <= i; subi++){
						for (int subj = 0; subj < size; subj++){
							//now we check which level we are dealing with
							if (level == 1){
								if (buzzleBoard1[subi][subj] == value){
									unique = 0;
									break;
								}
							}
							else
							if (level == 2){
								if (buzzleBoard2[subi][subj] == value){
									unique = 0;
									break;
								}
							}
							else
							if (buzzleBoard3[subi][subj] == value){
								unique = 0;
								break;
							}
						}
						if (!unique)
							break;
					}
					if (unique){ //so we can store this number
						if (level==1)
							buzzleBoard1[i][j] = value;
						else if (level==2)
							buzzleBoard2[i][j] = value;
						else
							buzzleBoard3[i][j] = value;
						break;
					}
				}
		}
	}
}

//view the array in formatted form
void printArray(int level,int size){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (level==1)
				printf("%3d ", buzzleBoard1[i][j]); //formatted printing 
			else
			if (level==2)
				printf("%3d ", buzzleBoard2[i][j]);
			else
				printf("%3d ", buzzleBoard3[i][j]);
		}
		printf("\n");
	}
}

//find the x and y indexes of a given number in the array
struct location findLocation(int number, int level, int size){
	struct location loc;
	loc.x = -1;
	loc.y = -1;
	for (int i = 0; i < size; i++){ //search the entire array
		for (int j = 0; j < size; j++){
			if (level == 1){
				if (buzzleBoard1[i][j] == number){
					loc.x = i;
					loc.y = j;
					return loc;
				}
			}
			if (level == 2){
				if (buzzleBoard2[i][j] == number){
					loc.x = i;
					loc.y = j;
					return loc;
				}
			}
			if (level == 3){
				if (buzzleBoard3[i][j] == number){
					loc.x = i;
					loc.y = j;
					return loc;
				}
			}
		}
	}
}

//check if the game is complete
int isComplete(int level,int size){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (level == 1){
				if (buzzleBoard1[i][j] != (1 + i*size + j)) //gives the 2d array index as 1d array index
					return 0;
			}
			if (level == 2){
				if (buzzleBoard2[i][j] != (1 + i*size + j)) //gives the 2d index as 1d index
					return 0;
			}
			if (level == 3){
				if (buzzleBoard3[i][j] != (1 + i*size + j)) //gives the 2d index as 1d index
					return 0;
			}
		}
	}
	return 1;
}

// play engine
void playLevel(int level,int size){
	constructGame(level, size);
	int moves = 0; //coutns correct move steps
	while (1){
		system("cls");  //clear screen
		printArray(level, size);
		fflush(stdin);
		int number = -1;
		scanf("%d", &number);
		//exit if number is -1
		if (number == -1)
			return;
		//check if number is next to current 0
		if ((number<1) || (number>=(size*size))){
			printf("Number is not acceptable\n");
			continue;
		}
		//find number location
		struct location loc = findLocation(number, level, size);
		struct location zero = findLocation(0, level, size); //find empty space index location
		//loc must be around zero index
		if ((((loc.x == zero.x - 1) || (loc.x == zero.x + 1)) && (loc.y == zero.y)) || (((loc.y == zero.y - 1) || (loc.y == zero.y + 1)) && (loc.x == zero.x))){
			//swap locations
			if (level == 1){
				buzzleBoard1[loc.x][loc.y] = 0;
				buzzleBoard1[zero.x][zero.y] = number;
			}
			if (level == 2){
				buzzleBoard2[loc.x][loc.y] = 0;
				buzzleBoard2[zero.x][zero.y] = number;
			}
			if (level == 3){
				buzzleBoard3[loc.x][loc.y] = 0;
				buzzleBoard3[zero.x][zero.y] = number;
			}
			moves++;
			system("cls"); //clear screen
			printArray(level, size);
			//check if game is over
			if (isComplete(level, size)){
				printf("Congratulations, you have completed the game in [ %d ] moves", moves);
				return;
			}
		}
	}
	//now play
}


//play menu
void play(){
	int choice = 0; //user choice
	while (1){ //loop tell exit
		printf("\nChoose a Level to play:\n");
		printf("1: Beginner Level\n");
		printf("2: Intermediate Level\n");
		printf("3: Advanced Level\n");
		printf("4: Back to main menu\n");
		fflush(stdin); //flush input buffer

		scanf("%d", &choice); //read user input
		switch (choice){
		case 1: //play beginner level
			playLevel(1,3);
			break;
		case 2: //play intermediate level
			playLevel(2, 4);
			break;
		case 3: //play advanced level
			playLevel(3, 5);
			break;
		case 4: //return to main menu
			return;
		default:
			printf("wrong input\n");
		}
	}
}

int main() {
	printWelcome();
	
	char choice = ' '; //user choice
	while (1){ //loop  exit is entered
		printf("\nInput one of the following options:\n");
		printf("A: Team Members\n");
		printf("B: Game Instructions\n");
		printf("C: Play Game\n");
		printf("D: Exit\n");
		fflush(stdin);  //flush input buffer

		scanf("%c", &choice); //read user input
		switch (choice){
		case 'a':
		case 'A': //exit
			printTeamMembers();
			break;
		case 'b':
		case 'B'://display infromation AND game instructions
			printWelcome();
			break;
		case 'c':
		case 'C'://play
			play();
			break;
		case 'd':
		case 'D'://display information
			return 0;
		default:
			printf("Wong input\n");
		}
	}
	return 0;
}