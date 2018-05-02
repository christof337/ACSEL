function computeMassRelDiffAfter(NB_ITERATIONS)

disp('début programme');

stochasticFolder = '../matrice_grad/stochFiles/output';
%stochasticFolder = '/home/kito/Dev/Sources/ACSEL/matrice_grad/output';
RNDNFolder = './output';
fileNamePrefix = 'lorenz_prec=';
fileNameSuffix1 = '_mp=200_ni=100000_rm=';
fileNameSuffix2 = '_si=10.000000_ro=28.000000_be=2.666700';
fileNameSuffix3 = '.dat';
RNDNStr = 'RNDN';
%StochasticStr = 'STOCHASTIC';
StochasticStr = 'STOCHASTIC';

delimiterIn = '/t';
headerlinesIn = 1;

MIN_PRECISION = 4;
MAX_PRECISION = 200;

k = MIN_PRECISION; 
shouldContinue = 1;
MAX_NB_STOCH_FILES = 50;  % I have ran it 161 timescomputeMultipleMassiveDiffAfter(10000), but only 50 are "correct"
NB_STOCH_FILES_TAKEN = 20;

NB_BENCH_ZEROS = 10; % stop reading files as soon as for 10 precisions in a row the computed relDiff is 0

referenceFileName = 'lorenzRef_pre=200_rm=RNDN.dat';
refArray = importdata(strcat(RNDNFolder,'/',referenceFileName),delimiterIn,headerlinesIn);

RNDNDiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2);
StochasticDiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2,NB_STOCH_FILES_TAKEN);

permutations = randperm(MAX_NB_STOCH_FILES);%,NB_STOCH_FILES_TAKEN); % taking NB_STOCH_FILES_TAKEN files randomly

nbZeros = 0;
% loop over precisions
while ( shouldContinue )
    index = k-MIN_PRECISION+1;
    
    precisionStr = int2str(k);
    % file name construction
    fileNameRNDN = strcat(RNDNFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,RNDNStr,fileNameSuffix2, fileNameSuffix3);
    
    % opening the file to check that it exists
    fileIDRNDN = fopen(fileNameRNDN, 'r');
    
    if (fileIDRNDN == -1)
        % if not, we're running out of files ==> exit
        shouldContinue = 0; % exit loop
        disp('End RNDN');
        %disp(precisionStr);
    elseif (nbZeros >= NB_BENCH_ZEROS)
        fclose(fileIDRNDN);
        disp('filling with zeros...')
        shouldContinue = 0; % exit loop
        % filling with zeros
        RNDNDiff(index:size(RNDNDiff,1),:) = horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(RNDNDiff,1)-index+1,1));
        for cpt = 1:NB_STOCH_FILES_TAKEN
            StochasticDiff(index:size(StochasticDiff,1),:,cpt) = horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(StochasticDiff,1)-index+1,1));
        end
    else
        % compute the file
        fclose(fileIDRNDN); % do not need it anymore
        
        % importing array
        RNDNArray = importdata(fileNameRNDN,delimiterIn,headerlinesIn);
        %disp(fileNameRNDN);
        % computing the diff with the reference file
        relDiff = computeRelativeDiffAt(refArray,RNDNArray, NB_ITERATIONS);
        tmp1 = [k relDiff];
        % saving the result in RNDN Diff
        %RNDNDiff = [RNDNDiff;tmp1];
        RNDNDiff(index,:) = tmp1;
        
        if (relDiff == 0)
            nbZeros = nbZeros + 1;
        else
            nbZeros = 0;
        end
        
        isStochFilesLeft = 1;
        l = 1;
        while ( isStochFilesLeft && l < NB_STOCH_FILES_TAKEN)
            itStr = int2str(permutations(l));
            %fileNameStochastic = strcat(stochasticFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,StochasticStr,fileNameSuffix2,'(',itStr,')',fileNameSuffix3);
            fileNameStochastic = strcat(stochasticFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,StochasticStr,fileNameSuffix2,fileNameSuffix3);
            fileIDStochastic = fopen(fileNameStochastic, 'r');
            if (fileIDStochastic == -1)
                isStochFilesLeft = 0;
                disp(['End Stochastic : pre=',precisionStr,', it max=',itStr]);
            else
                fclose(fileIDStochastic);
                
                StochasticArray = importdata(fileNameStochastic,delimiterIn,headerlinesIn);
                relDiff = computeRelativeDiffAt(refArray,StochasticArray,NB_ITERATIONS);
                tmp2 = [k relDiff];
                StochasticDiff(index,:,l) = tmp2;
                % StochasticDiff(:,1,:) = k:200;
                
                l = l + 1;
                
                %clear StochasticArray
            end
        end
        
        disp(strcat('[',precisionStr,'] : RNDN       = ',num2str(tmp1(:,2))));
        disp(strcat('[',precisionStr,'] : Stochastic = ',num2str(mean(StochasticDiff(index,2,:),3)))); % k*(l-1):((k+1)*l-1),2:3)))));
        disp('-');
        
        k = k + 1;
    end
end

outputFolder = 'data/';
dlmwrite(strcat(outputFolder,'RNDN_rel_dif_at_it_',int2str(NB_ITERATIONS),'.dat'),RNDNDiff,'/t');

meanValue = mean(					...
    StochasticDiff(  	...
    :, 	... all lines
    2, 	... only the second column (the diff value)
    :) 	... all stochastic runs
    , 3 ); 	% group the third dimension
dlmwrite(strcat(outputFolder,'STOCHASTIC_CADNA_dif_at_it_',int2str(NB_ITERATIONS),'(correctMean).dat'), ...
    [ StochasticDiff(:,1), 	... precision
    meanValue ...
    ]	...
    );

stdValue = std(					...
    StochasticDiff(  	...
    :, 	... all lines
    2, 	... only the second column (the diff value)
    :) 	... all stochastic runs
    , 0, ...
    3 ); 	% group the third dimension
stdUp = meanValue + stdValue;
stdDown = meanValue - stdValue;

dlmwrite(strcat(outputFolder,'STOCHASTIC_CADNA_dif_at_it_',int2str(NB_ITERATIONS),'(deviationUp).dat'), ...
    [ StochasticDiff(:,1), 	... precision
    stdUp	...
    ]	...
    );

dlmwrite(strcat(outputFolder,'STOCHASTIC_CADNA_dif_at_it_',int2str(NB_ITERATIONS),'(deviationDown).dat'), ...
    [ StochasticDiff(:,1), 	... precision
    stdDown	...
    ]	...
    );

disp('Exiting program normally...');

clear fileNamePrefix fileNameSuffix1 fileNameSuffix2 fileNameSuffix3 ...
    delimiterIn headerlinesIn k l shouldContinue fileNameStochastic ...
    fileNameRNDN stochasticFolder RNDNFolder isStochFilesLeft itStr ...
    INIT index precisionStr fileIDRNDN fileIDStochastic A tmp1 tmp2 ...
    refArray referenceFileName RNDNArray RNDNStr StochasticArray ...
    StochasticStr tmp relDiff meanValue stdValue stdUp stdDown;
% clear RNDNDiff StochasticDiff

% fileNameFolder = '/home/kito/Dev/Sources/ACSEL/matrice_grad/stochFiles/output';
% filename = 'output/lorenz_prec=131_mp=200_ni=100000_rm=RNDN_si=10.000000_ro=28.000000_be=2.666700.dat';

end