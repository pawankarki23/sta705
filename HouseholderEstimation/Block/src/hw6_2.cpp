
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Table.h"
#include "Block.h"

// checks if text file contains rectangular array of numbers
// empty line signals end of file
// assumes no line has more than 1024 characters
// assumes entries are separated by white space
// assumes there is one row per line
// returns 1 if there is an invalid number or separator
// returns 1 if rows do not have the same number of entries
// returns 0 otherwise, and
// number of rows and columns are returned through arguments
// file pointer is reset to beginning
int is_flat_file(FILE* file, int &nrow, int &ncol)
{
    const int ll = 1025;
    char      line[ll];
    char*     ptr;
    char*     end;
    double    x;
    nrow = 0;
    ncol = 0;
    while(true)
        {
        ptr = fgets(line , ll-1 , file);
        while(isspace(*ptr)) ptr++;
        if(*ptr == 0)  // blank line
        break;
    //    fprintf(stderr, "%s", line);
        int k = 0;
        while(*ptr)
        {
        x = strtod(ptr, &end);
        if(ptr == end) // illegal character
            return 1;
        ptr = end;
        k++;
        //fprintf(stderr, "%12.4g", x);
        while(isspace(*ptr)) ptr++;
        }
        if(nrow)
        {
        if(k != ncol) 
            return 1;
        }
        else
        ncol = k;
        nrow++;
        //fprintf(stderr, "%5d%5d\n", nrow, ncol);
        }
    rewind(file);
    return 0;
}

int main(int argc, char **argv)
{
    char name[100];
    strcpy(name, argv[0]);
    strcat(name, ".out");
    FILE*  out = fopen(name,"w");
    
    int nrow, ncol;
    FILE* in;
    in = fopen("Hald-X.dat", "r");
    if(!in)
    {
        fprintf(stderr, "File not found.\n");
        exit(1);
    }
    if(is_flat_file(in, nrow, ncol))
    {
        fprintf(stderr, "File content not valid.\n");
        exit(1);
    }
    else
        fprintf(stderr, "File has %d rows and %d columns.\n", nrow, ncol);
    
    Block* body = new Block(in, nrow, ncol, "body");
    fclose(in);
    
    body->print(out, "Hald data");
    Block* X = new Block(nrow, "intercept");
    X->adjoin(body);
    X->print(out, "X matrix");
    X->calc_transform(0);
    Table* E = X->get_block(X);
    E->print(out, "Echelon matrix");

    in = fopen("Hald-Y.dat", "r");
    Block* Y = new  Block(in, nrow, 1, "Y");
    Y->print(out, "Y vector");
    fclose(in);
    
    X->calc_transform(0);
    X->apply_transform(Y);
    Y->print(out, "Yx and Yp");
    

    double a[100];

    double c[] = {0,1,0,-1, 0, 0, 0};
    bool estimable = E->calc_a(c, a);
    if(estimable)
    {
        double v = 0.0;
        double e = 0.0;
        for(int i=0; i < E->m; i++)
        {
        fprintf(out, "%12.6lf%12.6lf\n", a[i], Yx[i]);
        v += a[i]*a[i];
        e += a[i]*Yx[i];
        }
        fprintf(out, "v = %.4lf, e = %.4lf\n", v, e);
    }
    else
    {
        fprintf(out, "Not estimable\n");
    }
    fclose( out);
    printf("Output file: %s\n", name);

    return 0;
}

