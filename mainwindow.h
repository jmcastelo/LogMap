// Copyright 2020 José María Castelo Ares

// This file is part of LogMap.

// LogMap is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// LogMap is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with LogMap.  If not, see <https://www.gnu.org/licenses/>.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logistic.h"
#include "qcustomplot.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSlider>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Logistic logistic;

    QLabel *parameterLabel;
    QSlider *parameterSlider;

    QDoubleSpinBox *initialCondition0SpinBox;
    QDoubleSpinBox *initialCondition1SpinBox;

    QCustomPlot *orbitPlot;
    QCustomPlot *bifurcationsPlot;
    QCustomPlot *lyapunovPlot;
    QCustomPlot *histogramPlot;
    QCPBars *histogram;

    void setOrbitPlot();
    void orbitPlotRangeChanged(QMouseEvent *event);
};

#endif // MAINWINDOW_H
