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

#include "logistic.h"

Logistic::Logistic(QObject *parent) : QObject(parent)
{
    // Parameter setup

    parameterMin = 1;
    parameterMax = 4;

    parameterIntervalSize = 500;

    computeParameterInterval();

    parameter = 3.56;
    parameter = parameterInterval[getParameterIndex()];

    // Orbit setup

    initialCondition[0] = 0.6;
    initialCondition[1] = 0.61;

    orbit[0].xMin = 600;
    orbit[0].xMax = 700;

    orbit[1].xMin = 600;
    orbit[1].xMax = 700;

    computeOrbit(0);

    showSecondOrbit = false;

    // Bifurcations setup

    bifurcations.xMin = 1;
    bifurcations.xMax = 4;

    bifurcationsTransient = 600;
    bifurcationsIts = 1000;

    computeBifurcations();

    // Histogram setup

    histogramBins = 100;
    histogramTransient = 600;
    histogramIts = 100000;

    computeHistogram();
}

void Logistic::computeParameterInterval()
{
    parameterInterval.clear();

    for (int i = 0; i <= parameterIntervalSize; i++)
    {
        double r = parameterMin + (parameterMax - parameterMin) * i / parameterIntervalSize;
        parameterInterval.push_back(r);
    }
}

void Logistic::centerParameter()
{
    parameterMin = bifurcations.xMin;
    parameterMax = bifurcations.xMax;

    computeParameterInterval();

    parameter = parameterInterval[parameterIntervalSize >> 1];
}

int Logistic::getParameterIndex()
{
    int index = 0;
    double distanceMin = 100.0;

   for (int i = 0; i <= parameterIntervalSize; i++)
   {
       double distance = fabs(parameter - parameterInterval[i]);
       if (distance < distanceMin)
       {
           index = i;
           distanceMin = distance;
       }
   }

   return index;
}

void Logistic::computeOrbit(int n)
{
    orbit[n].x.clear();
    orbit[n].y.clear();

    double y = initialCondition[n];

    for (int it = 0; it <= orbit[n].xMax; it++)
    {
        if (it >= orbit[n].xMin)
        {
            orbit[n].x.push_back(it);
            orbit[n].y.push_back(y);
        }

        y = parameter * y * (1.0 - y);
    }
}

void Logistic::changeOrbitXRange(double lower, double upper)
{
    orbit[0].xMin = lower;
    orbit[0].xMax = upper;

    computeOrbit(0);

    orbit[1].xMin = lower;
    orbit[1].xMax = upper;

    if (showSecondOrbit)
    {
        computeOrbit(1);
    }
}

void Logistic::computeBifurcations()
{
    bifurcations.x.clear();
    bifurcations.y.clear();

    for (int i = 0; i <= parameterIntervalSize; i++)
    {
        double r = bifurcations.xMin + (bifurcations.xMax - bifurcations.xMin) * i / parameterIntervalSize;
        double y = 1.0 / sqrt(7.0);

        for (int it = 0; it < bifurcationsTransient; it++)
        {
            y = r * y * (1.0 - y);
        }

        for (int it = 0; it < bifurcationsIts; it++)
        {
            y = r * y * (1.0 - y);

            bifurcations.x.push_back(r);
            bifurcations.y.push_back(y);
        }
    }
}

void Logistic::changeBifurcationsXRange(double lower, double upper)
{
    bifurcations.xMin = lower;
    bifurcations.xMax = upper;

    computeBifurcations();
}

void Logistic::computeHistogram()
{
    histogram.x.clear();
    histogram.y.clear();

    histogram.x.reserve(histogramBins);
    histogram.y.reserve(histogramBins);

    for (int i = 0; i < histogramBins; i++)
    {
        histogram.x.push_back((i + 0.5) / histogramBins);
        histogram.y.push_back(0);
    }

    double x = 1.0 / sqrt(7.0);

    for (int it = 0; it < histogramTransient; it++)
    {
        x = parameter * x * (1.0 - x);
    }

    for (int it = 0; it < histogramIts; it++)
    {
        x = parameter * x * (1.0 - x);

        histogram.y[static_cast<int>(floor(x * histogramBins))]++;
    }

    for (int i = 0; i < histogramBins; i++)
    {
        histogram.y[i] /= histogramIts;
    }
}

void Logistic::computeAll()
{
    computeOrbit(0);

    if (showSecondOrbit)
    {
        computeOrbit(1);
    }

    computeHistogram();
}
