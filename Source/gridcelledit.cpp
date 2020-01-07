#include "gridcelledit.h"
#include <QIntValidator>

GridCellEdit::GridCellEdit(size_t i, size_t j, Matrix<GridCellEdit*> &matrix):
  matrix_(matrix),
  row_(i),
  col_(j)
{

  static const int width = 62;
  setFixedSize(width,width);
  setAlignment(Qt::AlignCenter);
  setMaxLength(1);
  setValidator(new QIntValidator(1, 9, this));

  static QFont font;
  font.setPointSize(50);
  setFont(font);

}

void GridCellEdit::keyPressEvent(QKeyEvent *event)
{

  switch(event->key())
  {
    case Qt::Key_Up:
      if(row_ > 0)
      {
        clearFocus();
        matrix_[row_-1][col_]->setFocus();
        matrix_[row_-1][col_]->setSelection(0,1);
      }
      break;
    case Qt::Key_Down:
      if(row_ < 8)
      {
        clearFocus();
        matrix_[row_+1][col_]->setFocus();
        matrix_[row_+1][col_]->setSelection(0,1);
      }
      break;
    case Qt::Key_Left:
      if(col_ > 0)
      {
        clearFocus();
        matrix_[row_][col_-1]->setFocus();
        matrix_[row_][col_-1]->setSelection(0,1);
      }
      break;
    case Qt::Key_Right:
      if(col_ < 8)
      {
        clearFocus();
        matrix_[row_][col_+1]->setFocus();
        matrix_[row_][col_+1]->setSelection(0,1);
      }
      break;
    default:
      QLineEdit::keyPressEvent(event);
      break;
  }
}
