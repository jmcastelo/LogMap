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

    QLabel *parameterLabel = new QLabel("Parameter");

    parameterSpinBox = new QDoubleSpinBox;
    parameterSpinBox->setRange(0, 4);
    parameterSpinBox->setDecimals(12);
    parameterSpinBox->setValue(logistic.parameter);
    parameterSpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    parameterSlider = new QSlider(Qt::Horizontal);
    parameterSlider->setMinimum(0);
    parameterSlider->setMaximum(logistic.parameterIntervalSize);
    parameterSlider->setValue(0);

    QLabel *parameterValuesLabel = new QLabel("#Values");

    parameterValuesSpinBox = new QSpinBox;
    parameterValuesSpinBox->setRange(10, 10000000);
    parameterValuesSpinBox->setValue(logistic.parameterIntervalSize);

    centerParameterPushButton = new QPushButton("Center");

    QHBoxLayout *parameterHBoxLayout = new QHBoxLayout;
    parameterHBoxLayout->addWidget(parameterLabel);
    parameterHBoxLayout->addWidget(parameterSpinBox);
    parameterHBoxLayout->addWidget(parameterSlider);
    parameterHBoxLayout->addWidget(parameterValuesLabel);
    parameterHBoxLayout->addWidget(parameterValuesSpinBox);
    parameterHBoxLayout->addWidget(centerParameterPushButton);

    parameterSafetyFlag = false;

    // Main controls

    // Orbit controls

    QLabel *initialCondition0Label = new QLabel("Initial condition #1:");

    initialCondition0SpinBox = new QDoubleSpinBox;
    initialCondition0SpinBox->setRange(0, 1);
    initialCondition0SpinBox->setDecimals(12);
    initialCondition0SpinBox->setValue(logistic.initialCondition[0]);
    initialCondition0SpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);

    QLabel *initialCondition1Label = new QLabel("Initial condition #2:");

    initialCondition1SpinBox = new QDoubleSpinBox;
    initialCondition1SpinBox->setRange(0, 1);
    initialCondition1SpinBox->setDecimals(12);
    initialCondition1SpinBox->setValue(logistic.initialCondition[1]);
    initialCondition1SpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    initialCondition1SpinBox->setDisabled(true);

    showSecondOrbitCheckbox = new QCheckBox("Show orbit #2");
    showSecondOrbitCheckbox->setChecked(false);

    QVBoxLayout *orbitVBoxLayout = new QVBoxLayout;
    orbitVBoxLayout->addWidget(initialCondition0Label);
    orbitVBoxLayout->addWidget(initialCondition0SpinBox);
    orbitVBoxLayout->addWidget(initialCondition1Label);
    orbitVBoxLayout->addWidget(initialCondition1SpinBox);
    orbitVBoxLayout->addWidget(showSecondOrbitCheckbox);

    QGroupBox *orbitGroupBox = new QGroupBox("Orbit");
    orbitGroupBox->setLayout(orbitVBoxLayout);

    // Bifurcations controls

    QLabel *bifurcationsTransientLabel = new QLabel("Transient:");

    bifurcationsTransientSpinBox = new QSpinBox;
    bifurcationsTransientSpinBox->setRange(0, 10000000);
    bifurcationsTransientSpinBox->setValue(logistic.bifurcationsTransient);

    QLabel *bifurcationsItsLabel = new QLabel("#Iterations:");

    bifurcationsItsSpinBox = new QSpinBox;
    bifurcationsItsSpinBox->setRange(1, 10000000);
    bifurcationsItsSpinBox->setValue(logistic.bifurcationsIts);

    QVBoxLayout *bifurcationsVBoxLayout = new QVBoxLayout;
    bifurcationsVBoxLayout->addWidget(bifurcationsTransientLabel);
    bifurcationsVBoxLayout->addWidget(bifurcationsTransientSpinBox);
    bifurcationsVBoxLayout->addWidget(bifurcationsItsLabel);
    bifurcationsVBoxLayout->addWidget(bifurcationsItsSpinBox);

    QGroupBox *bifurcationsGroupBox = new QGroupBox("Bifurcations");
    bifurcationsGroupBox->setLayout(bifurcationsVBoxLayout);

    // Main controls vertical layout & widget

    QVBoxLayout *mainControlsVBoxLayout = new QVBoxLayout;
    mainControlsVBoxLayout->setAlignment(Qt::AlignTop);
    mainControlsVBoxLayout->addWidget(orbitGroupBox, 0, Qt::AlignTop);
    mainControlsVBoxLayout->addWidget(bifurcationsGroupBox, 0, Qt::AlignTop);

    QWidget *mainControlsWidget = new QWidget;
    mainControlsWidget->setLayout(mainControlsVBoxLayout);

    // Plots

    // Orbit plot

    orbitPlot = new QCustomPlot(this);

    orbitPlot->xAxis->setLabel("Iteration");
    orbitPlot->yAxis->setLabel("Xi");

    orbitPlot->yAxis->setRange(0, 1);

    orbitPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    orbitPlot->axisRect()->setupFullAxesBox(true);
    orbitPlot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    orbitPlot->axisRect()->setRangeDrag(Qt::Vertical | Qt::Horizontal);

    orbitPlot->addGraph();
    orbitPlot->graph(0)->setPen(QPen(Qt::blue));
    orbitPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    orbitPlot->addGraph();
    orbitPlot->graph(1)->setPen(QPen(Qt::red));
    orbitPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    setOrbitPlot();

    // Histogram plot

    histogramPlot = new QCustomPlot(this);

    histogramPlot->axisRect()->setupFullAxesBox(true);

    histogramPlot->xAxis->setLabel("X");
    histogramPlot->yAxis->setLabel("Histogram");

    histogram = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);

    // Bifurcations plot

    bifurcationsPlot = new QCustomPlot(this);

    bifurcationsPlot->xAxis->setLabel("Parameter");
    bifurcationsPlot->yAxis->setLabel("X(r)");

    bifurcationsPlot->xAxis->setRange(0, 4);
    bifurcationsPlot->yAxis->setRange(0, 1);

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
    bifurcationsPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    bifurcationsPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 0.3));
    bifurcationsPlot->graph(0)->setPen(QPen(Qt::white));
    bifurcationsPlot->graph(0)->setAdaptiveSampling(false);

    // Bifurcations plot cursor layer

    bifurcationsPlot->addLayer("cursor", bifurcationsPlot->layer("main"), QCustomPlot::limAbove);
    bifurcationsPlot->layer("cursor")->setMode(QCPLayer::lmBuffered);

    // Bifurcations parameter cursor

    bifurcationsLine = new QCPItemLine(bifurcationsPlot);
    bifurcationsLine->setLayer("cursor");

    bifurcationsLine->setPen(QPen(Qt::red));

    bifurcationsLine->start->setCoords(logistic.parameter, 0);
    bifurcationsLine->end->setCoords(logistic.parameter, 1);

    setBifurcationsPlot();

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

    connect(parameterSpinBox, &QDoubleSpinBox::editingFinished, this, &MainWindow::parameterChanged);
    connect(parameterSlider, &QAbstractSlider::valueChanged, this, &MainWindow::parameterIndexChanged);
    connect(parameterValuesSpinBox, &QSpinBox::editingFinished, this, &MainWindow::parameterValuesChanged);
    connect(centerParameterPushButton, &QPushButton::clicked, this, &MainWindow::centerParameter);
    connect(orbitPlot, &QCustomPlot::beforeReplot, this, &MainWindow::orbitPlotRangeChanged);
    connect(orbitPlot->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ orbitPlot->xAxis->setRange(newRange.bounded(0, logistic.orbit[0].xMax + 100)); });
    connect(orbitPlot->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ orbitPlot->yAxis->setRange(newRange.bounded(0, 1)); });
    connect(showSecondOrbitCheckbox, &QCheckBox::stateChanged, this, &MainWindow::toggleSecondOrbit);
    connect(initialCondition0SpinBox, &QDoubleSpinBox::editingFinished, this, &MainWindow::initialCondition0Changed);
    connect(initialCondition1SpinBox, &QDoubleSpinBox::editingFinished, this, &MainWindow::initialCondition1Changed);
    connect(bifurcationsPlot, &QCustomPlot::beforeReplot, this, &MainWindow::bifurcationsPlotRangeChanged);
    connect(bifurcationsPlot->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ bifurcationsPlot->xAxis->setRange(newRange.bounded(0, 4)); });
    connect(bifurcationsPlot->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ bifurcationsPlot->yAxis->setRange(newRange.bounded(0, 1)); });
    connect(bifurcationsTransientSpinBox, &QSpinBox::editingFinished, this, &MainWindow::bifurcationsTransientChanged);
    connect(bifurcationsItsSpinBox, &QSpinBox::editingFinished, this, &MainWindow::bifurcationsItsChanged);
}

