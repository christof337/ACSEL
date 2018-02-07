
disp('début programme');

stochasticFolder = '/home/kito/Dev/Sources/ACSEL/matrice_grad/stochFiles/output';
RNDNFolder = '/home/kito/Dev/Sources/ACSEL/Matlab/output';
fileNamePrefix = 'lorenz_prec=';
fileNameSuffix1 = '_mp=200_ni=100000_rm=';
fileNameSuffix2 = '_si=10.000000_ro=28.000000_be=2.666700';
fileNameSuffix3 = '.dat';
RNDNStr = 'RNDN';
StochasticStr = 'STOCHASTIC';

delimiterIn = '\t';
headerlinesIn = 1;

INIT = 7;

k = 2;
% k = INIT; % override
shouldContinue = 1;

referenceFileName = 'lorenzRef_pre=200_rm=RNDN.dat';
refArray = importdata(strcat(RNDNFolder,'/',referenceFileName),delimiterIn,headerlinesIn);

RNDNDiff = zeros(200,2);
StochasticDiff = zeros(200,2,200);

while ( shouldContinue )
    precisionStr = int2str(k);
    % file name construction
    fileNameRNDN = strcat(RNDNFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,RNDNStr,fileNameSuffix2, fileNameSuffix3);
    
    % opening the file to check that it exists
    fileIDRNDN = fopen(fileNameRNDN, 'r');
    
    if (fileIDRNDN == -1)
        % if not, we're running out of files ==> exit
        shouldContinue = 0; % exit loop
        disp('End RNDN');
        disp(precisionStr);
    else
        index = k-INIT+1;
        fclose(fileIDRNDN); % do not need it anymore
        
        % importing array
        RNDNArray = importdata(fileNameRNDN,delimiterIn,headerlinesIn);
        % computing the diff with the reference file
        tmp1 = [k computeRelativeDiff(refArray,RNDNArray)];
        % saving the result in RNDN Diff
        %RNDNDiff = [RNDNDiff;tmp1];
        RNDNDiff(index,:) = tmp1;
        
        isStochFilesLeft = 1;
        l = 1;
        while ( isStochFilesLeft )
            itStr = int2str(l-1);
            fileNameStochastic = strcat(stochasticFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,StochasticStr,fileNameSuffix2,'(',itStr,')',fileNameSuffix3);
            fileIDStochastic = fopen(fileNameStochastic, 'r');
            if (fileIDStochastic == -1)
                isStochFilesLeft = 0;
                disp(['End Stochastic : pre=',precisionStr,', it max=',itStr]);
            else
                fclose(fileIDStochastic);
                
                StochasticArray = importdata(fileNameStochastic,delimiterIn,headerlinesIn);
                tmp2 = [k computeRelativeDiff(refArray,StochasticArray)];
                StochasticDiff(k-1,:,l) = tmp2;
                
                l = l + 1;
                
                %clear StochasticArray
            end
        end
        
        disp(strcat('[',precisionStr,'] : RNDN       = ',num2str(tmp1(:,2))));
        disp(strcat('[',precisionStr,'] : Stochastic = ',num2str(mean(StochasticDiff(k-1,2,:),3)))); % k*(l-1):((k+1)*l-1),2:3)))));
        disp('-');
        
        k = k + 1;
    end
end

% disp('--------------------------');
% disp('RNDN Diff :');
% disp(RNDNDiff);
% disp('Stochastic Diff :');
% disp(StochasticDiff);
% 
% disp(mean(RNDNDiff,'omitnan'));
% disp(mean(StochasticDiff,'omitnan'));

dlmwrite('RNDN_dif_2.dat',RNDNDiff,'\t');
dlmwrite('STOCHASTIC_dif_correct_mean_2.dat', ...
	[ StochasticDiff(:,1), 	... precision
	mean(					...
		StochasticDiff(  	...
			:, 	... all lines
			2, 	... only the second column (the diff value)
			:) 	... all stochastic runs
		, 3 ) 	... group the third dimension
	]	...
);
% dlmwrite('STOCHASTIC_dif_multiple_1.dat',StochasticDiff,'\t');
% dlmwrite('STOCHASTIC_dif_mean_0.dat',mean(StochasticDiff),'\t');
% dlmwrite('STOCHASTIC_dif_mean_1.dat',mean(StochasticDiff,1),'\t');
% dlmwrite('STOCHASTIC_dif_mean_2.dat',mean(StochasticDiff,2),'\t');
% dlmwrite('STOCHASTIC_dif_mean_3.dat',mean(StochasticDiff,3),'\t');

clear fileNamePrefix fileNameSuffix1 fileNameSuffix2 fileNameSuffix3 delimiterIn headerlinesIn k l shouldContinue
clear fileNameStochastic fileNameRNDN stochasticFolder RNDNFolder isStochFilesLeft itStr INIT index
clear precisionStr fileIDRNDN fileIDStochastic A tmp1 tmp2 refArray referenceFileName RNDNArray RNDNStr StochasticArray StochasticStr tmp
% clear RNDNDiff StochasticDiff

% fileNameFolder = '/home/kito/Dev/Sources/ACSEL/matrice_grad/stochFiles/output';
% filename = 'output/lorenz_prec=131_mp=200_ni=100000_rm=RNDN_si=10.000000_ro=28.000000_be=2.666700.dat';