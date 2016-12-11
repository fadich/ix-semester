#define MAX 100
 /* структура базы данных рейсов */
struct FL 
  { char  from[20];
    char  to [20];
     int  distance;
    char  skip;  /* used in backtracking  */
  };
struct stack
  { char  from[20];
    char  to[20];
     int  dist;
};

 