function [STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, ...
	RNDZArray, RNDUArray, CADNAArray] = getRelArraysFromAllRMFiles(val, suffix)
% -----------------------------------
% VARIABLES


% -----------------------------------
% getting the wanted arrays from the files
fileExtension = '.dat';
dataFolder = 'data';

strSuffix = strcat('_rel_dif_',suffix,'_');
StochasticFileName = strcat('STOCHASTIC',strSuffix, ...
    int2str(val),'(mean)',fileExtension);
StochStdUpFileName = strcat('STOCHASTIC',strSuffix, ...
    int2str(val),'(deviationUp)',fileExtension);
StochStdDownFileName = strcat('STOCHASTIC',strSuffix, ...
    int2str(val),'(deviationDown)',fileExtension);
RNDNFileName = strcat('RNDN',strSuffix,int2str(val),fileExtension);
RNDAFileName = strcat('RNDA',strSuffix,int2str(val),fileExtension);
RNDDFileName = strcat('RNDD',strSuffix,int2str(val),fileExtension);
RNDZFileName = strcat('RNDZ',strSuffix,int2str(val),fileExtension);
RNDUFileName = strcat('RNDZ',strSuffix,int2str(val),fileExtension);
CadnaFileName = strcat('CADNA',strSuffix,int2str(val),fileExtension);

delimiterInS = ',';
delimiterInR = '/t';
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
CADNAArray = importdata(strcat(dataFolder,'/',CadnaFileName), ...
    delimiterInR,headerlinesIn);

clear dataFolder delimiterInR delimiterInS fileExtension ... % fileNameNumVal ...
    headerlinesIn;

end