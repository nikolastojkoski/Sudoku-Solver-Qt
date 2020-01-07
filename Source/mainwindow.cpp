#include "mainwindow.h"
#include <QIntValidator>
#include <QPalette>
#include <QColor>
#include <QMessageBox>
#include "sudokusolver.h"

MainWindow::MainWindow()
{

  setWindowTitle("Sudoku Solver");

  QPixmap bkgnd(":/images/background.png");
  QPalette palette;
  palette.setBrush(QPalette::Background, bkgnd);
  setPalette(palette);

  setupGrid();

  buttonLayout = new QHBoxLayout();
  buttonLayout->setMargin(25);

  QPushButton *buttonSolve = new QPushButton("Solve");
  buttonSolve->setFixedSize(150,35);
  connect(buttonSolve, SIGNAL(released()), this, SLOT(solve()));
  buttonLayout->addWidget(buttonSolve);

  QPushButton *buttonClear = new QPushButton("Clear");
  buttonClear->setFixedSize(150,35);
  connect(buttonClear, SIGNAL(released()), this, SLOT(clear()));
  buttonLayout->addWidget(buttonClear);

  mainLayout = new QVBoxLayout();
  mainLayout->addLayout(mainGrid);
  mainLayout->addLayout(buttonLayout);
  mainLayout->setMargin(0);
  mainLayout->setSpacing(0);
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  mainLayout->setAlignment(mainLayout, Qt::AlignLeft);
  setLayout(mainLayout);

}

void MainWindow::setupGrid()
{

  mainGrid = new QGridLayout();
  mainGrid->setMargin(5);
  mainGrid->setSpacing(5);

  subGrids.resize(3, std::vector<QGridLayout*>(3));
  input.resize(9, std::vector<GridCellEdit*>(9));

  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {

      subGrids[i][j] = new QGridLayout();
      subGrids[i][j]->setMargin(1);
      subGrids[i][j]->setSpacing(1);

      for(int k=0; k<3; k++)
      {
        for(int l=0; l<3; l++)
        {
          int curRow = i*3 + k;
          int curCol = j*3 + l;

          input[curRow][curCol] = new GridCellEdit(curRow, curCol, input);

          subGrids[i][j]->addWidget(input[curRow][curCol], k, l);

        }
      }
      mainGrid->addLayout(subGrids[i][j], i, j);
    }
  }
}

MainWindow::~MainWindow()
{

}

void MainWindow::clear()
{
  QPalette palette;
  palette.setColor(QPalette::ColorRole::Text, Qt::black);

  for(int i=0; i < 9; i++)
  {
    for(int j=0; j < 9; j++)
    {
      input[i][j]->clear();
      input[i][j]->setPalette(palette);
    }
  }
}

void MainWindow::solve()
{
  Matrix<int> grid(9, std::vector<int>(9));
  Matrix<bool> fromUser(9, std::vector<bool>(9, false));

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      int num = input[i][j]->text().toInt();
      grid[i][j] = num;
      if(num != 0)
        fromUser[i][j] = true;
    }
  }

  SudokuSolver solver(grid);
  SudokuSolver::result_t result = solver.solve();

  if(result == SudokuSolver::INVALID_INPUT)
  {
    QPalette palette;
    palette.setColor(QPalette::ColorRole::Text, Qt::red);

    for(int i=0;i<9;i++)
      for(int j=0;j<9;j++)
        if(grid[i][j] == -1)
          input[i][j]->setPalette(palette);

    QMessageBox messageBox;
    messageBox.setWindowTitle("Error");
    messageBox.setText("<p align='center'>Invalid Input!</p>");
    messageBox.setStyleSheet("QLabel{min-width: 200px;}");
    messageBox.exec();

    palette.setColor(QPalette::ColorRole::Text, Qt::black);

    for(int i=0;i<9;i++)
      for(int j=0;j<9;j++)
        if(grid[i][j] == -1)
          input[i][j]->setPalette(palette);

  }
  else if(result == SudokuSolver::NO_SOLUTION)
  {
    QMessageBox messageBox;
    messageBox.setWindowTitle("Error");
    messageBox.setText("<p align='center'>No solution could be found!</p>");
    messageBox.setStyleSheet("QLabel{min-width: 200px;}");
    messageBox.exec();
  }
  else
  {
    QPalette palette;
    palette.setColor(QPalette::ColorRole::Text, QColor(65,105,225));

    for(int i=0;i<9;i++)
    {
      for(int j=0;j<9;j++)
      {
        input[i][j]->setText(QString::number(grid[i][j]));
        if(!fromUser[i][j])
          input[i][j]->setPalette(palette);
      }
    }
  }
}

