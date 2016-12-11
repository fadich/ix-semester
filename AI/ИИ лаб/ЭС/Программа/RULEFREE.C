/* RuleFree.c             IBM-386               10.04.95
CADSHELL complex
*/
#include "expert.h"

void RuleFree()
{
  extern struct RULE  *rule_list;
         struct RULE  *curr_rule;
         struct PREM  *curr_prem;
         struct CON   *curr_con;

  while (rule_list )    /* rule cycle   */
    {
      curr_rule = rule_list;
/* printf("\nRuleFree: rule=%X", curr_rule);*/
      while (curr_rule->prem)        /* prem cycle   */
        {
          curr_prem = curr_rule->prem;
/* printf("\nRuleFree: prem=%X", curr_prem);*/
          curr_rule->prem = curr_prem->next;
          free(curr_prem);
        }
      while (curr_rule->con)           /* con cycle */
        {
          curr_con = curr_rule->con;
/* printf("\nRuleFree: con=%X", curr_con);*/
          curr_rule->con = curr_con->next;
          free (curr_con);
        }
      rule_list = curr_rule->next;
      free (curr_rule);
    }
} /* end of PGM  */
/* RuleFree -------------------------------------------------------------*/
