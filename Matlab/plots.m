font = 'Helvetica';

set(0,'defaultAxesFontName',font);
set(0,'defaultTextFontName',font);

STOCHASTICArray = STOCHASTIC_dif_correct_mean;
RNDNArray = RNDN_dif_1;
x = linspace(0,200);

p = plot(STOCHASTICArray(:,1),STOCHASTICArray(:,2), ...
    RNDNArray(:,1),RNDNArray(:,2), ...  % [0 200],[10^7 10^7],... 
    'LineWidth',1.5,...
    'LineStyle','--',...
    'Marker','o');

% scriptWindow(gca)
%hold on

h = xlabel('Floating point precision', 'FontName', font);
set(h,'FontSize',20);

%get(h)
% p1 = scatter(STOCHASTICArray);
% hold on
% p2 = scatter(RNDNArray(:,2));

xAX = get(gca,'XAxis');
set(gca,'FontSize',20);
set(gca,'FontName',font);
xLabelP = get(gca,'XLabel');
%disp('xlabel');
%get(xLabelP);
%disp('gca');
%get(gca);
%set(xAX,'FontSize', 30)

% disp(RNDNArray(:,2));
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

% yscale('log');
set(gca,'YScale','log');
set(gca,'FontSize',20);
xlim([3 inf]);
ylim([10^3 10^8+10^8*2]);
% xticks(0:10:200)

g = ylabel('Relative error (compared to optimal Lorenz Attractor run (prec=200))', 'FontSize', 20);
% set(g,'FontSize',30);

legend({'Stochastic rounding mode','Round to Nearest'...
    ,'Not a number threshold' ...
    })

title({'Deviation of RNDN rounding and Stochastic rounding compared to optimal';'Lorenz Attractor run (10^5 iterations) for various floating point precisions'}); 

p;

% p(1).DisplayName='Stochastic';
% p(2).DisplayName='RNDN';

% p(1).MarkerEdgeColor = 'b';
% p(2).MarkerEdgeColor = 'g';

% p(1).LineWidth = 1.5;
% p(2).LineWidth = 1.5;

% ax = gca;
% ax.YScale = 'log';

clear cpt font h x xAX xLabelP g p val;