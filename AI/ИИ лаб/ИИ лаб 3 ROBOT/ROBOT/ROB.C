/* robot Simulator */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <ctype.h>
void setup(void);
void edit(void);
void teach (void);
int get_point(void);
void run(void);
void moveto_setup(void);
int moveto(int,int);
int move(int,int);
int find_path_down(int,int);
int find_path_right(int,int);
void findt(void);
void finds(void);
void do_move(void);
void ifsense(void);
void get_token(void);
void do_goto(void);
void do_movep(void);
int outrange(int,int);
void position(void);
void make_triangle(int,int);
void make_right_triangle(int,int);
void make_square(int,int);
int recognize (int *, int *, char);
int istriangle(int,int);
int isright(int,int);
int issquare(int,int);
int follow(int,int);
int find_direction(int,int,int *,int *);
void assert_oldp(int,int);
int find(int,int);
int find_point(int,int,int *,int *);
int check_point(int,int);
void gotoxy(int,int);
void cls(void);
void clear_db(void);
void serror(char[]);
#define MAX 200
#define SQUARE 0
#define TRIANGLE 1
/* database for delta-D recognizer */
struct oldpoints{
  int x,y;
} oldp[MAX];
 int pos=0; /*index into oldp database */
struct loc_point {
  int x,y;
  char name[30];
} point[MAX];
#define PROGSIZE 1000
char prog[PROGSIZE]; /* holds the robot program */
char *p_pos=0;  /* points into the sentence */
char token[80];  /* contains the word */
char cur_x,cur_y;  /* current x,y pos of robot */

main()
{
 char ch;
 register int t;

 cls();
 for(t=1;t<MAX;t++) *(point[t].name)= '\0';
 for(;;) {
 gotoxy(0,24);
 printf("chose:(E)dit,(R)un,(T)each,(Q)uit:");
 setup();  /* restatr each time */
 switch (tolower(getch())) {
    case 'e':
	     edit();
	     break;
    case 'r':
	     position();
	     run();
	     break;
    case 't':
	     teach();
	     cls();
	     break;
    case 'q':exit(1);
   }
  }
 }


void setup()
{
 pos=0;
 p_pos=prog;
 cur_x=cur_y=0;
 return;
}


/* input a program */
void edit()
{
 char s[100];
 printf("\n");
 *prog='\0';
 do {
  printf(":");
  gets(s);
  if(*s) {
   strcat(s,"\n");
   strcat(prog,s);
  }
 } while(*s);
 return;
}


/* teach the robot certain moves */
void teach()
{
 int x,y;
 int i;
 char name[30],num[10];
 strcpy(name,"point");
 position();
 gotoxy(0,0);
 x=cur_x;y=cur_y;
 for(;;) {
  switch (tolower(getch())) {
    case '8':
	     if(move(x,y-1)) y--;
	     break;
    case '2':
	     if(move(x,y+1)) y++;
	     break;
    case '4':
	     if(move(x-1,y)) x--;
	     break;
    case '6':
	     if(move(x+1,y)) x++;
	     break;
    case '0':
	     i=get_point();
	     if (i) {
	     itoa(i,num,10);
	     strcpy(point[i].name,name);
	     /*increment point name */
	     strcat(point[i].name,num);
	     gotoxy(0,24);
	     printf("%s stoped with x=%d,y=%d (Enter)",
		     point[i].name, x, y);
	     getch();
	     printf("               		         ");
	     point[i].x=x;
	     point[i].y=y;
	  }
	  break;
    case'1':
	    cur_x=cur_y=0;/*reset globals */
	    return;
     }
    }
  }


/* return index of an open slot in the point database */
int get_point()
 {
  register int t ;
  for(t=1;t<MAX;t++)
   if(!*(point[t].name)) return t;
  return 0;
 }


/* execute a robot program */
void run()
 {
  get_token();
  while(*token)
   {
     /*gotoxy (0, 24);
     printf("run: token = %s      ", token);
     getch(); */
     if (!strcmp(token,"moveto")) moveto_setup();
     if (!strcmp(token,"findt")) findt();
     if (!strcmp(token,"finds")) finds();
     if (!strcmp(token,"move")) do_move();
     if (!strcmp(token,"ifsense")) ifsense();
     if (!strcmp(token,"goto")) do_goto();
     if (!strcmp(token,"movep")) do_movep();
     get_token();
  }
  return;
 }


void moveto_setup()
{
 int x,y;
 get_token();
 x=atoi(token);
 get_token();
 y=atoi(token);
 if(outrange(x,y)) {
  serror("moveto arguments out of range\n");
  printf("\nMS:x=%d, y=%d, %d", x,y, outrange(x,y));
  getch();
 }
 else moveto(x,y);
 return;
}


