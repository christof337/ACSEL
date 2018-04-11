function plot_relative_distance_CADNA_at_it_log_2(nbIterations)

% Loading data from files
[STOCHASTICCadnaArray, RNDNArray] = getRelCadnaArraysFromFiles(nbIterations);

[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray] = getRelArraysFromFiles(nbIterations);

% changing to log2
STOCHASTICArray(:,2) = log2(STOCHASTICArray(:,2));
RNDNArray(:,2) = log2(RNDNArray(:,2));
StochStdUpArray(:,2) = log2(StochStdUpArray(:,2));
StochStdDownArray(:,2) = log2(StochStdDownArray(:,2));

 %= 10000;

% changing to log2
STOCHASTICCadnaArray(:,2) = log2(STOCHASTICCadnaArray(:,2));
%RNDNArray(:,2) = log2(RNDNArray(:,2));

% -----------------------------------
% plotting
%plot_with_std(nbIterations,STOCHASTICArray,RNDNArray, StochStdUpArray,StochStdDownArray,1)
%plot_without_std(nbIterations,STOCHASTICCadnaArray,RNDNArray,1);
p = plot(STOCHASTICCadnaArray(:,1),STOCHASTICCadnaArray(:,2), ...
    STOCHASTICArray(:,1),STOCHASTICArray(:,2), ...
    RNDNArray(:,1),RNDNArray(:,2), ...  % [0 200],[10^7 10^7],...
    StochStdUpArray(:,1),StochStdUpArray(:,2), ...
    StochStdDownArray(:,1),StochStdDownArray(:,2), ...
    'LineWidth',2,...
    'LineStyle','-',...
    'Marker','o');
% -----------------------------------
% changing plot labels
% title
plotTitle = {'Deviation of RNDN rounding and mean Stochastic rounding compared to optimal'; ...
    strcat('Lorenz Attractor run after ',int2str(nbIterations),' iterations for various floating point precisions')};
t = title(plotTitle);
% xaxis name
h = xlabel('Significand precision');
% yaxis name
g = ylabel({'Distance compared to optimal';'Lorenz Attractor run (prec=200)'});
%legend
leg = legend({'Stochastic rounding mode (mean)','Round to Nearest',...
    'Stochastic rounding mode standard deviation'
    ... % ,'Not a number threshold' ... % unused now
    });
set(leg,'FontSize',15);

% -----------------------------------
% changing plot font and size
font = 'Helvetica';
set(0,'defaultAxesFontName',font);
set(0,'defaultTextFontName',font);
set(h,'FontName',font);
set(h,'FontSize',30);
set(g,'FontName',font);
set(g,'FontSize',30);
set(gca,'FontSize',25);
set(gca,'FontName',font);
set(t,'FontSize',30);

% scriptWindow(gca)

% printing vertical lines instead of NaN values ; never worked
%x = linspace(0,200);
isNanArray = isnan(RNDNArray(:,2));
cpt = 0;
for val = isNanArray
    % val
    if val == 1
        disp('test?');
        disp([cpt, ' element is Nan ',RNDNArray(cpt,2)]);
        % we change each "NaN" value by a vertical line
        line([cpt cpt],[0 inf],'Color','green');
    end
    cpt = cpt + 1;
end
% pl = line([0 200],[10^8 10^8],'Color','black');

% p;

% -----------------------------------
% changing plot parameters

    lastNonInfValue = getIndexOfLastNonInfValue(STOCHASTICArray(:,2));
    MARGIN = 10;
    xlim([3 (lastNonInfValue + MARGIN)]);
    yticks = get(gca,'YTick');
    for j = 1:length(yticks)
        ytl{j} = ['2^' num2str(yticks(j))];
    end
    set(gca, 'YTickLabel', ytl)


set(p(1),'Color','r');
set(p(1),'Marker','d');
set(p(1),'LineWidth',4);
%set(p(1),'LineStyle','-.');
set(p(2),'Color','b');
set(p(2),'LineWidth',2);
set(p(3),'Color','g');
set(p(3),'LineWidth',2);
set(p(3),'Marker','+');
set(p(3),'LineStyle','-');
set(p(4),'Color','b');
set(p(4),'LineStyle','--');
set(p(4),'LineWidth',1.9);
set(p(4),'Marker','none');
set(p(5),'Color','b');
set(p(5),'LineStyle','--');
set(p(5),'LineWidth',1.9);
set(p(5),'Marker','none');

% title
plotTitle = {' distance of RNDN rounding and CADNA Stochastic rounding compared to optimal'; ...
    strcat('Lorenz Attractor run after ',int2str(nbIterations),' iterations for various floating point precisions')};
t = title(plotTitle);
% yaxis name
g = ylabel({' distance compared to optimal';'Lorenz Attractor run (prec=200)'});
%legend
leg = legend({'CADNA Stochastic rounding mode (mean)', ...
    'Stochastic rounding', 'Round to Nearest', ...
    'Stochastic rounding mode standard deviation'
    ... % ,'Not a number threshold' ... % unused now
    });
end