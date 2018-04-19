function [STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, ...
	RNDZArray, RNDUArray, CADNAArray] = getRelArraysFromAllRMFilesAtPre(precision)
	
	suffix = 'at_pre';

	[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, RNDZArray, ...
		RNDUArray, CADNAArray] = getRelArraysFromAllRMFiles(precision,suffix);

	clear suffix;
end