/*  expert.h - h_file for student's expert system shell   C-UNIX  08.04.93
*/
struct LIST     /* universal list  */
   {
            void  *elem;
     struct LIST  *next;
   };
struct VALUE
   {
             char  *name;    /* symbolic name of value     */
            short   cert;    /* certenty factor            */
      struct LIST  *prem,    /* list of the rules including this
                                object-value pair in the prem-part */
                   *con;     /* same only for con-part     */
     struct VALUE  *next;    /* next member of value list  */
   };
struct OBJECT
   {
              char  *name,     /* symbolic name of object    */
                    *question; /* text of question to object */
      struct VALUE  *value;    /* pointer on value list      */
     struct OBJECT  *next;     /* next member of object list */
   };
struct PREM
   {
     struct OBJECT  *obj;     /* pointer on the object     */
      struct VALUE  *value;   /* pointer on the value      */
       struct PREM  *next;    /* next prem of this rule    */
   };
struct CON
   {
     struct OBJECT  *obj;     /* pointer on the object         */
      struct VALUE  *value;   /* pointer on the value          */
               int  cert;     /* certenty factor for this con  */
        struct CON  *next;    /* next con of this rule         */
   };
struct RULE
   {
             int  numb,    /* number of this rule                 */
                  cert;    /* factor of realability of this rule  */
            char  used;    /* 0 - rule doesn't be used
                              1 - rule has been used
                              2 - rule is false: contradiction with facts */
     struct PREM  *prem;   /* pointer on prem list                */
     struct CON   *con;    /* pointer on con list                 */
     struct RULE  *next;   /* next rule of rule list              */
   };

struct STACK
   {
     struct OBJECT *goal;
     struct STACK  *next;
   };

