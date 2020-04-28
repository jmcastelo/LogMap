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
    parameterSpinBox->setMaximumWidth(110);

    parameterSlider = new QSlider(Qt::Horizontal);
    parameterSlider->setMinimum(0);
    parameterSlider->setMaximum(logistic.parameterIntervalSize);
    parameterSlider->setValue(logistic.getParameterIndex());

    QLabel *parameterValuesLabel = new QLabel("#Values");

    parameterValuesSpinBox = new QSpinBox;
    parameterValuesSpinBox->setRange(10, 10000000);
    parameterValuesSpinBox->setValue(logistic.parameterIntervalSize);
    parameterValuesSpinBox->setMaximumWidth(110);

    centerParameterPushButton = new QPushButton("Center");

    resetPushButton = new QPushButton("Reset");

    QHBoxLayout *parameterHBoxLayout = new QHBoxLayout;
    parameterHBoxLayout->addWidget(parameterLabel);
    parameterHBoxLayout->addWidget(parameterSpinBox);
    parameterHBoxLayout->addWidget(parameterSlider);
    parameterHBoxLayout->addWidget(parameterValuesLabel);
    parameterHBoxLayout->addWidget(parameterValuesSpinBox);
    parameterHBoxLayout->addWidget(centerParameterPushButton);
    parameterHBoxLayout->addWidget(resetPushButton);

    parameterSafetyFlag = false;

    // Main controls

    // Orbit controls

    QLabel *initialCondition0Label = new QLabel("Initial condition #1");

    initialCondition0SpinBox = new QDoubleSpinBox;
    initialCondition0SpinBox->setRange(0, 1);
    initialCondition0SpinBox->setDecimals(12);
    initialCondition0SpinBox->setValue(logistic.initialCondition[0]);
    initialCondition0SpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    initialCondition0SpinBox->setMaximumWidth(110);

    QLabel *initialCondition1Label = new QLabel("Initial condition #2");

    initialCondition1SpinBox = new QDoubleSpinBox;
    initialCondition1SpinBox->setRange(0, 1);
    initialCondition1SpinBox->setDecimals(12);
    initialCondition1SpinBox->setValue(logistic.initialCondition[1]);
    initialCondition1SpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
    initialCondition1SpinBox->setDisabled(true);
    initialCondition1SpinBox->setMaximumWidth(110);

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

    QLabel *bifurcationsTransientLabel = new QLabel("Transient");

    bifurcationsTransientSpinBox = new QSpinBox;
    bifurcationsTransientSpinBox->setRange(0, 10000000);
    bifurcationsTransientSpinBox->setValue(logistic.bifurcationsTransient);
    bifurcationsTransientSpinBox->setMaximumWidth(110);

    QLabel *bifurcationsItsLabel = new QLabel("#Iterations");

    bifurcationsItsSpinBox = new QSpinBox;
    bifurcationsItsSpinBox->setRange(1, 10000000);
    bifurcationsItsSpinBox->setValue(logistic.bifurcationsIts);
    bifurcationsItsSpinBox->setMaximumWidth(110);

    QVBoxLayout *bifurcationsVBoxLayout = new QVBoxLayout;
    bifurcationsVBoxLayout->addWidget(bifurcationsTransientLabel);
    bifurcationsVBoxLayout->addWidget(bifurcationsTransientSpinBox);
    bifurcationsVBoxLayout->addWidget(bifurcationsItsLabel);
    bifurcationsVBoxLayout->addWidget(bifurcationsItsSpinBox);

    QGroupBox *bifurcationsGroupBox = new QGroupBox("Bifurcations");
    bifurcationsGroupBox->setLayout(bifurcationsVBoxLayout);

    // Histogram controls

    QLabel *histogramTransientLabel = new QLabel("Transient");

    histogramTransientSpinBox = new QSpinBox;
    histogramTransientSpinBox->setRange(0, 10000000);
    histogramTransientSpinBox->setValue(logistic.histogramTransient);
    histogramTransientSpinBox->setMaximumWidth(110);

    QLabel *histogramItsLabel = new QLabel("#Iterations");

    histogramItsSpinBox = new QSpinBox;

    histogramItsSpinBox->setRange(1, 10000000);
    histogramItsSpinBox->setValue(logistic.histogramIts);
    histogramItsSpinBox->setMaximumWidth(110);

    QLabel *histogramBinsLabel = new QLabel("#Bins");

    histogramBinsSpinBox = new QSpinBox;
    histogramBinsSpinBox->setRange(1, 1000000);
    histogramBinsSpinBox->setValue(logistic.histogramBins);
    histogramBinsSpinBox->setMaximumWidth(110);

    QVBoxLayout *histogramVBoxLayout = new QVBoxLayout;
    histogramVBoxLayout->addWidget(histogramTransientLabel);
    histogramVBoxLayout->addWidget(histogramTransientSpinBox);
    histogramVBoxLayout->addWidget(histogramItsLabel);
    histogramVBoxLayout->addWidget(histogramItsSpinBox);
    histogramVBoxLayout->addWidget(histogramBinsLabel);
    histogramVBoxLayout->addWidget(histogramBinsSpinBox);

    QGroupBox *histogramGroupBox = new QGroupBox("Invariant density");
    histogramGroupBox->setLayout(histogramVBoxLayout);

    // Lyapunov controls

    lyapunovExponentLabel = new QLabel;
    setLyapunovExponentLabel(logistic.getParameterIndex());

    QLabel *lyapunovTransientLabel = new QLabel("Transient");

    lyapunovTransientSpinBox = new QSpinBox;
    lyapunovTransientSpinBox->setRange(0, 10000000);
    lyapunovTransientSpinBox->setValue(logistic.lyapunovTransient);
    lyapunovTransientSpinBox->setMaximumWidth(110);

    QLabel *lyapunovItsLabel = new QLabel("#Iterations");

    lyapunovItsSpinBox = new QSpinBox;
    lyapunovItsSpinBox->setRange(1, 10000000);
    lyapunovItsSpinBox->setValue(logistic.lyapunovIts);
    lyapunovItsSpinBox->setMaximumWidth(110);

    QVBoxLayout *lyapunovVBoxLayout = new QVBoxLayout;
    lyapunovVBoxLayout->addWidget(lyapunovExponentLabel);
    lyapunovVBoxLayout->addWidget(lyapunovTransientLabel);
    lyapunovVBoxLayout->addWidget(lyapunovTransientSpinBox);
    lyapunovVBoxLayout->addWidget(lyapunovItsLabel);
    lyapunovVBoxLayout->addWidget(lyapunovItsSpinBox);

    QGroupBox *lyapunovGroupBox = new QGroupBox("Lyapunov exponent");
    lyapunovGroupBox->setLayout(lyapunovVBoxLayout);

    // Main controls vertical layout & widget

    QVBoxLayout *mainControlsVBoxLayout = new QVBoxLayout;
    mainControlsVBoxLayout->setAlignment(Qt::AlignTop);
    mainControlsVBoxLayout->addWidget(orbitGroupBox, 0, Qt::AlignTop);
    mainControlsVBoxLayout->addWidget(bifurcationsGroupBox, 0, Qt::AlignTop);
    mainControlsVBoxLayout->addWidget(histogramGroupBox, 0, Qt::AlignTop);
    mainControlsVBoxLayout->addWidget(lyapunovGroupBox, 0, Qt::AlignTop);

    QWidget *mainControlsWidget = new QWidget;
    mainControlsWidget->setLayout(mainControlsVBoxLayout);

    // Plots

    // Orbit plot

    orbitPlot = new QCustomPlot(this);

    orbitPlot->xAxis->setLabel("Iteration");
    orbitPlot->yAxis->setLabel("X(i)");

    orbitPlot->xAxis->setRange(logistic.orbit[0].xMin, logistic.orbit[0].xMax);
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
    histogramPlot->yAxis->setLabel("Invariant density");

    histogramPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    histogramPlot->axisRect()->setupFullAxesBox();
    histogramPlot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    histogramPlot->axisRect()->setRangeDrag(Qt::Vertical | Qt::Horizontal);

    histogram = new QCPBars(histogramPlot->xAxis, histogramPlot->yAxis);
    histogram->setWidth(1.0 / logistic.histogramBins);

    setHistogramPlot();

    // Bifurcations plot

    bifurcationsPlot = new QCustomPlot(this);

    bifurcationsPlot->xAxis->setLabel("Parameter");
    bifurcationsPlot->yAxis->setLabel("X(r)");

    bifurcationsPlot->xAxis->setRange(1, 4);
    bifurcationsPlot->yAxis->setRange(0, 1);

    bifurcationsPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    bifurcationsPlot->axisRect()->setupFullAxesBox(true);
    bifurcationsPlot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    bifurcationsPlot->axisRect()->setRangeDrag(Qt::Vertical | Qt::Horizontal);

    bifurcationsPlot->addGraph();
    bifurcationsPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    bifurcationsPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 0.1));
    bifurcationsPlot->graph(0)->setPen(QPen(Qt::black));
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

    lyapunovPlot->xAxis->setRange(1, 4);
    lyapunovPlot->yAxis->setRange(-1, 1);

    lyapunovPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

    lyapunovPlot->axisRect()->setupFullAxesBox(true);
    lyapunovPlot->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);
    lyapunovPlot->axisRect()->setRangeDrag(Qt::Vertical | Qt::Horizontal);

    lyapunovPlot->addGraph();
    lyapunovPlot->graph(0)->setPen(QPen(Qt::black));

    // Lyapunov plot cursor layer

    lyapunovPlot->addLayer("cursor", lyapunovPlot->layer("main"), QCustomPlot::limAbove);
    lyapunovPlot->layer("cursor")->setMode(QCPLayer::lmBuffered);

    // Lyapunov parameter cursor

    lyapunovLine = new QCPItemLine(lyapunovPlot);
    lyapunovLine->setLayer("cursor");

    lyapunovLine->setPen(QPen(Qt::red));

    lyapunovLine->start->setCoords(logistic.parameter, -100);
    lyapunovLine->end->setCoords(logistic.parameter, 100);

    setLyapunovPlot();

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

    // Main grid layout

    QGridLayout *mainGridLayout = new QGridLayout;
    mainGridLayout->addWidget(mainControlsWidget, 0, 0, Qt::AlignLeft);
    mainGridLayout->addWidget(splittersSplitter, 0 ,1);

    // Main vertical layout

    QVBoxLayout *mainVBoxLayout = new QVBoxLayout;

    mainVBoxLayout->addLayout(parameterHBoxLayout);
    mainVBoxLayout->addLayout(mainGridLayout);

    setLayout(mainVBoxLayout);

    setWindowTitle("LogMap");

    resize(1200, 800);

    bifurcationsPlotMousePressed = false;
    lyapunovPlotMousePressed = false;

    settingBifurcationsPlotXRange = false;
    settingLyapunovPlotXRange = false;

    // Signals + Slots

    connect(parameterSpinBox, &QDoubleSpinBox::editingFinished, this, &MainWindow::parameterChanged);
    connect(parameterSlider, &QAbstractSlider::valueChanged, this, &MainWindow::parameterIndexChanged);
    connect(parameterValuesSpinBox, &QSpinBox::editingFinished, this, &MainWindow::parameterValuesChanged);
    connect(centerParameterPushButton, &QPushButton::clicked, this, &MainWindow::centerParameter);
    connect(resetPushButton, &QPushButton::clicked, this, &MainWindow::reset);
    connect(orbitPlot->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ onOrbitPlotXRangeChanged(newRange); });
    connect(orbitPlot->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ orbitPlot->yAxis->setRange(newRange.bounded(0, 1)); });
    connect(showSecondOrbitCheckbox, &QCheckBox::stateChanged, this, &MainWindow::toggleSecondOrbit);
    connect(initialCondition0SpinBox, &QDoubleSpinBox::editingFinished, this, &MainWindow::initialCondition0Changed);
    connect(initialCondition1SpinBox, &QDoubleSpinBox::editingFinished, this, &MainWindow::initialCondition1Changed);
    connect(bifurcationsPlot, &QCustomPlot::mousePress, [this](const QMouseEvent *event){ Q_UNUSED(event) bifurcationsPlotMousePressed = true; });
    connect(bifurcationsPlot, &QCustomPlot::mouseRelease, this, &MainWindow::onBifurcationsPlotMouseRelease);
    connect(bifurcationsPlot->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ onBifurcationsPlotXRangeChanged(newRange); });
    connect(bifurcationsPlot->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ onBifurcationsPlotYRangeChanged(newRange); });
    connect(bifurcationsTransientSpinBox, &QSpinBox::editingFinished, this, &MainWindow::bifurcationsTransientChanged);
    connect(bifurcationsItsSpinBox, &QSpinBox::editingFinished, this, &MainWindow::bifurcationsItsChanged);
    connect(histogramPlot->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ histogramPlot->xAxis->setRange(newRange.bounded(0, 1)); });
    connect(histogramPlot->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ histogramPlot->yAxis->setRange(newRange.bounded(0, 1)); });
    connect(histogramTransientSpinBox, &QSpinBox::editingFinished, this, &MainWindow::histogramTransientChanged);
    connect(histogramItsSpinBox, &QSpinBox::editingFinished, this, &MainWindow::histogramItsChanged);
    connect(histogramBinsSpinBox, &QSpinBox::editingFinished, this, &MainWindow::histogramBinsChanged);
    connect(lyapunovPlot, &QCustomPlot::mousePress, [this](const QMouseEvent *event){ Q_UNUSED(event) lyapunovPlotMousePressed = true; });
    connect(lyapunovPlot, &QCustomPlot::mouseRelease, this, &MainWindow::onLyapunovPlotMouseRelease);
    connect(lyapunovPlot->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), [this](const QCPRange &newRange){ onLyapunovPlotXRangeChanged(newRange); });
    connect(lyapunovTransientSpinBox, &QSpinBox::editingFinished, this, &MainWindow::lyapunovTransientChanged);
    connect(lyapunovItsSpinBox, &QSpinBox::editingFinished, this, &MainWindow::lyapunovItsChanged);
}

