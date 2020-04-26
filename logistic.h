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

#ifndef LOGISTIC_H
#define LOGISTIC_H

#include <math.h>
#include <QObject>
#include <QVector>

struct Data
{
    QVector<double> x, y;
    double xMin, xMax;
};

class Logistic : public QObject
{
    Q_OBJECT

public:
    Data orbit[2], bifurcations, lyapunov, histogram;

    double initialCondition[2];

    double parameter, parameterMin, parameterMax;
    QVector<double> parameterInterval;
    int parameterIntervalSize;

    int bifurcationsTransient, bifurcationsIts;
    int lyapunovIts;
    int histogramBins, histogramTransient, histogramIts;

    bool showSecondOrbit;

    Logistic(QObject *parent = nullptr);

    void computeParameterInterval();
    void centerParameter();
    int getParameterIndex();

    void computeOrbit(int n);
    void changeOrbitXRange(double lower, double upper);

    void computeBifurcations();
    void changeBifurcationsXRange(double lower, double upper);

    void computeHistogram();

    void computeAll();
};

#endif // LOGISTIC_H
