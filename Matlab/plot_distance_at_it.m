function plot_distance_at_it(nbIterations)

% Loading data from files
[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray] = getArraysFromFiles(nbIterations);

% -----------------------------------
% plotting
plot_with_std(nbIterations,STOCHASTICArray,RNDNArray,StochStdUpArray,StochStdDownArray, 0);

end