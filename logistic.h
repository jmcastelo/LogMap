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
#include <QVector>

struct Data
{
    QVector<double> x, y;
    double xMin, xMax;
    double yMin, yMax;
};

class Logistic
{
public:
    Data orbit[2], bifurcations, lyapunov, histogram;

    double initialCondition[2];

    double parameter, parameterMin, parameterMax;
    QVector<double> parameterInterval;
    int parameterIntervalSize;

    int bifurcationsTransient, bifurcationsIts;
    int lyapunovTransient, lyapunovIts;
    int histogramBins, histogramTransient, histogramIts;

    bool showSecondOrbit;

    Logistic();

    void computeParameterInterval();
    void centerParameter();
    int getParameterIndex();

    void computeOrbit(int n);
    void changeOrbitXRange(double lower, double upper);

    void computeBifurcations();
    void changeBifurcationsRange(double xLower, double xUpper, double yLower, double yUpper);

    void computeHistogram();
    void changeLyapunovXRange(double lower, double upper);

    void computeLyapunov();

    void computeAll();

    void reset();
};

#endif // LOGISTIC_H