MainWindow::~MainWindow()
{
}

void MainWindow::parameterChanged()
{
    logistic.parameter = parameterSpinBox->value();
    logistic.computeAll();

    setOrbitPlot();

    shiftBifurcationsLine(logistic.parameter);

    parameterSafetyFlag = true;
    parameterSlider->setValue(logistic.getParameterIndex());
}

void MainWindow::parameterIndexChanged(int i)
{
    if (!parameterSafetyFlag)
    {
        logistic.parameter = logistic.parameterInterval[i];
    }
    else
    {
        parameterSafetyFlag = false;
    }

    logistic.computeAll();

    parameterSpinBox->setValue(logistic.parameter);

    setOrbitPlot();

    shiftBifurcationsLine(logistic.parameter);
}

void MainWindow::parameterValuesChanged()
{
    logistic.parameterIntervalSize = parameterValuesSpinBox->value();

    logistic.computeParameterInterval();
    logistic.computeBifurcations();

    setBifurcationsPlot();

    parameterSafetyFlag = true;

    int index = logistic.getParameterIndex();
    logistic.parameter = logistic.parameterInterval[index];

    parameterSlider->setMaximum(logistic.parameterIntervalSize);
    parameterSlider->setValue(index);

    parameterSpinBox->setValue(logistic.parameter);
}

