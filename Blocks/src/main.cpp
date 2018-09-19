
int main(int argc, char **argv)
  {
  char name[100];
  strcpy(name, argv[0]);
  strcat(name, ".out");

  FILE* logfile = fopen(name,"w");

  double  x[]     = {1.2,2.9,3.8,4.1,5.7,6.3,7.0,8.5,9.2};
  int     treat[] = {0,0,0,1,1,1,2,2,2};

  int nt = 3;
  Block** term = new Block*[nt];
  for(int i=0; i<nt; i++)
    term[i] = new Block();
  term[0]->ones(9);
  term[1]->categories(treat, 3, 9);
  term[2]->numeric(x, 9);
  Block* a = new Block();
  a->adjoin(term, nt);
  a->print(logfile, "Adjoined all");
  a->calc_transform(0);
  Block* b = new Block();
  b->get_block(&a, 0, 0);
  b->print(logfile, "Reduced adjoined matrix");

  int r = 0;
  for(int i=0; i<nt; i++)
    {
    for(int j=0; j<i; j++)
      term[j]->apply_transform(term[i]);
    r = term[i]->calc_transform(r);
    }

  const char* factor[] = {"ones", "treat", "Y"};
  Block* bk;
  char label[100];
  for(int i=0; i<nt; i++)
    for(int j=i; j<nt; j++)
      {
      sprintf(label, "(%s, %s)", factor[i], factor[j]);
      bk = new Block();
      int k = bk->get_block(term, i, j);
      if(k)
        fprintf(logfile, "%s\n%12s\n", label, "NULL");
      else
        bk->print(logfile, label);
      fflush(logfile);
      delete bk;
      }
  fclose(logfile);
  printf("Output file: %s\n", name);
  return 0;
  }

