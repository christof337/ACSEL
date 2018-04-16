function [STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, RNDZArray, RNDUArray] = getRelArraysFromAllRMFiles(nbIterations)
% -----------------------------------
% VARIABLES
% fileNameNumVal = 3;

% -----------------------------------
% getting the wanted arrays from the files
fileExtension = '.dat';
dataFolder = 'data';

StochasticFileName = strcat('STOCHASTIC_rel_dif_at_it_', ...
    int2str(nbIterations),'(correctMean)',fileExtension);
StochStdUpFileName = strcat('STOCHASTIC_rel_dif_at_it_', ...
    int2str(nbIterations),'(deviationUp)',fileExtension);
StochStdDownFileName = strcat('STOCHASTIC_rel_dif_at_it_', ...
    int2str(nbIterations),'(deviationDown)',fileExtension);
strSuffix = '_rel_dif_at_it_';
RNDNFileName = strcat('RNDN',strSuffix,int2str(nbIterations),fileExtension);
RNDAFileName = strcat('RNDA',strSuffix,int2str(nbIterations),fileExtension);
RNDDFileName = strcat('RNDD',strSuffix,int2str(nbIterations),fileExtension);
RNDZFileName = strcat('RNDZ',strSuffix,int2str(nbIterations),fileExtension);
RNDUFileName = strcat('RNDZ',strSuffix,int2str(nbIterations),fileExtension);

delimiterInS = ',';
delimiterInR = '\t';
headerlinesIn = 0;

STOCHASTICArray = importdata(strcat(dataFolder,'/',StochasticFileName), ...
    delimiterInS,headerlinesIn);
StochStdUpArray = importdata(strcat(dataFolder,'/',StochStdUpFileName), ...
    delimiterInS,headerlinesIn);
StochStdDownArray = importdata(strcat(dataFolder,'/',StochStdDownFileName), ...
    delimiterInS,headerlinesIn);
RNDNArray = importdata(strcat(dataFolder,'/',RNDNFileName), ...
    delimiterInR,headerlinesIn);
RNDAArray = importdata(strcat(dataFolder,'/',RNDAFileName), ...
    delimiterInR,headerlinesIn);
RNDDArray = importdata(strcat(dataFolder,'/',RNDDFileName), ...
    delimiterInR,headerlinesIn);
RNDZArray = importdata(strcat(dataFolder,'/',RNDZFileName), ...
    delimiterInR,headerlinesIn);
RNDUArray = importdata(strcat(dataFolder,'/',RNDUFileName), ...
    delimiterInR,headerlinesIn);

clear dataFolder delimiterInR delimiterInS fileExtension ... % fileNameNumVal ...
    headerlinesIn;

end