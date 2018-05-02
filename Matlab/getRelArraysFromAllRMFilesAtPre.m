function [STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, ...
	RNDZArray, RNDUArray, CADNAArray] = getRelArraysFromAllRMFilesAtPre(precision, isRelDiff)
	
	suffix = 'at_pre';

	[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, RNDZArray, ...
		RNDUArray, CADNAArray] = getRelArraysFromAllRMFiles(precision,suffix, isRelDiff);

	clear suffix;
end