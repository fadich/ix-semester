/* ml.h
	Learning class desription by using the
	"hit-and-near-miss" method and global data
	declaration
*/
//#define  MAX 1000
extern int MAX;

struct attr{
	char subject[80];
	char verb[80];
	char object[80];
	unsigned char active;
};

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//extern FILE  *prtcl;  // protocol file
extern attr *may;    // may-have database
extern attr *must;   // must-have database
extern int may_pos;   // index into may-have database
extern int must_pos;  // index into must-have database


short find_may (char *n, char *v, char *o);
void assert_must (char *n, char *v, char *o);
void assert_may (char *n, char *v, char *o);
void generalize (char *n, char *v, char *o);
void restrict (char *ms, char *mv, char *mo);

//void learn();
//void display();
//short get_example (char *n, char *v, char *o);