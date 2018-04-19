function plotDistAtPre(precision)
	% Loading data from files
	[STOCHASTICArray, RNDNArray, StochStdUpArray, StochStdDownArray, RNDAArray, RNDDArray, RNDZArray, ...
		RNDUArray, CADNAArray] = getRelArraysFromAllRMFilesAtPre(precision);

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

	% -----------------------------------
	% plotting
	%plot_with_std(nbIterations,STOCHASTICArray,RNDNArray, StochStdUpArray,StochStdDownArray,1)
	%plot_without_std(nbIterations,STOCHASTICCadnaArray,RNDNArray,1);
	C = 1;
	S = 2;
	N = 3;
	ARM = 4:7;
	Sstd = 8:9;

	p = plot(CADNAArray(:,1),CADNAArray(:,2), ...
		STOCHASTICArray(:,1),STOCHASTICArray(:,2), ...
		RNDNArray(:,1),RNDNArray(:,2), ...  % [0 200],[10^7 10^7],...
		RNDZArray(:,1),RNDZArray(:,2), ...  % [0 200],[10^7 10^7],...
		RNDUArray(:,1),RNDUArray(:,2), ...  % [0 200],[10^7 10^7],...
		RNDDArray(:,1),RNDDArray(:,2), ...  % [0 200],[10^7 10^7],...
		RNDAArray(:,1),RNDAArray(:,2), ...  % [0 200],[10^7 10^7],...
		StochStdUpArray(:,1),StochStdUpArray(:,2), ...
		StochStdDownArray(:,1),StochStdDownArray(:,2), ...
		'LineWidth',2,...
		'LineStyle','-',...
		'Marker','o');

	% -----------------------------------
	% changing plot parameters
	%lastNonInfValue = size(STOCHASTICArray(:,2));
	% lastNonInfValue = getIndexOfLastNonInfValue(STOCHASTICArray(:,2));
	%MARGIN = 10;
	if (precision < 80)
		xlim([3 (lastNonInfValue + MARGIN)]);
	end
	% overwrite
	%xlim([30 60000]);
	yticks = get(gca,'YTick');
	for j = 1:length(yticks)
		ytl{j} = ['2^' num2str(yticks(j))];
	end
	set(gca, 'YTickLabel', ytl)


	set(p(C),'Color','r');
	set(p(C),'Marker','d');
	set(p(C),'LineWidth',4);
	%set(p(1),'LineStyle','-.');
	set(p(S),'Color','b');
	set(p(S),'LineWidth',2);
	set(p(N),'Color','g');
	set(p(N),'LineWidth',2);
	set(p(N),'Marker','x');
	set(p(N),'LineStyle','-');
	set(p(Sstd),'Color','b');
	set(p(Sstd),'LineStyle','--');
	set(p(Sstd),'LineWidth',1.9);
	set(p(Sstd),'Marker','none');
	set(p(ARM),'Marker','d');
	set(p(ARM),'LineWidth',2);
	set(p(ARM(1)),'Marker','s');
	set(p(ARM(1)),'MarkerSize',9);
	set(p(ARM(3)),'Marker','^');
	set(p(ARM(4)),'Marker','*');
	%set(p(:),'MarkerIndices',1:3:length(RNDNArray(:,2)));

	% -----------------------------------
	% changing plot labels
	% title
	plotTitle = {'Distance of various rounding modes compared to optimal'; ...
		strcat('Lorenz Attractor run for a precision of ',int2str(precision),' bits over time')};
	t = title(plotTitle);
	% xaxis name
	h = xlabel('Iterations');
	% yaxis name
	g = ylabel({'Distance compared to optimal';'Lorenz Attractor run (prec=200)'});
	%legend
	leg = legend({'Round to Nearest','Stochastic rounding mode (mean)',...
		'CADNA rounding', 'Round toward zero', 'Round toward plus infinity', ...
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
	set(gca,'FontSize',25);
	set(gca,'FontName',font);
	set(t,'FontSize',30);
	set(leg,'FontSize',15);

end