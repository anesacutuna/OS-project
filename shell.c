#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <libgen.h>
#include <signal.h>
#include <sys/wait.h>

int loop = 1;
int main(void) {

    system("clear");

    char input[1024];

    while (loop) {

        prompt(); //implement custom promt

        fgets(input, 1024, stdin); // get input

        router(input); //set router to given input
    }

    return 0;
}

void prompt() {

    char * username; // init username
    char hostname[HOST_NAME_MAX + 1]; //init machine name

    username = getlogin(); // populate username

    gethostname(hostname, HOST_NAME_MAX + 1); // populate machine name

    char cwd[PATH_MAX];

    purple_color();
    printf("%s", hostname);  // set color and text for hostname

    yellow_color();
    printf("@");  // set color and text for @ sign

    red_color();
    printf("%s", username); // set color and text for machine name

    reset();

    printf(":~$ "); // add :~$ from assigment

}

void router(char input[1024]) {

    char function [10] = ""; // function list
    int fun_counter = 0; // counter how many functions there are


    // get function from given input string that would operate shell
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ' || (int) input[i] == 0) {
            function [fun_counter] = input[i];
            fun_counter++;
        } else {
            break;
        }
    }


    function [strcspn(function, "\n")] = 0;

    if (strcmp(function, "wc") == 0) { //check if shell command is copy
        execlp("wc","wc",NULL);
    } else if (strcmp(function, "grep") == 0) { //check if shell command is history
        grep();
    } else if (strcmp(function, "matrix") == 0) { //check if shell command is free
        matrix();
    } else if (strcmp(function, "fortune") == 0) { //check if shell command is fortune
        fortune();
    } else if(strcmp(function, "art") == 0){ //check if shell command is custom art
        for (int i = 0; i < 50; i++){
            system("sleep 0.01");
            system("clear");
            drawArt(i); // the art moves 50 spaces
        }
        system("clear");
    }else if ((int)function [0] != 0) { //check if shell command is invalid and display message
        printf("%s: command not found\n", function);
    }

}


#define MAX_LINE 80
#define BUFFER_SIZE 50
#define buffer
char history[10][BUFFER_SIZE];
int count = 0;


void purple_color() {
    printf("\033[0;35m"); // Set bash color purple
}

void yellow_color() {
    printf("\033[0;33m"); // Set bash color yellow
}

void red_color() {
    printf("\033[0;31m"); // Set bash color red
}

void reset() {
    printf("\033[0m"); // Reset bash color
}

void grep() {
  char fn[10],pat[10],temp[200];
FILE *fp;
printf("Enter file name\n");
scanf("%s",fn);
printf("Enter pattern to be searched\n");
scanf("%s",pat);
fp=fopen(fn,"r");
while(!feof(fp))
{
fgets(temp,1000,fp);
if(strstr(temp,pat))
  printf("%s",temp);
}
fclose(fp);
}

void command_free() {
    int * ptr; // init list
    int n, i;

    n = 5;
    printf("elements size %d\n", n);
    ptr = (int * ) malloc(n * sizeof(int)); // allocate memory to list

    printf("memory is allocated\n");

    free(ptr); //free list memory
    printf("memory is free now\n");
}

int random_int(int Size) { //function retreive random number for given size
    int k;
    k = 0;
    srand((unsigned) time(NULL));
    k = rand() % Size;
    return k;
}


const char* fortunes_list[] = {
        "freebsd-tips", "osfortune", "zippy",
        "startrek", "debian-hints",
        "limerick", "fortunes2", "linuxcookie" // fortunes commands so you could pack eny of these
};
const size_t fortunes_size = sizeof(fortunes_list)/sizeof(*fortunes_list) - 1;
void fortune() {
    execlp("/usr/games/fortune", fortunes_list[random_int(fortunes_size)], "-l", NULL, NULL);
}

void print(char *line, int number){
    for(int i = 0; i < number; i++){
        printf(" "); // add spaces to simulate moving
    }
    printf("%s\n", line); // when spaces added add car line content
}

void drawArt(int spaces){
    purple_color();

    char *line1 = "|\   \\\\__     o";
    char *line2 = "| \_/    o \    o";
    char *line3 = "> _   (( <_  oo";
    char *line4 = "| / \__+___/";
    char *line5 = "|/     |/";

    print(line1, spaces);
    print(line2, spaces);
    print(line3, spaces);
    print(line4, spaces);
    print(line5, spaces);
    reset();
}

void forkbomb(){
    red_color();

    /**
     * The forkbomb command is simple in nature, all we need is a infinite loop and the fork command
     * forkbomb weren't implemented so you can thank me later for not breaking your PC ;)
     */

    while(1){
        fork();
    }

}

void matrix(){
  int firstMatrix[10][10], secondMatrix[10][10], mult[10][10], rowFirst, columnFirst, rowSecond, columnSecond, i, j, k;

	printf("Enter rows and column for first matrix: ");
	scanf("%d %d", &rowFirst, &columnFirst);

	printf("Enter rows and column for second matrix: ");
	scanf("%d %d", &rowSecond, &columnSecond);

	// If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again.
	while (columnFirst != rowSecond)
	{
		printf("Error! column of first matrix not equal to row of second.\n");
		printf("Enter rows and column for first matrix: ");
		scanf("%d%d", &rowFirst, &columnFirst);
		printf("Enter rows and column for second matrix: ");
		scanf("%d%d", &rowSecond, &columnSecond);
	}

	// Function to take matrices data
        enterData(firstMatrix, secondMatrix, rowFirst, columnFirst, rowSecond, columnSecond);

        // Function to multiply two matrices.
        multiplyMatrices(firstMatrix, secondMatrix, mult, rowFirst, columnFirst, rowSecond, columnSecond);

        // Function to display resultant matrix after multiplication.
        display(mult, rowFirst, columnSecond);
}

void enterData(int firstMatrix[][10], int secondMatrix[][10], int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{
	int i, j;
	printf("\nEnter elements of matrix 1:\n");
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnFirst; ++j)
		{
			printf("Enter elements a%d%d: ", i + 1, j + 1);
			scanf("%d", &firstMatrix[i][j]);
		}
	}

	printf("\nEnter elements of matrix 2:\n");
	for(i = 0; i < rowSecond; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			printf("Enter elements b%d%d: ", i + 1, j + 1);
			scanf("%d", &secondMatrix[i][j]);
		}
	}
}

void multiplyMatrices(int firstMatrix[][10], int secondMatrix[][10], int mult[][10], int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{
	int i, j, k;

	// Initializing elements of matrix mult to 0.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			mult[i][j] = 0;
		}
	}

	// Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			for(k=0; k<columnFirst; ++k)
			{
				mult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}
}

void display(int mult[][10], int rowFirst, int columnSecond)
{
	int i, j;
	printf("\nOutput Matrix:\n");
	for(i = 0; i < rowFirst; ++i)
	{
		for(j = 0; j < columnSecond; ++j)
		{
			printf("%d  ", mult[i][j]);
			if(j == columnSecond - 1)
				printf("\n\n");
		}
	}
}