MainWindow::~MainWindow()
{
}

void MainWindow::parameterChanged()
{
    logistic.parameter = parameterSpinBox->value();
    logistic.computeAll();

    setOrbitPlot();
    setHistogramPlot();

    shiftBifurcationsLine(logistic.parameter);
    shiftLyapunovLine(logistic.parameter);

    parameterSafetyFlag = true;

    int index = logistic.getParameterIndex();

    parameterSlider->setValue(index);

    setLyapunovExponentLabel(index);
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
    setHistogramPlot();

    shiftBifurcationsLine(logistic.parameter);
    shiftLyapunovLine(logistic.parameter);

    setLyapunovExponentLabel(i);
}

void MainWindow::parameterValuesChanged()
{
    logistic.parameterIntervalSize = parameterValuesSpinBox->value();

    logistic.computeParameterInterval();
    logistic.computeBifurcations();
    logistic.computeLyapunov();

    setBifurcationsPlot();
    setLyapunovPlot();

    parameterSafetyFlag = true;

    int index = logistic.getParameterIndex();

    logistic.parameter = logistic.parameterInterval[index];

    parameterSlider->setMaximum(logistic.parameterIntervalSize);
    parameterSlider->setValue(index);

    parameterSpinBox->setValue(logistic.parameter);

    setLyapunovExponentLabel(index);
}

