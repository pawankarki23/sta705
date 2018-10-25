#include <stdio.h>

struct Peg
{
  // stack in the peg 
  int *stack;
  // put disc on a peg
  void push(int);
  // take disc off of a peg
  int  pop();
  // points to the position just above the top element on the peg
  int  top;
  // printing
  void print(int);
  // constructor
  Peg(int n);
};

// definition of constructor  
Peg::Peg(int n)
{
  stack = new int[n];
  // there is no disc on start out
  top   = 0;
}  
  
void Peg::print(int id)
{
  fprintf(stderr, "peg %d:", id);
  for(int i=0; i<top; i++) 
    fprintf(stderr, "%5d", stack[i]);
  fprintf(stderr, "\n");
}

// push the disc into the stack of the peg
void Peg::push(int disk)
{
  stack[top++] = disk;
}


// take out a disc from the stack
int Peg::pop()
{
  return stack[--top];
}

// there are three pegs
Peg *peg[3];


void move_disk(int from, int dest)
{
  // move disc from from to dest peg
  printf("peg %d -> peg %d\n", from, dest);
  int k = peg[from]->pop();
  peg[dest]->push(k);
}
  
void move_stack(int n, int from, int inter, int dest) 
{
  if(n == 0) return;
  // move n-1 stack from form to intermediate state
  move_stack(n-1, from, dest, inter);
  // move rest from to destination
  move_disk(from, dest);
  // move the n-1 from inter to dest
  move_stack(n-1, inter, from, dest);
} 
    
int main()
{
  // we have 5 discs
  const int n = 5;

  // create instances of three pegs
  for(int i=0; i<3; i++)
    peg[i] = new Peg(n);

  // put n disks on peg 0
  for(int i=0; i<n; i++)
    peg[0]->push(i);

  // show initial state  
  for(int i=0; i<3; i++)
    peg[i]->print(i);
  
  // move it  from peg 0 to peg 2 using 1 as intermediate state
  move_stack(n, 0, 1, 2);
  
  // show final state  
  for(int i=0; i<3; i++)
    peg[i]->print(i);
  
  return 0;
}  

