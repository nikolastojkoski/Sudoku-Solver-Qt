#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <vector>

class SudokuSolver
{
public:

  enum result_t{INVALID_INPUT, NO_SOLUTION, SOLVED};

  template<typename T>
  using Matrix = std::vector< std::vector< T >>;

  SudokuSolver(Matrix<int> &grid_);
  virtual ~SudokuSolver() = default;

  result_t solve();

private:
  Matrix<int> &grid_;
  int allowedNum_[9][9][10];

  bool searchSolution(int i, int j);
  void propagateRestriction(int i, int j, bool isAllowed);
  bool checkInput();

};

#endif // SUDOKUSOLVER_H
