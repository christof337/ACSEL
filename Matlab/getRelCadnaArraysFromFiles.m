function [STOCHASTICArray, RNDNArray] = getRelCadnaArraysFromFiles(nbIterations)
% -----------------------------------
% VARIABLES
% fileNameNumVal = 3;

% -----------------------------------
% getting the wanted arrays from the files
fileExtension = '.dat';
dataFolder = 'data';

StochasticFileName = strcat('STOCHASTIC_CADNA_rel_dif_at_it_', ...
    int2str(nbIterations),'(correctMean)',fileExtension);
RNDNFileName = strcat('RNDN_rel_dif_at_it_',int2str(nbIterations),fileExtension);

delimiterInS = ',';
delimiterInR = '\t';
headerlinesIn = 0;

STOCHASTICArray = importdata(strcat(dataFolder,'/',StochasticFileName), ...
    delimiterInS,headerlinesIn);
RNDNArray = importdata(strcat(dataFolder,'/',RNDNFileName), ...
    delimiterInR,headerlinesIn);

clear dataFolder delimiterInR delimiterInS fileExtension ... % fileNameNumVal ...
    headerlinesIn;

end