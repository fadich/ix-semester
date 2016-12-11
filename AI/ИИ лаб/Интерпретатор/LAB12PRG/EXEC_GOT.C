 /*exec_goto.c           IBM          19.03.1995
 */
  void  exec_goto ()
  {
         char  *loc;
  extern char  *prog, token[];

     get_token();
     loc = (char *) find_label (token);
     if (loc == '\0')
	serror (7,"exec_goto");
      else
	prog = loc;
  }
/*--------------------------------------------------------------------*/
