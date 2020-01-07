#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <vector>
#include "gridcelledit.h"

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow();
  virtual ~MainWindow();

  QVBoxLayout *mainLayout;
  QHBoxLayout *buttonLayout;
  QGridLayout *mainGrid;

  template<typename T>
  using Matrix = std::vector< std::vector< T >>;

  Matrix<QGridLayout*> subGrids;
  Matrix<GridCellEdit*> input;

public slots:
  void clear();
  void solve();

private:
  void setupGrid();

};

#endif // MAINWINDOW_H
