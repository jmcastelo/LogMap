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
#include <QGridLayout>
#include <QSplitter>
#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QSlider>
#include <QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Logistic logistic;

    QDoubleSpinBox *parameterSpinBox;
    QSlider *parameterSlider;
    QSpinBox *parameterValuesSpinBox;
    QPushButton *centerParameterPushButton;
    QPushButton *resetPushButton;
    bool parameterSafetyFlag;

    QDoubleSpinBox *initialCondition0SpinBox;
    QDoubleSpinBox *initialCondition1SpinBox;
    QCheckBox *showSecondOrbitCheckbox;

    QSpinBox *bifurcationsTransientSpinBox;
    QSpinBox *bifurcationsItsSpinBox;

    QSpinBox *histogramTransientSpinBox;
    QSpinBox *histogramItsSpinBox;
    QSpinBox *histogramBinsSpinBox;

    QLabel *lyapunovExponentLabel;
    QSpinBox *lyapunovTransientSpinBox;
    QSpinBox *lyapunovItsSpinBox;

    QCustomPlot *orbitPlot;
    QCustomPlot *bifurcationsPlot;
    QCPItemLine *bifurcationsLine;
    QCustomPlot *lyapunovPlot;
    QCPItemLine *lyapunovLine;
    QCustomPlot *histogramPlot;
    QCPBars *histogram;

    bool bifurcationsPlotMousePressed;
    bool lyapunovPlotMousePressed;

    bool settingBifurcationsPlotXRange;
    bool settingLyapunovPlotXRange;

    void parameterChanged();
    void parameterIndexChanged(int i);
    void parameterValuesChanged();
    void centerParameter();
    void reset();

    void setOrbitPlot();
    void toggleSecondOrbit(int state);
    void initialCondition0Changed();
    void initialCondition1Changed();

    void setBifurcationsPlot();
    void bifurcationsTransientChanged();
    void bifurcationsItsChanged();
    void shiftBifurcationsLine(double value);

    void setHistogramPlot();
    void histogramTransientChanged();
    void histogramItsChanged();
    void histogramBinsChanged();

    void setLyapunovPlot();
    void setLyapunovExponentLabel(int i);
    void lyapunovTransientChanged();
    void lyapunovItsChanged();
    void shiftLyapunovLine(double value);

    void onOrbitPlotXRangeChanged(QCPRange newRange);

    void onBifurcationsPlotMouseRelease();
    void onBifurcationsPlotXRangeChanged(QCPRange newRange);
    void onBifurcationsPlotYRangeChanged(QCPRange newRange);

    void onLyapunovPlotMouseRelease();
    void onLyapunovPlotXRangeChanged(QCPRange newRange);
};

#endif // MAINWINDOW_H
