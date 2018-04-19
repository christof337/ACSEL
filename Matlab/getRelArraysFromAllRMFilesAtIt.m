function [STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, ...
	RNDZArray, RNDUArray, CADNAArray] = getRelArraysFromAllRMFilesAtIt(nbIterations)
	
	suffix = 'at_it';

	[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, ...
		RNDZArray, RNDUArray, CADNAArray] = getRelArraysFromAllRMFiles(nbIterations,suffix);

	clear suffix;
end