void MainWindow::centerParameter()
{
    logistic.centerParameter();
    logistic.computeAll();

    parameterSpinBox->setValue(logistic.parameter);
    parameterSlider->setValue(logistic.parameterIntervalSize >> 1);

    setOrbitPlot();
}

void MainWindow::reset()
{
    logistic.reset();

    bifurcationsPlot->xAxis->setRange(1, 4);
    bifurcationsPlot->yAxis->setRange(0, 1);

    lyapunovPlot->xAxis->setRange(1, 4);
    lyapunovPlot->yAxis->setRange(-1, 1);

    setBifurcationsPlot();
    setLyapunovPlot();

}

void MainWindow::setOrbitPlot()
{
    orbitPlot->graph(0)->setData(logistic.orbit[0].x, logistic.orbit[0].y, true);
    orbitPlot->graph(1)->setData(logistic.orbit[1].x, logistic.orbit[1].y, true);
    orbitPlot->replot();
}

void MainWindow::onOrbitPlotXRangeChanged(QCPRange newRange)
{
    orbitPlot->xAxis->setRange(newRange.bounded(0, logistic.orbit[0].xMax + 100));

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
    bifurcationsPlot->replot();
}

void MainWindow::onBifurcationsPlotMouseRelease()
{
    settingBifurcationsPlotXRange = true;

    QCPRange xRange = bifurcationsPlot->xAxis->range();
    QCPRange yRange = bifurcationsPlot->yAxis->range();

    logistic.changeBifurcationsRange(xRange.lower, xRange.upper, yRange.lower, yRange.upper);
    bifurcationsPlot->graph(0)->setData(logistic.bifurcations.x, logistic.bifurcations.y, true);
    bifurcationsPlot->replot();

    logistic.changeLyapunovXRange(xRange.lower, xRange.upper);
    lyapunovPlot->graph(0)->setData(logistic.lyapunov.x, logistic.lyapunov.y, true);
    lyapunovPlot->xAxis->setRange(xRange.lower, xRange.upper);
    lyapunovPlot->replot();

    bifurcationsPlotMousePressed = false;
}