void MainWindow::centerParameter()
{
    logistic.centerParameter();
    logistic.computeAll();

    parameterSpinBox->setValue(logistic.parameter);
    parameterSlider->setValue(logistic.parameterIntervalSize >> 1);

    setOrbitPlot();
}

void MainWindow::setOrbitPlot()
{
    orbitPlot->graph(0)->setData(logistic.orbit[0].x, logistic.orbit[0].y, true);
    orbitPlot->graph(1)->setData(logistic.orbit[1].x, logistic.orbit[1].y, true);
    orbitPlot->xAxis->setRange(logistic.orbit[0].xMin, logistic.orbit[0].xMax);
    orbitPlot->replot();
}

void MainWindow::orbitPlotRangeChanged()
{
    QCPRange xRange = orbitPlot->xAxis->range();

    logistic.changeOrbitXRange(xRange.lower, xRange.upper);

    setOrbitPlot();
}

void MainWindow::toggleSecondOrbit(int state)
{
    if (state == Qt::Unchecked)
    {
        logistic.showSecondOrbit = false;

        orbitPlot->graph(1)->setVisible(false);
        orbitPlot->replot();

        initialCondition1SpinBox->setDisabled(true);
    }
    else if (state == Qt::Checked)
    {
        logistic.showSecondOrbit = true;
        logistic.computeOrbit(1);

        orbitPlot->graph(1)->setData(logistic.orbit[1].x, logistic.orbit[1].y, true);
        orbitPlot->graph(1)->setVisible(true);
        orbitPlot->replot();

        initialCondition1SpinBox->setDisabled(false);
    }
}

void MainWindow::initialCondition0Changed()
{
    logistic.initialCondition[0] = initialCondition0SpinBox->value();
    logistic.computeOrbit(0);
    orbitPlot->graph(0)->setData(logistic.orbit[0].x, logistic.orbit[0].y, true);
    orbitPlot->replot();
}

void MainWindow::initialCondition1Changed()
{
    logistic.initialCondition[1] = initialCondition1SpinBox->value();
    logistic.computeOrbit(1);
    orbitPlot->graph(1)->setData(logistic.orbit[1].x, logistic.orbit[1].y, true);
    orbitPlot->replot();
}

void MainWindow::setBifurcationsPlot()
{
    bifurcationsPlot->graph(0)->setData(logistic.bifurcations.x, logistic.bifurcations.y, true);
    bifurcationsPlot->xAxis->setRange(logistic.bifurcations.x.first(), logistic.bifurcations.x.last());
    bifurcationsPlot->replot();
}

void MainWindow::bifurcationsPlotRangeChanged()
{
    QCPRange xRange = bifurcationsPlot->xAxis->range();

    logistic.changeBifurcationsXRange(xRange.lower, xRange.upper);

    setBifurcationsPlot();
}

void MainWindow::bifurcationsTransientChanged()
{
    logistic.bifurcationsTransient = bifurcationsTransientSpinBox->value();
    logistic.computeBifurcations();
    setBifurcationsPlot();
}

void MainWindow::bifurcationsItsChanged()
{
    logistic.bifurcationsIts = bifurcationsItsSpinBox->value();
    logistic.computeBifurcations();
    setBifurcationsPlot();
}

void MainWindow::shiftBifurcationsLine(double value)
{
    bifurcationsLine->start->setCoords(value, 0);
    bifurcationsLine->end->setCoords(value, 1);
    bifurcationsPlot->layer("cursor")->replot();
}
