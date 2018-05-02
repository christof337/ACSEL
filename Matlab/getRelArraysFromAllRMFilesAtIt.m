function [STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, ...
	RNDZArray, RNDUArray, CADNAArray] = getRelArraysFromAllRMFilesAtIt(nbIterations, isRelDiff)
    
    suffix = 'at_it';

	[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, ...
		RNDZArray, RNDUArray, CADNAArray] = getRelArraysFromAllRMFiles(nbIterations,suffix,isRelDiff);

	clear suffix;
end