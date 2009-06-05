#!/bin/bash

sed 's/migrationRate = 0.2/migrationRate = 0.05/' ConstantsTemp.hh > Constants.hh ;
sed 's/20/05/' DoPlotTemp.R > DoPlot.R;
scons;
./camouflage 
R --batch --no-save < DoPlot.R;

sed 's/migrationRate = 0.2/migrationRate = 0.1/' ConstantsTemp.hh > Constants.hh ;
sed 's/20/10/' DoPlotTemp.R > DoPlot.R;
scons;
./camouflage 
R --batch --no-save < DoPlot.R;

sed 's/migrationRate = 0.2/migrationRate = 0.15/' ConstantsTemp.hh > Constants.hh ;
sed 's/20/15/' DoPlotTemp.R > DoPlot.R;
scons;
./camouflage 
R --batch --no-save < DoPlot.R;

sed 's/migrationRate = 0.2/migrationRate = 0.2/' ConstantsTemp.hh > Constants.hh ;
sed 's/20/20/' DoPlotTemp.R > DoPlot.R;
scons;
./camouflage 
R --batch --no-save < DoPlot.R;

sed 's/migrationRate = 0.2/migrationRate = 0.25/' ConstantsTemp.hh > Constants.hh ;
sed 's/20/25/' DoPlotTemp.R > DoPlot.R;
scons;
./camouflage 
R --batch --no-save < DoPlot.R;

sed 's/migrationRate = 0.2/migrationRate = 0.3/' ConstantsTemp.hh > Constants.hh ;
sed 's/20/30/' DoPlotTemp.R > DoPlot.R;
scons;
./camouflage 
R --batch --no-save < DoPlot.R;

sed 's/migrationRate = 0.2/migrationRate = 0.5/' ConstantsTemp.hh > Constants.hh ;
sed 's/20/50/' DoPlotTemp.R > DoPlot.R;
scons;
./camouflage 
R --batch --no-save < DoPlot.R;

