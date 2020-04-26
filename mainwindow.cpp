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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    // Parameter controls

    parameterLabel = new QLabel;
    parameterLabel->setText(QString("Parameter: %1").arg(logistic.parameter));

    parameterSlider = new QSlider(Qt::Horizontal);
    parameterSlider->setMinimum(0);
    parameterSlider->setMaximum(logistic.parameterIntervalSize);

    QHBoxLayout *parameterHBoxLayout = new QHBoxLayout;
    parameterHBoxLayout->addWidget(parameterLabel);
    parameterHBoxLayout->addWidget(parameterSlider);

    // Main controls

    // Orbit controls

    QLabel *initialCondition0Label = new QLabel("Initial condition:");

    initialCondition0SpinBox = new QDoubleSpinBox;
    initialCondition0SpinBox->setRange(0, 1);
    initialCondition0SpinBox->setValue(logistic.initialCondition[0]);
    initialCondition0SpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    QLabel *initialCondition1Label = new QLabel("Initial condition:");

    initialCondition1SpinBox = new QDoubleSpinBox;
    initialCondition1SpinBox->setRange(0, 1);
    initialCondition1SpinBox->setValue(logistic.initialCondition[1]);
    initialCondition1SpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    QVBoxLayout *orbitVBoxLayout = new QVBoxLayout;
    orbitVBoxLayout->addWidget(initialCondition0Label);
    orbitVBoxLayout->addWidget(initialCondition0SpinBox);
    orbitVBoxLayout->addWidget(initialCondition1Label);
    orbitVBoxLayout->addWidget(initialCondition1SpinBox);

    QGroupBox *orbitGroupBox = new QGroupBox("Orbit");
    orbitGroupBox->setLayout(orbitVBoxLayout);

    // Main controls vertical layout & widget

    QVBoxLayout *mainControlsVBoxLayout = new QVBoxLayout;
    mainControlsVBoxLayout->addWidget(orbitGroupBox, 0, Qt::AlignTop);

    QWidget *mainControlsWidget = new QWidget;
    mainControlsWidget->setLayout(mainControlsVBoxLayout);

    // Plots

    // Orbit plot

    orbitPlot = new QCustomPlot(this);

    orbitPlot->xAxis->setLabel("Iteration");
    orbitPlot->yAxis->setLabel("x");

    orbitPlot->yAxis->setRange(0, 1);

    orbitPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    orbitPlot->axisRect()->setupFullAxesBox(true);
    orbitPlot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    orbitPlot->axisRect()->setRangeDrag(Qt::Vertical | Qt::Horizontal);

    orbitPlot->addGraph();
    orbitPlot->graph(0)->setName("Orbit");

    orbitPlot->legend->setVisible(true);
    orbitPlot->legend->setBrush(QColor(255, 255, 255, 150));

    setOrbitPlot();

    // Histogram plot

    histogramPlot = new QCustomPlot(this);

    histogramPlot->axisRect()->setupFullAxesBox(true);

    histogramPlot->xAxis->setLabel("x");
    histogramPlot->yAxis->setLabel("Histogram");

    histogram = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);

    // Bifurcations plot

    bifurcationsPlot = new QCustomPlot(this);

    bifurcationsPlot->xAxis->setLabel("Parameter");
    bifurcationsPlot->yAxis->setLabel("x");

    bifurcationsPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    bifurcationsPlot->axisRect()->setupFullAxesBox(true);
    bifurcationsPlot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    bifurcationsPlot->axisRect()->setRangeDrag(Qt::Vertical | Qt::Horizontal);

    bifurcationsPlot->setBackground(QBrush(Qt::black));
    QList<QCPAxis*> bifurcationsPlotAxes = bifurcationsPlot->axisRect()->axes();
    for (QCPAxis *axis : bifurcationsPlotAxes)
    {
        axis->setBasePen(QPen(Qt::white));
        axis->setTickPen(QPen(Qt::white));
        axis->setSubTickPen(QPen(Qt::white));
        axis->setTickLabelColor(Qt::white);
        axis->setLabelColor(Qt::white);
    }

    bifurcationsPlot->addGraph();
    bifurcationsPlot->graph(0)->setName("Bifurcations");

    // Lyapunov plot

    lyapunovPlot = new QCustomPlot(this);

    lyapunovPlot->xAxis->setLabel("Parameter");
    lyapunovPlot->yAxis->setLabel("Lyapunov exponent");

    lyapunovPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    lyapunovPlot->axisRect()->setupFullAxesBox(true);
    lyapunovPlot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    lyapunovPlot->axisRect()->setRangeDrag(Qt::Vertical | Qt::Horizontal);

    lyapunovPlot->setBackground(QBrush(Qt::black));
    QList<QCPAxis*> lyapunovPlotAxes = lyapunovPlot->axisRect()->axes();
    for (QCPAxis *axis : lyapunovPlotAxes)
    {
        axis->setBasePen(QPen(Qt::white));
        axis->setTickPen(QPen(Qt::white));
        axis->setSubTickPen(QPen(Qt::white));
        axis->setTickLabelColor(Qt::white);
        axis->setLabelColor(Qt::white);
    }

    lyapunovPlot->addGraph();
    lyapunovPlot->graph(0)->setName("Lyapunov exponent");

    // Orbit + Histogram plots left vertical splitter

    QSplitter *leftSplitter = new QSplitter;
    leftSplitter->setOrientation(Qt::Vertical);
    leftSplitter->addWidget(orbitPlot);
    leftSplitter->addWidget(histogramPlot);
    leftSplitter->setCollapsible(0, true);
    leftSplitter->setCollapsible(1, true);

    // Bifurcations + Lyapunov plots right vertical splitter

    QSplitter *rightSplitter = new QSplitter;
    rightSplitter->setOrientation(Qt::Vertical);
    rightSplitter->addWidget(bifurcationsPlot);
    rightSplitter->addWidget(lyapunovPlot);
    rightSplitter->setCollapsible(0, true);
    rightSplitter->setCollapsible(1, true);

    // Left + Right splitters horizontal splitter

    QSplitter *splittersSplitter = new QSplitter;
    splittersSplitter->setOrientation(Qt::Horizontal);
    splittersSplitter->addWidget(leftSplitter);
    splittersSplitter->addWidget(rightSplitter);
    splittersSplitter->setCollapsible(0, true);
    splittersSplitter->setCollapsible(1, true);

    // Main splitter

    QSplitter *mainSplitter = new QSplitter;
    mainSplitter->setOrientation(Qt::Horizontal);
    mainSplitter->addWidget(mainControlsWidget);
    mainSplitter->addWidget(splittersSplitter);
    mainSplitter->setStretchFactor(0, 0);
    mainSplitter->setStretchFactor(1, 1);
    mainSplitter->setCollapsible(0, true);
    mainSplitter->setCollapsible(1, false);

    // Main vertical layout

    QVBoxLayout *mainVBoxLayout = new QVBoxLayout;

    mainVBoxLayout->addLayout(parameterHBoxLayout);
    mainVBoxLayout->addWidget(mainSplitter);

    setLayout(mainVBoxLayout);

    setWindowTitle("LogMap");

    resize(1200, 800);

    // Signals + Slots

    connect(parameterSlider, &QAbstractSlider::valueChanged, &logistic, &Logistic::parameterIndexChanged);
    connect(&logistic, &Logistic::orbitComputed, this, &MainWindow::setOrbitPlot);
    connect(orbitPlot, &QCustomPlot::mouseRelease, this, &MainWindow::orbitPlotRangeChanged);
    connect(orbitPlot->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ if (orbitPlot->graph(0)->dataCount() > 0) orbitPlot->yAxis->setRange(newRange.bounded(0, 1)); });
}

MainWindow::~MainWindow()
{
}

void MainWindow::setOrbitPlot()
{
    orbitPlot->graph(0)->setData(logistic.orbit[0].x, logistic.orbit[0].y, true);
    orbitPlot->xAxis->setRange(logistic.orbit[0].xMin, logistic.orbit[0].xMax);
    orbitPlot->replot();
}

void MainWindow::orbitPlotRangeChanged(QMouseEvent *event)
{
    Q_UNUSED(event)

    QCPRange xRange = orbitPlot->xAxis->range();

    logistic.orbit[0].xMin = xRange.lower;
    logistic.orbit[0].xMax = xRange.upper;

    logistic.computeOrbit(0);

    setOrbitPlot();
}