/* move to a point */
moveto (x,y)
int x,y;
{
 char incx,incy;
  int x0,y0;

 x0 = x; y0 = y;
 x = x - cur_x;
 y = y - cur_y;
 do {
  while(y) {
   if(y<0) incy=-1;else incy=1;
   if(move(cur_x,cur_y+incy))
    y-=incy;
   else x+=find_path_right(cur_x,cur_y);
  }
  while(x) {
   if(x<0) incx=-1;else incx=1;
   if(move(cur_x+incx,cur_y))
    x-=incx;
   else y+=find_path_down(cur_x,cur_y);
  }
 } while(x || y);
/* gotoxy (x0, y0);
 putchar ('O');  */
 getch();
 return;
}


/* moves the robot to specified point if possible */
int move (x,y)
int x,y;
{
 if(outrange(cur_x,cur_y))return 0;
 if(check_point(x,y))return 0;
 gotoxy(cur_x,cur_y);
 putchar('.');
 gotoxy(x,y);
 putchar('#');
 cur_x=x, cur_y=y;
 return 1;
}

 find_path_down(x,y)
 int x,y;
{
 if(check_point(x,y+1)) {
   move(cur_x,cur_y-1);
   return 1;
 } else {
   move(cur_x,cur_y+1);
   return -1;
  }
 }


find_path_right(x,y)
 int x,y;
{
 if(check_point(x+1,y)) {
   move(cur_x-1,cur_y);
   return 1;
 } else {
   move(cur_x+1,cur_y);
   return -1;
  }
 }


/* find a triangle */
void findt()
{
 int x,y,i;
 i = recognize(&x,&y,TRIANGLE);
 if (i)
   { gotoxy (0, 24);
     printf("recognize triangle Ok, x=%d,y=%d",x,y);
     getch();
     move (x-1,y);
   }
   else {serror ("recognize triangle not Ok");
	 getch();
	}
 return;
}

 /* find a square  */
void finds()
{
  int x,y;
  if (recognize (&x,&y,SQUARE))
      { gotoxy (0, 24);
	printf("recognize square Ok, x=%d,y=%d", x,y);
	getch();
	move (x-1,y);
	}
     else {serror ("recognize square not Ok with finds");
	   getch();
	  }
}


void do_move()
{
 get_token();
  if (!strcmp(token,"up")) move(cur_x,cur_y-1);
  else if(!strcmp(token,"down")) move(cur_x,cur_y+1);
  else if (!strcmp(token,"left")) move(cur_x-1,cur_y);
  else if (!strcmp(token,"right")) move(cur_x+1,cur_y);
  return;
}


void ifsense()
{
 char xinc,yinc;
 xinc=yinc=0;
 get_token();
 if (!strcmp(token,"up")) yinc=-1;
 else if(!strcmp(token,"down")) yinc=1;
 else if (!strcmp(token,"left")) xinc=-1;
 else if (!strcmp(token,"right")) xinc=1;
 if (!check_point (cur_x+xinc,cur_y+yinc))
   {
    /* failure,so find next statemens */
    while(*p_pos!='\n' && *p_pos!='\0') p_pos++;
    return;
   }
 get_token();
/* check for "then" */
if (strcmp (token,"then"))
  { gotoxy (0, 23);
    printf("token=%s", token);
    serror("-then-expected\n");
  }
 return;
}


/* perform the goto */
void do_goto()
{
 char *p, label[80];

 get_token();
 strcpy (label,token);
 p = p_pos;
 p_pos = prog; /* start at top and look for label */
 get_token();
 while (*token)
   {
    if (!strcmp (label, token)) return; /* found */
    get_token();
   }
 p_pos=p;
 return;
}

  /* not found so clean up */
void  do_movep()
{
 register int t;

 get_token();
 for (t=1; t<MAX; t++)
   {
    if (!strcmp (point[t].name,token))
     {
       moveto(point[t].x,point[t].y);
       return;
     }
   }
serror("point not found");
return;
}


int outrange (x,y)
    int x,y;
{
 /*printf("\n\rOutrange: x=%d, y=%d", x,y); */
 if (x<0 ) return 1;
 if (x>79) return 1;
 if (y<0 ) return 1;
 if (y>24) return 1;
 return 0;
}

/* return a token from theinput stream */
void get_token()
{
  char *p;
  p=token;
  /* skip spaces */
  while(*p_pos==' ') p_pos++;
  if(*p_pos=='\n') {
    *p++='\n';
    *p++='\0';
    p_pos++;
    return;
  }
  if(*p_pos=='\0') {
    *p++='\0';
    return;
  }
  /* read the word until a space or newline  */
  while(*p_pos != ' ' && *p_pos != '\n') {
    *p = *p_pos++;
    p++;
  }
  *p='\0';
  return;
}


void position()
{
 cls();
 make_triangle(10,4);
 make_square(30,10);
 make_right_triangle(50,11);
 return;
}


/* draw an isosceles triangle at x,y */
void  make_triangle(x,y)
 int x,y;
{
 int t;
 for(t=0;t<5;t++) {
 gotoxy(x-t,y+t);
 printf("*");
}
 for(t=0;t<5;t++) {
 gotoxy(x+t,y+t);
 printf("*");
}
 gotoxy(x-5,y+5);
 printf("***********");
 return;
}


