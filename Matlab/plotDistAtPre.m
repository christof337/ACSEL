function plotDistAtPre(precision, isRelDiff)
    %precision = 53;

	% Loading data from files
	[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, RNDZArray, ...
		RNDUArray, CADNAArray] = getRelArraysFromAllRMFilesAtPre(precision, isRelDiff);

	% changing to log2
	STOCHASTICArray(:,2) = log2(STOCHASTICArray(:,2));
	RNDNArray(:,2) = log2(RNDNArray(:,2));
	RNDAArray(:,2) = log2(RNDAArray(:,2));
	RNDDArray(:,2) = log2(RNDDArray(:,2));
	RNDZArray(:,2) = log2(RNDZArray(:,2));
	RNDUArray(:,2) = log2(RNDUArray(:,2));
	CADNAArray(:,2) = log2(CADNAArray(:,2));
	StochStdUpArray(:,2) = log2(StochStdUpArray(:,2));
	StochStdDownArray(:,2) = log2(StochStdDownArray(:,2));
% 	STOCHASTICArray = log2(STOCHASTICArray);
% 	RNDNArray = log2(RNDNArray);
% 	RNDAArray = log2(RNDAArray);
% 	RNDDArray = log2(RNDDArray);
% 	RNDZArray = log2(RNDZArray);
% 	RNDUArray = log2(RNDUArray);
% 	CADNAArray = log2(CADNAArray);
% 	StochStdUpArray = log2(StochStdUpArray);
% 	StochStdDownArray = log2(StochStdDownArray);
	% -----------------------------------
	% plotting
	%plot_with_std(nbIterations,STOCHASTICArray,RNDNArray, StochStdUpArray,StochStdDownArray,1)
	%plot_without_std(nbIterations,STOCHASTICCadnaArray,RNDNArray,1);
	C = 1;
	S = 2;
	N = 3;
	ARM = 4:7;
	Sstd = 8:9;

	p = plot(cat(0,CADNAArray(:,1)),cat(0,CADNAArray(:,2)), ...
		cat(0,STOCHASTICArray(:,1)),cat(0,STOCHASTICArray(:,2)), ...
		cat(0,RNDNArray(:,1)),cat(0,RNDNArray(:,2)), ...  % [0 200],[10^7 10^7],...
		cat(0,RNDZArray(:,1)),cat(0,RNDZArray(:,2)), ...  % [0 200],[10^7 10^7],...
		cat(0,RNDUArray(:,1)),cat(0,RNDUArray(:,2)), ...  % [0 200],[10^7 10^7],...
		cat(0,RNDDArray(:,1)),cat(0,RNDDArray(:,2)), ...  % [0 200],[10^7 10^7],...
		cat(0,RNDAArray(:,1)),cat(0,RNDAArray(:,2)), ...  % [0 200],[10^7 10^7],...
		cat(0,StochStdUpArray(:,1)),cat(0,StochStdUpArray(:,2)), ...
		cat(0,StochStdDownArray(:,1)),cat(0,StochStdDownArray(:,2)), ...
		'LineWidth',2,...
		'LineStyle','-',...
		'Marker','o');

	% -----------------------------------
	% changing plot parameters
	%lastNonInfValue = size(STOCHASTICArray(:,2));
	% lastNonInfValue = getIndexOfLastNonInfValue(STOCHASTICArray(:,2));
	%MARGIN = 10;
% 	if (precision < 80)
% 		xlim([3 (lastNonInfValue + MARGIN)]);
%         xlim([0 60000]);
% 	end
	
% 	size(RNDNArray(:,1),1)
% 	RNDNArray()
    ticks(1) = 0;
	for j = 1:size(RNDNArray(:,1),1)
		ticks(j+1) = 2^(j-1);
	end
	set(gca,'XTick',ticks)
    % X log2 tick labels
    xticks = get(gca,'XTick');
	xtl{1} = '0';
	xtl{2} = ['2^' num2str(xticks(2)-1)];
	for j = 3:length(xticks)
		xtl{j} = ['2^' num2str(log2(xticks(j)))];
	end
	set(gca, 'XTickLabel', xtl)
	%xticks(ticks)
 	%set(gca, 'XTickLabel', num2str(ticks))
% 	set(gca, 'XTickLabel', ticks)
	
    % Y log2 tick labels
	yticks = get(gca,'YTick');
	for j = 1:length(yticks)
		ytl{j} = ['2^' num2str(yticks(j))];
	end
	set(gca, 'YTickLabel', ytl)
	
% 	set(gca, 'XTickLabel',[])                      %# suppress current x-labels
% 	xt = get(gca, 'XTick');
% 	yl = get(gca, 'YLim');
% 	str = cellstr( num2str(2^xt(:),'%d') );      %# format x-ticks as 2^{xx}
% 	hTxt = text(xt, yl(ones(size(xt))), str, ...   %# create text at same locations
%     'Interpreter','tex', ...                   %# specify tex interpreter
%     'VerticalAlignment','top', ...             %# v-align to be underneath
%     'HorizontalAlignment','center');           %# h-aligh to be centered
	set(gca,'XScale','log')

	set(p(N),'Color','r');
	set(p(N),'Marker','d');
	set(p(N),'LineWidth',7);
	%set(p(1),'LineStyle','-.');
	set(p(S),'Color','b');
	set(p(S),'LineWidth',3);
	set(p(C),'Color','g');
	set(p(C),'LineWidth',3);
	set(p(C),'Marker','x');
	set(p(C),'LineStyle','-');
	set(p(Sstd),'Color','b');
	set(p(Sstd),'LineStyle','--');
	set(p(Sstd),'LineWidth',1.9);
	set(p(Sstd),'Marker','none');
	set(p(ARM),'Marker','d');
	set(p(ARM),'LineWidth',3);
	set(p(ARM(1)),'Marker','s');
	set(p(ARM(1)),'MarkerSize',9);
	set(p(ARM(3)),'Marker','^');
	set(p(ARM(4)),'Marker','*');
	%set(p(:),'MarkerIndices',1:3:length(RNDNArray(:,2)));

	% -----------------------------------
	% changing plot labels
	% title
    if(isRelDiff)
        metrique = 'Relative distance ';
    else
        metrique = 'Kullback-Liebler divergence ';
    end
	plotTitle = {strcat(metrique, ' of various rounding modes compared to optimal'); ...
		strcat('Lorenz Attractor run for a precision of ',int2str(precision),' bits over time')};
	t = title(plotTitle);
	% xaxis name
	h = xlabel('Iterations');
	% yaxis name
	g = ylabel({strcat(metrique, ' compared to optimal');'Lorenz Attractor run (prec=200)'});
	%legend
	leg = legend({'CADNA rounding','Stochastic rounding mode (mean)',...
		 'Round to Nearest','Round toward zero', 'Round toward plus infinity', ...
		'Round toward minus infinity', 'Round away from zero', ...
		'Stochastic rounding mode standard deviation', ...
		});

	% -----------------------------------
	% changing plot font and size
	font = 'Helvetica';
	set(0,'defaultAxesFontName',font);
	set(0,'defaultTextFontName',font);
	set(h,'FontName',font);
	set(h,'FontSize',30);
	set(g,'FontName',font);
	set(g,'FontSize',30);
	set(gca,'FontSize',20);
	set(gca,'FontName',font);
	set(t,'FontSize',30);
	set(leg,'FontSize',15);

end