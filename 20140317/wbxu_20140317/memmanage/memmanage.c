#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "memmanage.h"
#include "fit.h"
#include "table.h"
#include "ui.h"

//storage for your input.
char g_chBuf[MAX_SPACE];

//used for maintain
//seems a waste.
int g_add_table[MAX_SPACE];
int g_del_table[MAX_SPACE];

//how many (size, start) are stored into table;
int g_indexMAX_add;
int g_indexMAX_del;
int g_indexMAX_buf;

//the way you can get suitable size
int g_fitWAY = FIT_EQUAL;

int 
query(char chInput[], int *index)
{
    int i;
    int size;
    int result;

    result = NOT_EXIST;

    size = strlen(chInput) + 1;

    for (i = 0; i < g_indexMAX_add; i += 2)
    {
        if (size != g_add_table[i])
        {
            continue;
        }

        if (0 == strcmp(&g_chBuf[g_add_table[i + 1]], chInput))
        {
            *index = i;
            result = SUCCESS;

            break;
        }
    }

    return result;
}


int
store(char chBuf[], int start, char chInput[], int requestsize)
{
    int result = SUCCESS;

    //make sure g_indexMAX_buf updated
    if (start == g_indexMAX_buf)
    {
        if (MAX_SPACE == g_indexMAX_buf)
        {
            result = NO_SPACE;
            return result;
            
        }
        g_indexMAX_buf += requestsize;
    }

    strcpy(&chBuf[start], chInput);
    chBuf[start + requestsize - 1] = '\0';

    return result;
} 


int
add(char chInput[])
{
    int requestsize;
    int index;  //index of (size, start) within g_del_table
    int start;
    int size;

    int result;
    result = NO_SPACE;
        
    //we also store the '\0'
    requestsize = strlen(chInput) + 1;

    result = getsize(requestsize, &index);

    //no suitable size, we just store into g_chBuf[g_indexMAX_buf]
    if (NOT_EXIST == result)
    {
        result = store(g_chBuf, g_indexMAX_buf, chInput, requestsize);
       
        if (NO_SPACE == result)
        {
            //failed, no space
            return result;
        }

        start = g_indexMAX_buf - requestsize;

        updatetable(g_add_table, g_indexMAX_add, requestsize, g_indexMAX_buf - requestsize);

        g_indexMAX_add += 2;        
    }
    else
    {
        size  = g_del_table[index];
        start = g_del_table[index + 1];
        result = store(g_chBuf, start, chInput, requestsize);

        if (NO_SPACE == result)
        {
            //failed
            return result;
        }


        if (requestsize == size)
        {
            removefromtable(g_del_table, &g_indexMAX_del, index);
            insertintoaddtable(g_add_table, &g_indexMAX_add, size, start);
        }
        else
        {
            updatetable(g_del_table, index, size - requestsize, start + requestsize);
            insertintoaddtable(g_add_table, &g_indexMAX_add, requestsize, start);
        }
    }//end for else

    result = start;

    return result;
}


int
del(char chInput[])
{
    //indexpre(sizepre, startpre), index(size, start), indexaft(sizeaft, startaft)
    int index;
    int size;
    int start;
    int result;

    result = query(chInput, &index);

    if (NOT_EXIST == result)
    {
        //failed; not exist
        return result;
    }
    else
    {
        size  = g_add_table[index];
        start = g_add_table[index + 1];

        insertintodeltable(g_del_table, &g_indexMAX_del, size, start);
        removefromtable(g_add_table, &g_indexMAX_add, index); 
        

    }//end for result != NOT_EXIST

    return result;
}


int
modify(char origin[], char newinput[])
{
    int index;
    int oldsize, newsize;
    int start;

    int result;

    result = query(origin, &index);

    if (NOT_EXIST == result)
    {
        //not exist
        return result;
    }
    else    
    {
        oldsize = strlen(origin) + 1;
        newsize = strlen(newinput) + 1;

        start = g_add_table[index + 1];

       
        if (newsize < oldsize)
        {
            // this will generate unused space, we need to update g_add_table and g_del_table;
            result = store(g_chBuf, start, newinput, newsize);
            if (NO_SPACE == result)
            {
                //failed, no more space
                return result;
            }

            updatetable(g_add_table, index, newsize, start);
            insertintodeltable(g_del_table, &g_indexMAX_del, oldsize - newsize, start + newsize);
        }
        else if (newsize == oldsize)
        {
            //just replace directly
            result = store(g_chBuf, start, newinput, newsize);
            if (NO_SPACE == result)
            {
                //failed, no space.
                return result;
            }

        }
        else
        {
            del(origin);
            result = add(newinput);
        }
    }//end for result != NOT_EXIST

    return result;
}

void
display(void)
{
    int i;
    int size;
    int start;

    for (i = 0; i < g_indexMAX_add; i +=2)
    {
        size  = g_add_table[i];
        start = g_add_table[i + 1];

        printf("%s  start: %d, size: %d\r\n", &g_chBuf[start], start, size);
    }
}



