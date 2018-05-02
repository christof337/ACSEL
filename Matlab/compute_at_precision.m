function compute_at_precision(precision, stepIt, isRelDiff)
    if ( isRelDiff ) 
		comparator = @computeRelativeDiffAt;
		comparatorNS = @computeRelativeDiffAtNonStruct;
	else
		comparator = @Kullback;
		comparatorNS = @KullbackNonStruct;
	end
    %%% This function takes each file of a given precision, for each rounding mode. It then computes the
    %%% relative distance at some precise iterations points. To know which, it will be the 1st point, then the
    %%% stepIt th point, then the (2*stepIt)th point, and so on.
	%%% This function has to be called before plotting with the same parameters
	disp('Debut programme');
	disp(strcat('On traite tous les fichiers de precision ',int2str(precision), ...
		' puis on met dans les fichiers de "data" correspondant les distances calculees aux iterations donnees'));
	
	refFolder = './output';
    dataFolder = '../matrice_grad/output';
    stochasticFolder = '../matrice_grad/stochFiles/output';
	
	NUMBER_OF_ITERATIONS = 100000;
	
	fileNamePrefix = 'lorenz_prec=';
	fileNameSuffix1 = strcat('_mp=200_ni=',int2str(NUMBER_OF_ITERATIONS),'_rm=');
	fileNameSuffix2 = '_si=10.000000_ro=28.000000_be=2.666700';
	fileNameSuffix3 = '.dat';
	%roundingModeStrings = {'RNDA';'RNDD';'RNDZ';'RNDU';'STOCHASTIC_CADNA'};
	RNDNStr = 'RNDN';
	StochasticStr = 'STOCHASTIC';
	
	delimiterIn = '\t';
	headerlinesIn = 1;
	
	MAX_NB_STOCH_FILES = 50;  % I have ran it 161 timescomputeMultipleMassiveDiffAfter(10000), but only 50 are "correct"
	NB_STOCH_FILES_TAKEN = 10;
	
	referenceFileName = 'lorenzRef_pre=200_rm=RNDN.dat';
	refArray = importdata(strcat(refFolder,'/',referenceFileName),delimiterIn,headerlinesIn);
	
	RNDNDiff = zeros(int16(log(NUMBER_OF_ITERATIONS)/log(stepIt)),2);
	RNDADiff = zeros(int16(log(NUMBER_OF_ITERATIONS)/log(stepIt)),2);
	RNDDDiff = zeros(int16(log(NUMBER_OF_ITERATIONS)/log(stepIt)),2);
	RNDZDiff = zeros(int16(log(NUMBER_OF_ITERATIONS)/log(stepIt)),2);
	RNDUDiff = zeros(int16(log(NUMBER_OF_ITERATIONS)/log(stepIt)),2);
	StochasticCadnaDiff = zeros(int16(log(NUMBER_OF_ITERATIONS)/log(stepIt)),2);
	StochasticDiff = zeros(int16(log(NUMBER_OF_ITERATIONS)/log(stepIt)),2,NB_STOCH_FILES_TAKEN-1);

	permutations = randperm(MAX_NB_STOCH_FILES); % taking NB_STOCH_FILES_TAKEN files randomly from the MAX_NB_STOCH_FILES		
	precisionStr = int2str(precision);
	% file name construction
	fileNameRNDN = strcat(dataFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,RNDNStr,fileNameSuffix2, fileNameSuffix3);
		
	% opening the file to check that it exists
	fileIDRNDN = fopen(fileNameRNDN, 'r');
		
	if (fileIDRNDN == -1)
		disp(strcat('File ',fileNameRNDN,' doesn t exist. Exiting...'));
	else
		disp('Found the file');
		% compute the file
		fclose(fileIDRNDN); % do not need it anymore
		
		% looping over rounding modes
		%roundingModeStrings = {'RNDA';'RNDD';'RNDZ';'RNDU';'STOCHASTIC_CADNA'};
		fileNameRNDA = strcat(dataFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,'RNDA',fileNameSuffix2, fileNameSuffix3);
		fileNameRNDD = strcat(dataFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,'RNDD',fileNameSuffix2, fileNameSuffix3);
		fileNameRNDZ = strcat(dataFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,'RNDZ',fileNameSuffix2, fileNameSuffix3);
		fileNameRNDU = strcat(dataFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,'RNDU',fileNameSuffix2, fileNameSuffix3);
		fileNameCADNA = strcat(dataFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,'STOCHASTIC_CADNA',fileNameSuffix2, fileNameSuffix3);

		disp('importing arrays...');
		% importing arrays		
		RNDNArray = importdata(fileNameRNDN,delimiterIn,headerlinesIn);
		RNDAArray = importdata(fileNameRNDA,delimiterIn,headerlinesIn);
		RNDDArray = importdata(fileNameRNDD,delimiterIn,headerlinesIn);
		RNDZArray = importdata(fileNameRNDZ,delimiterIn,headerlinesIn);
		RNDUArray = importdata(fileNameRNDU,delimiterIn,headerlinesIn);
		CADNAArray = importdata(fileNameCADNA,delimiterIn,headerlinesIn);
		StochasticArray = zeros(NUMBER_OF_ITERATIONS+1,3,NB_STOCH_FILES_TAKEN-1);
		
		disp('importing arrays from multiple stochastic files...');
		for stochIndex = 1:NB_STOCH_FILES_TAKEN
			itStr = int2str(permutations(stochIndex));
			fileNameStochastic = strcat(stochasticFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,StochasticStr,fileNameSuffix2,'(',itStr,')',fileNameSuffix3);
			fileIDStochastic = fopen(fileNameStochastic, 'r');
			if (fileIDStochastic == -1)
				disp(strcat('Couldn t find the stochastic file ',fileNameStochastic,' . Exiting...'));
				exit;
			else
				fclose(fileIDStochastic);
				array = importdata(fileNameStochastic,delimiterIn,headerlinesIn);
				StochasticArray(:,:,stochIndex) = array.data;
			end
		end

		j = 0;
		while j <= log(NUMBER_OF_ITERATIONS)/log(stepIt)
			%currentIt = (j-1)*stepIt+1;
			% exponential progress
			if ( j == 0 )
				currentIt = 0;
			else
				currentIt = stepIt^(j-1);
			end
			
			% computing the diff with the reference file
			relDiffN = comparator(refArray,RNDNArray, currentIt+1);
			relDiffA = comparator(refArray,RNDAArray, currentIt+1);
			relDiffD = comparator(refArray,RNDDArray, currentIt+1);
			relDiffZ = comparator(refArray,RNDZArray, currentIt+1);
			relDiffU = comparator(refArray,RNDUArray, currentIt+1);
			relDiffC = comparator(refArray,CADNAArray, currentIt+1);
			tmp1 = [currentIt relDiffN];
			% saving the result in RNDN Diff
			%RNDNDiff = [RNDNDiff;tmp1];
			RNDNDiff(j+1,:) = [currentIt relDiffN];
			RNDADiff(j+1,:) = [currentIt relDiffA];
			RNDDDiff(j+1,:) = [currentIt relDiffD];
			RNDZDiff(j+1,:) = [currentIt relDiffZ];
			RNDUDiff(j+1,:) = [currentIt relDiffU];
			StochasticCadnaDiff(j+1,:) = [currentIt relDiffC];
			for stochIndex = 1:NB_STOCH_FILES_TAKEN
				relDiff = comparatorNS(refArray,StochasticArray(:,:,stochIndex),currentIt+1);
				tmp2 = [currentIt relDiff];
				StochasticDiff(j+1,:,stochIndex) = tmp2;
			end	
			j=j+1;
		end

		disp(strcat('Computing went fine for ',int2str(j),' loops'));
