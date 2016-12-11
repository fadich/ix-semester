/* greturn.c           19.03.95
*/
void greturn()
{
extern char *prog;

prog = (char *) gpop();
}
