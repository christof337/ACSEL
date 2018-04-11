function plot_distance_at_it_log_2(nbIterations)

% Loading data from files
[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray] = getArraysFromFiles(nbIterations);

% changing to log2
STOCHASTICArray(:,2) = log2(STOCHASTICArray(:,2));
RNDNArray(:,2) = log2(RNDNArray(:,2));
StochStdUpArray(:,2) = log2(StochStdUpArray(:,2));
StochStdDownArray(:,2) = log2(StochStdDownArray(:,2));

% -----------------------------------
% plotting
plot_with_std(nbIterations,STOCHASTICArray,RNDNArray,StochStdUpArray,StochStdDownArray,1);


end