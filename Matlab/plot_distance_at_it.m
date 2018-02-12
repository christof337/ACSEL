function plot_distance_at_it(nbIterations) 
    % -----------------------------------
    % VARIABLES
    fileNameNumVal = 3;

    % -----------------------------------
    % getting the wanted arrays
    fileExtension = '.dat';
    dataFolder = 'data';

    StochasticFileName = strcat('STOCHASTIC_dif_at_it_', ...
        int2str(nbIterations),'(correctMean)',fileExtension);
    RNDNFileName = strcat('RNDN_dif_at_it_',int2str(nbIterations),fileExtension);

    delimiterInS = ',';
    delimiterInR = '\t';
    headerlinesIn = 0;

    STOCHASTICArray = importdata(strcat(dataFolder,'/',StochasticFileName), ...
        delimiterInS,headerlinesIn);
    RNDNArray = importdata(strcat(dataFolder,'/',RNDNFileName), ...
        delimiterInR,headerlinesIn);

    % -----------------------------------
    % plotting
    p = plot(STOCHASTICArray(:,1),STOCHASTICArray(:,2), ...
        RNDNArray(:,1),RNDNArray(:,2), ...  % [0 200],[10^7 10^7],... 
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
    g = ylabel('Distance  compared to optimal Lorenz Attractor run (prec=200)');
    %legend
    legend({'Stochastic rounding mode','Round to Nearest'...
       ... % ,'Not a number threshold' ... % unused now
        });

    % -----------------------------------
    % changing plot parameters
    % x and y limits
    xlim([3 70]);
    %ylim([10^3 10^8+10^8*2]);
    % xticks(0:10:200)
    set(gca,'YScale','log');

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

    clear cpt font h x xAX xLabelP g p val dataFolder delimiterInR ...
        delimiterInS fileExtension fileNameNumVal headerlinesIn isNanArray ...
        nbIterations plotTitle t;
end