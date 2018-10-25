  nt = 2;
  term[0] = fb;
  term[1] = yb;
  r = 0;
  for(int i=0; i<nt; i++)
    {
    for(int j=0; j<i; j++)
      term[j]->apply_transform(term[i]);
    r = term[i]->calc_transform(r);
    }
  for(int i=0; i<nt; i++)
    {
    term[i]->print(logfile);
    term[i]->auxiliary(logfile);
    }
  for(int i=0; i<nt-1; i++)
    for(int j=i; j<nt; j++)
      {
      Table* table = term[j]->get_block(term[i]);
      table->print(logfile);
      }