% 		disp(strcat('[',precisionStr,'] : RNDN       = ',num2str(tmp1(:,2))));
% 		disp(strcat('[',precisionStr,'] : Stochastic CADNA = ',num2str(mean(StochasticDiff(index,2,:),3)))); % k*(l-1):((k+1)*l-1),2:3)))));
% 		disp(strcat('[',precisionStr,'] : Stochastic(',int2str(NB_STOCH_FILES_TAKEN),') = ',num2str(mean(StochasticDiff(index,2,:),3)))); % k*(l-1):((k+1)*l-1),2:3)))));
% 		disp('-');
	end
	
	outputFolder = 'data/';	
	if (isRelDiff )
		comparatorStr = 'relDist';
	else
		comparatorStr = 'Kullback';
	end
	dlmwrite(strcat(outputFolder,'RNDN_',comparatorStr,'_at_pre_',precisionStr,'.dat'),RNDNDiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDA_',comparatorStr,'_at_pre_',precisionStr,'.dat'),RNDADiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDD_',comparatorStr,'_at_pre_',precisionStr,'.dat'),RNDDDiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDZ_',comparatorStr,'_at_pre_',precisionStr,'.dat'),RNDZDiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDU_',comparatorStr,'_at_pre_',precisionStr,'.dat'),RNDUDiff,'\t');
	dlmwrite(strcat(outputFolder,'CADNA_',comparatorStr,'_at_pre_',precisionStr,'.dat'),StochasticCadnaDiff,'\t');
	
	meanValue = mean(					...
		StochasticDiff(  	...
		:, 	... all lines
		2, 	... only the second column (the diff value)
		:) 	... all stochastic runs
		, 3 ); 	% group the third dimension (the stochastic runs)
	dlmwrite(strcat(outputFolder,'STOCHASTIC_',comparatorStr,'_at_pre_',precisionStr,'(mean).dat'), ...
		[ StochasticDiff(:,1), 	... the iteration number
		meanValue ...
		]	...
		);
	
	stdValue = std(					...
		StochasticDiff(  	...
		:, 	... all lines
		2, 	... only the second column (the diff value)
		:) 	... all stochastic runs
		, 0, ...
		3 ); 	% group the third dimension (the stochastic runs)
	stdUp = meanValue + stdValue;
	stdDown = meanValue - stdValue;
	
	dlmwrite(strcat(outputFolder,'STOCHASTIC_',comparatorStr,'_at_pre_',precisionStr,'(deviationUp).dat'), ...
		[ StochasticDiff(:,1), 	... the iteration number
		stdUp	...
		]	...
		);
		
	dlmwrite(strcat(outputFolder,'STOCHASTIC_',comparatorStr,'_at_pre_',precisionStr,'(deviationDown).dat'), ...
		[ StochasticDiff(:,1), 	... precision
		stdDown	...
		]	...
		);
	
	disp('Successfully wrote in files');
	disp('Exiting program normally...');
	
	
	clear refFolder dataFolder stochasticFolder NUMBER_OF_ITERATIONS fileNamePrefix fileNameSuffix1 ...
		fileNameSuffix2	fileNameSuffix3 roundingModeStrings RNDNStr StochasticStr delimiterIn ...
		headerlinesIn shouldContinue MAX_NB_STOCH_FILES NB_STOCH_FILES_TAKEN referenceFileName refArray ...
		RNDNDiff RNDADiff RNDDDiff RNDZDiff	RNDUDiff StochasticCadnaDiff StochasticDiff permutations ...
		precisionStr fileNameRNDN fileIDRNDN fileNameRNDA fileNameRNDD fileNameRNDZ fileNameRNDU ...
		fileNameCADNA RNDNArray RNDAArray RNDDArray  RNDDArray RNDZArray RNDUArray CADNAArray ...
		StochasticArray itStr fileNameStochastic fileIDStochastic currentIt relDiffN relDiffA relDiffD ...
		relDiffZ relDiffU relDiffC tmp1 relDiff tmp2 j outputFolder meanValue stdValue;
	
	% fileNameFolder = '/home/kito/Dev/Sources/ACSEL/matrice_grad/stochFiles/output';
	% filename = 'output/lorenz_prec=131_mp=200_ni=100000_rm=RNDN_si=10.000000_ro=28.000000_be=2.666700.dat';

end