void MainWindow::onBifurcationsPlotXRangeChanged(QCPRange newRange)
{
    bifurcationsPlot->xAxis->setRange(newRange.bounded(0, 4));

    if (!bifurcationsPlotMousePressed && !settingLyapunovPlotXRange)
    {
        settingBifurcationsPlotXRange = true;

        QCPRange xRange = bifurcationsPlot->xAxis->range();
        QCPRange yRange = bifurcationsPlot->yAxis->range();

        logistic.changeBifurcationsRange(xRange.lower, xRange.upper, yRange.lower, yRange.upper);
        bifurcationsPlot->graph(0)->setData(logistic.bifurcations.x, logistic.bifurcations.y, true);

        logistic.changeLyapunovXRange(xRange.lower, xRange.upper);
        lyapunovPlot->graph(0)->setData(logistic.lyapunov.x, logistic.lyapunov.y, true);
        lyapunovPlot->xAxis->setRange(xRange.lower, xRange.upper);
        lyapunovPlot->replot();
    }

    settingLyapunovPlotXRange = false;
}

void MainWindow::onBifurcationsPlotYRangeChanged(QCPRange newRange)
{
    bifurcationsPlot->yAxis->setRange(newRange.bounded(0, 1));

    if (!bifurcationsPlotMousePressed)
    {
        QCPRange xRange = bifurcationsPlot->xAxis->range();

        logistic.changeBifurcationsRange(xRange.lower, xRange.upper, newRange.lower, newRange.upper);

        bifurcationsPlot->graph(0)->setData(logistic.bifurcations.x, logistic.bifurcations.y, true);
    }
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

void MainWindow::setHistogramPlot()
{
    histogram->setData(logistic.histogram.x, logistic.histogram.y);
    histogram->setWidth(1.0 / logistic.histogramBins);
    histogramPlot->replot();
    histogramPlot->rescaleAxes();
}

void MainWindow::histogramTransientChanged()
{
    logistic.histogramTransient = histogramTransientSpinBox->value();
    logistic.computeHistogram();
    setHistogramPlot();
}

void MainWindow::histogramItsChanged()
{
    logistic.histogramIts = histogramItsSpinBox->value();
    logistic.computeHistogram();
    setHistogramPlot();
}

void MainWindow::histogramBinsChanged()
{
    logistic.histogramBins = histogramBinsSpinBox->value();
    logistic.computeHistogram();
    setHistogramPlot();
}

void MainWindow::setLyapunovPlot()
{
    lyapunovPlot->graph(0)->setData(logistic.lyapunov.x, logistic.lyapunov.y, true);
    lyapunovPlot->replot();
}

void MainWindow::onLyapunovPlotMouseRelease()
{
    settingLyapunovPlotXRange = true;

    QCPRange xRange = lyapunovPlot->xAxis->range();

    logistic.changeBifurcationsRange(xRange.lower, xRange.upper, logistic.bifurcations.yMin, logistic.bifurcations.yMax);
    bifurcationsPlot->graph(0)->setData(logistic.bifurcations.x, logistic.bifurcations.y, true);
    bifurcationsPlot->xAxis->setRange(xRange.lower, xRange.upper);
    bifurcationsPlot->replot();

    logistic.changeLyapunovXRange(xRange.lower, xRange.upper);
    lyapunovPlot->graph(0)->setData(logistic.lyapunov.x, logistic.lyapunov.y, true);
    lyapunovPlot->replot();

    lyapunovPlotMousePressed = false;
}

void MainWindow::onLyapunovPlotXRangeChanged(QCPRange newRange)
{
    lyapunovPlot->xAxis->setRange(newRange.bounded(0, 4));

    if (!lyapunovPlotMousePressed && !settingBifurcationsPlotXRange)
    {
        settingLyapunovPlotXRange = true;

        QCPRange xRange = lyapunovPlot->xAxis->range();

        logistic.changeBifurcationsRange(xRange.lower, xRange.upper, logistic.bifurcations.yMin, logistic.bifurcations.yMax);
        bifurcationsPlot->graph(0)->setData(logistic.bifurcations.x, logistic.bifurcations.y, true);
        bifurcationsPlot->xAxis->setRange(xRange.lower, xRange.upper);
        bifurcationsPlot->replot();

        logistic.changeLyapunovXRange(xRange.lower, xRange.upper);
        lyapunovPlot->graph(0)->setData(logistic.lyapunov.x, logistic.lyapunov.y, true);
    }

    settingBifurcationsPlotXRange = false;
}

void MainWindow::shiftLyapunovLine(double value)
{
    lyapunovLine->start->setCoords(value, -100);
    lyapunovLine->end->setCoords(value, 100);
    lyapunovPlot->layer("cursor")->replot();
}

void MainWindow::setLyapunovExponentLabel(int i)
{
    lyapunovExponentLabel->setText(QString("%1").arg(logistic.lyapunov.y[i]));
}

void MainWindow::lyapunovTransientChanged()
{
    logistic.lyapunovTransient = lyapunovTransientSpinBox->value();
    logistic.computeLyapunov();
    setLyapunovPlot();
}

void MainWindow::lyapunovItsChanged()
{
    logistic.lyapunovIts = lyapunovItsSpinBox->value();
    logistic.computeLyapunov();
    setLyapunovPlot();
}
