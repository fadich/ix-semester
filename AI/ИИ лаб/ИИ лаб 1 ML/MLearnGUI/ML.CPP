#include "stdafx.h"
#include "ml.h"

//////////Data structures/////////////////////////
int MAX;
attr *may;    // may-have database
attr *must;   // must-have database
int may_pos;   // index into may-have database
int must_pos;  // index into must-have database
//////////////////////////////////////////////////

/* 04.09.98
     Learning class description by using the
	    "hit-and-near-miss" method
     place an entry into the may-have database
    */
void assert_may (char *n, char *v, char *o)
{
	if (may_pos < MAX)
	{
		strcpy (may [may_pos].subject, n);
		strcpy (may [may_pos].verb, v);
		strcpy (may [may_pos].object, o);
		may [may_pos].active = 1;
		may_pos++;
	}
	else
		puts("Out of memory for may_have database");	
}
/*
	displaying results of learning
*/
/*void display()
{	
	int t;

	printf("\n\nDisplay of description:\n\n May have :");
	//fputs("\n\nDisplay of description:\n", prtcl);
	//fputs("-----------------------\n May have :", prtcl);

	for (t=0; t < may_pos; t++)
		if (may[t].active)
		{ 
			printf ("\n %s %s %s", may[t].subject,		
					may[t].verb,may[t].object);
			//fprintf (prtcl, "\n %s %s %s",may[t].subject,
					//may[t].verb,may[t].object);
		}

	printf("\n\n Must have :");
	//fputs("\n\n Must have:", prtcl);

	for (t=0; t<must_pos; t++)
	{
		printf("\n %s %s %s", must[t].subject,must[t].verb,
				must[t].object);
		//fprintf (prtcl, "\n %s %s %s", must[t].subject,
				//must[t].verb, must[t].object);
	}
}*/

/* 07.09.98
   find and entry in the may have database
*/
short find_may (char *n, char *v, char *o)
{
	int t;

	for (t=0; t<may_pos; t++)
		if (!strcmp(may[t].subject,n) &&
				!strcmp(may[t].verb,v) &&
				!strcmp(may[t].object,o) &&
				may[t].active)
			return t;

	return -1;
}

/* 04.09.98
   generalize new examples
    */
void generalize (char *n, char *v, char *o)
{
	int  t,i;

   /* check may_have list*/
	for (t=0; t<may_pos; t++)
		if (strcmp(may[t].subject,n)  &&  /*not same subject*/
				!strcmp(may[t].verb,v)  &&
				!strcmp(may[t].object,o) && may[t].active){
			strcat(may[t].subject," or ");
			strcat(may[t].subject,n);
		}
	
	for (t=0; t<may_pos; t++)
		if (!strcmp(may[t].subject,n) &&
				!strcmp(may[t].verb,v) &&
				strcmp(may[t].object,o) /*not same object*/
				&& may[t].active)
		{
			strcat(may[t].object," or ");
			strcat(may[t].object,o);
		}

	/*check must_have list */
	for (t=0; t<must_pos; t++)
		if(strcmp(must[t].subject,n)  &&  /*not same subject*/
				!strcmp(must[t].verb,v) && !strcmp(must[t].object,o))
		{
			strcat(must[t].subject," or ");
			strcat(must[t].subject,n);
			i = find_may(n,v,o);
			may[i].active=0; /*remove from may_have list*/
		}

	for (t=0; t<must_pos; t++)
		if (!strcmp(must[t].subject,n) &&
				!strcmp(must[t].verb,v) &&
				strcmp(must[t].object,o)) /*not same object*/
		{
			strcat(must[t].object," or ");
			strcat(must[t].object,o);
			i=find_may(n,v,o);
			may[i].active=0;   /*remove from may_have list*/
		}
      
}

/* 04.09.98
     Learn a class description for an object
  */
/*void learn()
{
	char  sub[80], verb[80], obj[80],
			msub[80], mverb[80], mobj[80];

	while (1){

		printf("\nEnter an example.");
		//fputs("\n\nEntering an example.", prtcl);
		if (!get_example(sub, verb, obj)) 
			return;
		if (find_may(sub,verb,obj)==-1){
			assert_may (sub,verb,obj);
			generalize (sub,verb,obj);
		}
		printf("Enter a near-miss (<NL> to skip).");
		//fputs("\n\nEnter a near-miss (<NL> to skip).", prtcl);
		get_example(msub, mverb, mobj);
		restrict(msub, mverb, mobj);
	}

}*/

/* 04.09.98
  place an entry into the must have database */
void assert_must (char *n, char *v, char *o)
{
	if (must_pos < MAX)
	{
		strcpy(must[must_pos].subject,n);
		strcpy(must[must_pos].verb,v);
		strcpy(must[must_pos].object,o);
		must_pos ++;
	}
	else{
		//puts("Out of memory for must have database\n");
		MessageBox(0, "Out of memory for must have database", NULL,
				MB_OK | MB_ICONSTOP);
	}
}

/* 04.09.98
   restrict the description of an object- i. e. remove from
    may-have list and place in must-have list.
     */
void restrict (char *ms, char *mv, char *mo)
{
	int t;
	char temp[4];
        
	for(t=0; t<3; t++)
		temp[t] = mv[t];
	temp[3] = '\0';
	strlwr(temp);
	if(strcmp(temp,"not"))
		return;

	for (t=0; t<may_pos; t++){
		if (!strcmp (&mv[4],may[t].verb) &&
				!strcmp (may[t].subject,ms) &&
				!strcmp (may[t].object,mo) && may[t].active){
			assert_must(may[t].subject, may[t].verb, may[t].object);
			may[t].active = 0; /*remove from list*/
			return;
		}
	}
}

/* get_exmp.c                      07.09.98
       input definition
    */
short get_example (char *n, char *v, char *o)
{
	printf("\n subject: ");
	gets(n);
	if (!*n)
		strcpy(n, "<NL>");
	//fprintf (prtcl, "\n subject: %s", n);

	if (n[0]=='<' && n[1]=='N'
			&& n[2]=='L' && n[3]=='>')
		return 0;

	printf("    verb: ");
	gets(v);
	printf("  object: ");
	gets(o);
	//fprintf(prtcl,"\n    verb: %s\n  object: %s", v, o);

	return 1;
}