#include "sudokusolver.h"
#include <iostream>
#include <algorithm>
#include <cstring>

SudokuSolver::result_t SudokuSolver::solve()
{
  //TODO: mozebi za da ima nesto od STL da se iskoristi 3d matrix i vector::fill?
  //
  memset(allowedNum_, 0, sizeof(allowedNum_));

  for(int i=0; i<9; i++)
    for(int j=0;j<9; j++)
      if(grid_[i][j] != 0)
        propagateRestriction(i, j, false);

  if(!checkInput())
    return INVALID_INPUT;

  if(searchSolution(0,0))
    return SOLVED;
  else
    return NO_SOLUTION;

}

SudokuSolver::SudokuSolver(Matrix<int> &grid):
  grid_(grid)
{
}

bool SudokuSolver::searchSolution(int i, int j)
{
  if(i > 8)
    return true;

  if(j > 8)
    return searchSolution(i+1, 0);

  if(grid_[i][j] == 0)
  {
    for(int k=1; k<=9; k++)
    {
      if(allowedNum_[i][j][k] == 0)
      {
        grid_[i][j] = k;
        propagateRestriction(i,j, false);

        if(searchSolution(i,j+1))
          return true;

        propagateRestriction(i,j, true);
        grid_[i][j] = 0;
      }
    }
    return false;
  }

  return searchSolution(i, j+1);

}

void SudokuSolver::propagateRestriction(int i, int j, bool isAllowed)
{

  int rval = 1;
  if(!isAllowed)
    rval = -1;

  //Propagate row:
  for(int k=0;k<9;k++)
  {
    if(k == j)
      continue;
    allowedNum_[i][k][grid_[i][j]] += rval;
  }

  //Propagate col:
  for(int k=0;k<9;k++)
  {
    if(k == i)
      continue;
    allowedNum_[k][j][grid_[i][j]] += rval;
  }

  //Propagate region:
  const int ri0 = (i/3)*3, rj0 = (j/3)*3;
  for(int ri = ri0; ri < ri0+3; ri++)
    for(int rj = rj0; rj < rj0+3; rj++)
        if((ri != i) || (rj != j))
            allowedNum_[ri][rj][grid_[i][j]] += rval;

}

bool SudokuSolver::checkInput()
{
  bool isValid = true;
  for(int i=0; i<9; i++)
  {
    for(int j=0; j<9; j++)
    {
      if(allowedNum_[i][j][grid_[i][j]] < 0)
      {
        isValid = false;
        grid_[i][j] = -1;
      }
    }
  }
  return isValid;
}
