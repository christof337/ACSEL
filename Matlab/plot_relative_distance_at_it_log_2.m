function plot_relative_distance_at_it_log_2(nbIterations)

 %= 10000;
% Loading data from files
[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray] = getRelArraysFromFiles(nbIterations);

% changing to log2
STOCHASTICArray(:,2) = log2(STOCHASTICArray(:,2));
RNDNArray(:,2) = log2(RNDNArray(:,2));
StochStdUpArray(:,2) = log2(StochStdUpArray(:,2));
StochStdDownArray(:,2) = log2(StochStdDownArray(:,2));

% -----------------------------------
% plotting
plot_with_std(nbIterations,STOCHASTICArray,RNDNArray,StochStdUpArray,StochStdDownArray,1);

% title
plotTitle = {'Relative distance of RNDN rounding and mean Stochastic rounding compared to optimal'; ...
    strcat('Lorenz Attractor run after ',int2str(nbIterations),' iterations for various floating point precisions')};
t = title(plotTitle);
% yaxis name
g = ylabel({'Relative distance compared to optimal';'Lorenz Attractor run (prec=200)'});

end