void
showbuf(int index, int len)
{
    int i;

    if (index < 0)
    {
        index = 0;
    }

    for (i = index; i < index + len; i++)
    {
        if ('\0' == g_chBuf[i])
        {
            printf("\\0 ");
        }
        else
        {
            printf("%c ", g_chBuf[i]); 
        }
    }
}

void
statistics(void)
{
    int index_buf;
    int col;  
    int max;
    int table;
    int start;
    int len;
    int remain;
    int i;

    char flag;

    index_buf = 0;
    col       = 0;

    table     = ADD;
    max       = -1;

    for ( ; index_buf < g_indexMAX_buf; index_buf++)
    {
        //this index belong to which one? g_add_table, g_del_table ?
        if (index_buf >= max )
        {
            table = gettable(index_buf, &max);            
        }
        else
        {
            //that is to keep the table result last time unchanged.
            //so no need to gettable again.
        }
        

        if (ADD == table)       //used
        {
            flag = 'U';
        }
        else if (DEL == table)  //free
        {
            flag = 'F';
        }
        else
        {
            //sth wrong?
            //printf("Sth wrong?");
            getchar();
        }

        if (0 == col % (SPLIT))
        {
            printf("%d: ", col);
        }
       
        printf("%c ", flag);
        

        if ((col != 0)
            &&(0 == (col + 1) % (SPLIT)) )
        {
            printf("    ");
            //
            start = col + 1 - (SPLIT);
            len   = SPLIT;
            showbuf(start, len);

            printf("\r\n\r\n");

        }

        col += 1;
    } 
    
    //
    remain = (SPLIT) - col % (SPLIT);
    for (i = 0; i < remain; i++)
    {
        printf("  ");
    }
    printf("  ");
    
    len   = (SPLIT) - remain;
    start = col - len;
    
    showbuf(start, len);
    
}

/*
Function: used for debug, show detail info about g_add_table, g_del_table
*/
void
showtable(void)
{
    int i;
    
    printf("\r\n[Debug]showing g_add_table, g_del_table  (size, start) ......\r\n");
    
    printf("g_add_table:\r\n");
    for (i = 0; i < g_indexMAX_add; i += 2)
    {
        printf("(%d %d) ", g_add_table[i], g_add_table[i+1]);
    }
    printf("\r\n\r\n");
    
    printf("g_del_table:\r\n");
    for (i = 0; i < g_indexMAX_del; i += 2)
    {
        printf("(%d %d) ", g_del_table[i], g_del_table[i+1]);
    }
    printf("\r\n\r\n"); 
}


void
process(int select)
{
    int index;
    char chInput[MAX_INPUT];
    char newinput[MAX_INPUT];
    int result;

    switch (select)
    {
    default:
        {
            printf("Please make the right decision ^_^\r\n");
            break;
        }

    case 1:
        {
            //Add
            printf("Add what ? ");
            getinput(chInput);
            
            result = add(chInput);
            if (NO_SPACE == result)
            {
                printf("Add failed, for No More Space\r\n");
            }
            else
            {
                printf("ADD: store into %d\r\n", result);
            }

            break;
        }

        
    case 2:
        {
            //query
            printf("Query what ? ");
            getinput(chInput);

            result = query(chInput, &index);

            if (NOT_EXIST == result)
            {
                printf("Query: not exist\r\n");
            }
            else
            {
                printf("Query: at %d\r\n", g_add_table[index + 1]);
            }

            break;
        }

        
    case 3:
        {
            //del
            printf("Del what ? ");
            getinput(chInput);
            
            result = del(chInput);

            if (-1 == result)
            {
                printf("%s does not exist\r\n", chInput);
            }
            else
            {
                printf("Del ok\r\n");
            }
            
            break;
        }
        

        
    case 4:
        {
            //modify
            printf("Modify, origin ? ");
            getinput(chInput);
            
            printf("newinput ? ");
            getinput(newinput);
            
            result = modify(chInput, newinput);
            if (NOT_EXIST == result)
            {
                printf("Modify: %s not exist\r\n", chInput);
            }
            else if (NO_SPACE == result)
            {
                printf("Modify: no more space to store newinput\r\n");
            }
            else
            {
                printf("Modify ok\r\n");
            }
            
            break;
        }

        
    case 5:
        {
            //display:
            printf("Displaying......\r\n");
            
            display();
            
            break;
        }

        
    case 6:
        {
            //statistics
            printf("Statisticsing......U for Used, F for Free\r\n\r\n");
            
            statistics();
            break;
        }

    case 7:
        {
            //set fit
            printf("Please choose the fit way\r\n");

            showfit();

            getselect(&select);

            if (select < FIT_EQUAL || select > FIT_EQUAL_FIRST )
            {
                printf("Please make the right decision ^_^\r\n");
            }
            else
            {
                setfit(select);
            }
        }

    }//end for switch
}

int
main(void)
{
    int select;

    while (1)
    {
        showmenu();

        getselect(&select);

        if (0 == select)
        {
            break;
        }

        process(select);

        showtable();

        printf("\r\n\r\n");
    }

    return 0;
}