/*
Unfinished attempt to implement Schnabel and Eskows'
"A new modified cholesky factorization"
*/  
int Triangular::schnabel_eskow()
  {
#ifdef X  
  double tau      = 0.000001;
  bool   phaseone = true;
  double gamma    = fabs(p[0][0]);
  
  for(int i=1; i<n; i++)
    if(fabs(p[i][i]) > gamma)
      gamma = fabs(p[i][i]);
  int j = 0;
  int i = j;
  while( (j<n) and phaseone)
    {
    double max = p[j][j];
    for(int l=j+1; l<n; l++)
      if(p[l][l] > max)
        {
        i = l;
        max = p[l][l];
        }
    if(i != j)
      interchange(j, i);
    double min = HUGE_VAL;
    for(int l=j+1; l<n; l++)
      if(p[l][l] - pow(p[j][l],2)/p[j][j] < min)
        min =  p[l][l] - pow(p[j][l],2)/p[j][j];
    if(min < tau*gamma)
      phaseone = false;
    else
      {
      p[j][j] = sqrt(p[j][j]);
      for(int l=j+1; l<n; l++)
        p[j][l] /= p[j][j];
      for(int l=j+1; l<n; l++)
        for(int m =l; m<n; m++)
          p[l][m] -= p[j][l]*p[j][m];
      }
    j++;
    }
  if(not phaseone)
    {
    int k = j-1;
    }
#endif
  return 0;
  }

