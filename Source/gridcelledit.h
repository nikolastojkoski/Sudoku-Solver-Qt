#ifndef GRIDCELLEDIT_H
#define GRIDCELLEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <vector>

class GridCellEdit : public QLineEdit
{
public:

  virtual ~GridCellEdit() = default;

  template<typename T>
  using Matrix = std::vector< std::vector< T >>;
  GridCellEdit(size_t i, size_t j, Matrix<GridCellEdit*> &matrix);

protected:
  virtual void keyPressEvent(QKeyEvent *event) override;

private:
  size_t row_, col_;
  Matrix<GridCellEdit*> &matrix_;
};

#endif // GRIDCELLEDIT_H
