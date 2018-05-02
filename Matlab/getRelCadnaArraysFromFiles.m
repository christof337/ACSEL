function [CADNAArray, RNDNArray] = getRelCadnaArraysFromFiles(nbIterations, isRelDiff)
% -----------------------------------
% VARIABLES
% fileNameNumVal = 3;

% -----------------------------------
% getting the wanted arrays from the files
fileExtension = '.dat';
dataFolder = 'data';

if (isRelDiff)
    comparatorStr = 'relDist';
else
    comparatorStr = 'Kullback';
end
    
CadnaFileName = strcat('CADNA_',comparatorStr,'_at_it_', ...
    int2str(nbIterations),fileExtension);
RNDNFileName = strcat('RNDN_',comparatorStr,'_at_it_',int2str(nbIterations),fileExtension);

delimiterInS = ',';
delimiterInR = '\t';
headerlinesIn = 0;

CADNAArray = importdata(strcat(dataFolder,'/',CadnaFileName), ...
    delimiterInS,headerlinesIn);
RNDNArray = importdata(strcat(dataFolder,'/',RNDNFileName), ...
    delimiterInR,headerlinesIn);

clear dataFolder delimiterInR delimiterInS fileExtension ... % fileNameNumVal ...
    headerlinesIn CadnaFileName RNDNFileName comparatorStr;

end