/* draw a right triagle at x,y */
void make_right_triangle(x,y)
int x,y;
{
 int t;
 for(t=0;t<10;t++) {
 gotoxy(x,y+t);
 printf("*");
}
 for(t=0;t<9;t++) {
 gotoxy(x-t+9,y+t);
 printf("*");
}
 gotoxy(x,y);
 printf("***********");
 return;
}


/* draw a square at x,y */
void make_square(x,y)
int x,y;
{
 int t;
 for(t=0;t<5;t++)
 {
 gotoxy(x,y+t);
 printf("*");
}
 for(t=0;t<5;t++)
 {
 gotoxy(x+10,y+t);
 printf("*");
 }
 gotoxy(x,y);
 printf("***********");
 gotoxy(x,y+5);
 printf("***********");
 }

 /* The delta-D recognizer  */
int recognize (x1,y1,obj)
    int  *x1,*y1;
   char  obj;
{
 int x,y,t;

 t=0;
 x=cur_x;
 y=cur_y;
 if( obj == TRIANGLE)
  while (find_point(x,y,&x,&y))
    { if(istriangle(x,y))
       { gotoxy(t*40,0); t++;
	 *x1=x, *y1=y;
	 return 1;
       }
      x++;
    }
  else
    { clear_db();
       while (find_point(x,y,&x,&y))
	 { if(issquare(x,y))
	    { gotoxy(0,1); t++;
	      *x1=x,*y1=y;
	      return 1;
	    }
	  x++;
	 }
    }
 return 0;
}


/* check for an isosceles triagle by key points */
int istriangle (x,y)
    int x,y;
{
 if (follow (x,y) == 2) return 1;
 return 0;
}


/* check for a right triagle by key points */
int isright(x,y)
int x,y;
{
 if (check_point(x+10,y) && check_point(x,y+9))
 return 1;
 return 0;
}


/* check for a square by key points */
int issquare(x,y)
int x,y;
{
 if(follow(x,y)==3) return 1;
 return 0;
}


/* follow a share and return number of turns */
int  follow(x,y)
    int x,y;
{
 int incx,incy,startx,starty,count;

 startx=x, starty=y;
 count=0;
 assert_oldp(x,y);
 if (!find_direction(x,y,&incx,&incy)) return 0;
 do
   { while (check_point(x+incx,y+incy))
      { x=incx+x;
	y=incy+y;
	assert_oldp(x,y);
      }
    if(x==startx && y==starty)  return count;
    count++;
    if (!find_direction(x,y,&incx,&incy)) return 0;
   } while(1);
}


/* find a newline to follow */
find_direction(x,y,incx,incy)
int x,y,*incx,*incy;
{
 register int a,b;

 for (a=-1; a<2; a++)
   for( b=-1; b<2; b++)
      if (check_point(x+a,y+b) && !find(x+a,y+b))
	{ *incx=a;
	  *incy=b;
	  return 1;
	}
 return 0;
}


void assert_oldp(x,y)
int x,y;
{
 if(pos==MAX) {
  printf("point database full\n");
  return;
 }
 if(find(x,y)) return; /* already in db */
 oldp[pos].x=x;
 oldp[pos].y=y;
 pos++;
}


find(x,y)
int x,y;
{
 register int t ;

 for(t=0;t<pos;t++) {
  if(oldp[t].x==x && oldp[t].y==y) return 1;
 }
return 0;
}


int find_point (startx,starty,x,y)
    int startx, starty, *x, *y;
{
 int a,b;
 a=startx; b=starty;
 do
  { do
     { /*putchar('+');*/
       if (check_point(a,b))
	{ *x=a;  *y=b;
       /*	  putchar('1');
	  getch();
	  gotoxy(a,b);
	  putchar('*');  */
	  return 1;
	}
       a++;
     } while(a<79);
    a=0;
    b++;
  } while(b<24);
 putchar ('o');
 getch();
 return 0;
}


/* checks to see if the point is an '*' */
check_point(a,b)
int a,b;
{
 union REGS regs;
 gotoxy(a,b);
 regs.h.ah=8;
 regs.h.bh=0;
 int86(16,&regs,&regs);
 if(regs.h.al=='*') return 1;
 return 0;
}


/* put cursor at x,y */
void gotoxy(x,y)
int x,y;
{
 union REGS regs;
 regs.h.ah=2;
 regs.h.dh=y;
 regs.h.dl=x;
 regs.h.bh=0;
 int86(16,&regs,&regs);
}


/* clear the screen */
void cls()
{
 union REGS regs;
 regs.h.ah=6;
 regs.h.al=0;
 regs.h.ch=0;
 regs.h.cl=0;
 regs.h.dh=24;
 regs.h.dl=79;
 regs.h.bh=7;
 int86(16,&regs,&regs);
}


void clear_db()
{
 register int t;
 for(t=0;t<MAX;t++) oldp[t].x=oldp[t].y=0;
 return;
}

/* report syntax errors */
void serror(s)
char *s;
{
gotoxy(0,24);
printf("                                ");
gotoxy(0,24);
printf(s);
getch();
return;
}
