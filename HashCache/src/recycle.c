#ifndef STANDARD
# include "standard.h"
#endif
#ifndef RECYCLE
# include "recycle.h"
#endif

reroot *remkroot(size)
size_t  size;
{
   reroot *r = (reroot *)remalloc(sizeof(reroot), "recycle.c, root");
   r->list = (recycle *)0;
   r->trash = (recycle *)0;
   r->size = align(size);
   r->logsize = RESTART;
   r->numleft = 0;
   return r;
}

void  refree(r)
struct reroot *r;
{
   recycle *temp;
   if ((temp = r->list) != NULL) while (r->list)
   {
      temp = r->list->next;
      free((char *)r->list);
      r->list = temp;
   }
   free((char *)r);
   return;
}

/* to be called from the macro renew only */
char  *renewx(r)
struct reroot *r;
{
   recycle *temp;
   if (r->trash)
   {  /* pull a node off the trash heap */
      temp = r->trash;
      r->trash = temp->next;
      (void)memset((void *)temp, 0, r->size);
   }
   else
   {  /* allocate a new block of nodes */
      r->numleft = r->size*((ub4)1<<r->logsize);
      if (r->numleft < REMAX) ++r->logsize;
      temp = (recycle *)remalloc(sizeof(recycle) + r->numleft, 
				 "recycle.c, data");
      temp->next = r->list;
      r->list = temp;
      r->numleft-=r->size;
      temp = (recycle *)((char *)(r->list+1)+r->numleft);
   }
   return (char *)temp;
}

char   *remalloc(len, purpose)
size_t  len;
char   *purpose;
{
  char *x = (char *)malloc(len);
  if (!x)
  {
    fprintf(stderr, "malloc of %d failed for %s\n", 
	    (int)len, purpose);
    exit(SUCCESS);
  }
  return x;
}

