function [STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray] = getArraysFromFiles(nbIterations)
% -----------------------------------
% VARIABLES
% fileNameNumVal = 3;

% -----------------------------------
% getting the wanted arrays from the files
fileExtension = '.dat';
dataFolder = 'data';

StochasticFileName = strcat('STOCHASTIC_dif_at_it_', ...
    int2str(nbIterations),'(correctMean)',fileExtension);
StochStdUpFileName = strcat('STOCHASTIC_dif_at_it_', ...
    int2str(nbIterations),'(deviationUp)',fileExtension);
StochStdDownFileName = strcat('STOCHASTIC_dif_at_it_', ...
    int2str(nbIterations),'(deviationDown)',fileExtension);
RNDNFileName = strcat('RNDN_dif_at_it_',int2str(nbIterations),fileExtension);

delimiterInS = ',';
delimiterInR = '\t';
headerlinesIn = 0;

STOCHASTICArray = importdata(strcat(dataFolder,'/',StochasticFileName), ...
    delimiterInS,headerlinesIn);
RNDNArray = importdata(strcat(dataFolder,'/',RNDNFileName), ...
    delimiterInR,headerlinesIn);
StochStdUpArray = importdata(strcat(dataFolder,'/',StochStdUpFileName), ...
    delimiterInS,headerlinesIn);
StochStdDownArray = importdata(strcat(dataFolder,'/',StochStdDownFileName), ...
    delimiterInS,headerlinesIn);

clear dataFolder delimiterInR delimiterInS fileExtension ... % fileNameNumVal ...
    headerlinesIn;

end