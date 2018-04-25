function computeRelDiffAfter(NB_ITERATIONS)

	disp('debut programme');

	RNDXFolder = '../matrice_grad/output';
	cadnaFolder = '../matrice_grad/output';
	stochasticFolder = '../matrice_grad/stochFiles/output';

	RNDNFolder = './output';
	fileNamePrefix = 'lorenz_prec=';
	fileNameSuffix1 = '_mp=200_ni=100000_rm=';
	fileNameSuffix2 = '_si=10.000000_ro=28.000000_be=2.666700';
	fileNameSuffix3 = '.dat';
	roundingModeStrings = ['RNDA';'RNDD';'RNDZ';'RNDU'];
	RNDNStr = 'RNDN';
	CadnaStr = 'STOCHASTIC_CADNA';
	StochasticStr = 'STOCHASTIC';

	delimiterIn = '\t';
	headerlinesIn = 1;

	MIN_PRECISION = 4;
	MAX_PRECISION = 200;

	k = MIN_PRECISION;
	shouldContinue = 1;
	MAX_NB_STOCH_FILES = 50;  % I have ran it 161 timescomputeMultipleMassiveDiffAfter(10000), but only 50 are "correct"
	NB_STOCH_FILES_TAKEN = 20;

	NB_BENCH_ZEROS = 5; % stop reading files as soon as for 10 precisions in a row the computed relDiff is 0

	referenceFileName = 'lorenzRef_pre=200_rm=RNDN.dat';
	refArray = importdata(strcat(RNDNFolder,'/',referenceFileName),delimiterIn,headerlinesIn);

	RNDNDiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2);
	RNDADiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2);
	RNDDDiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2);
	RNDZDiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2);
	RNDUDiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2);
	CADNADiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2);
	StochasticDiff = zeros(MAX_PRECISION-MIN_PRECISION+1,2,NB_STOCH_FILES_TAKEN-1);

	permutations = randperm(MAX_NB_STOCH_FILES);%,NB_STOCH_FILES_TAKEN); % taking NB_STOCH_FILES_TAKEN files randomly

	nbZeros = 0;
	% loop over precisions (k)
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
			RNDADiff(index:size(RNDADiff,1),:) = horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(RNDADiff,1)-index+1,1));
			RNDDDiff(index:size(RNDDDiff,1),:) = horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(RNDDDiff,1)-index+1,1));
			RNDZDiff(index:size(RNDZDiff,1),:) = horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(RNDZDiff,1)-index+1,1));
			RNDUDiff(index:size(RNDUDiff,1),:) = horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(RNDUDiff,1)-index+1,1));
			CADNADiff(index:size(CADNADiff,1),:)=horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(CADNADiff,1)-index+1,1));
			for cpt = 1:NB_STOCH_FILES_TAKEN
				StochasticDiff(index:size(StochasticDiff,1),:,cpt) = horzcat(permute(k:MAX_PRECISION,[2 1]),zeros(size(StochasticDiff,1)-index+1,1));
			end
		else
			% compute the file
			fclose(fileIDRNDN); % do not need it anymore

			fileNameRNDA = strcat(RNDXFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,roundingModeStrings(1,:),fileNameSuffix2, fileNameSuffix3);
			fileNameRNDD = strcat(RNDXFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,roundingModeStrings(2,:),fileNameSuffix2, fileNameSuffix3);
			fileNameRNDZ = strcat(RNDXFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,roundingModeStrings(3,:),fileNameSuffix2, fileNameSuffix3);
			fileNameRNDU = strcat(RNDXFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,roundingModeStrings(4,:),fileNameSuffix2, fileNameSuffix3);
			fileNameCADNA= strcat(cadnaFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,CadnaStr,fileNameSuffix2, fileNameSuffix3);
			% importing arrays
			RNDNArray = importdata(fileNameRNDN,delimiterIn,headerlinesIn);
			RNDAArray = importdata(fileNameRNDA,delimiterIn,headerlinesIn);
			RNDDArray = importdata(fileNameRNDD,delimiterIn,headerlinesIn);
			RNDZArray = importdata(fileNameRNDZ,delimiterIn,headerlinesIn);
			RNDUArray = importdata(fileNameRNDU,delimiterIn,headerlinesIn);
			CADNAArray = importdata(fileNameCADNA,delimiterIn,headerlinesIn);
			%disp(fileNameRNDN);
			% computing the diff with the reference file
			relDiffN = computeRelativeDiffAt(refArray,RNDNArray, NB_ITERATIONS);
			relDiffA = computeRelativeDiffAt(refArray,RNDAArray, NB_ITERATIONS);
			relDiffD = computeRelativeDiffAt(refArray,RNDDArray, NB_ITERATIONS);
			relDiffZ = computeRelativeDiffAt(refArray,RNDZArray, NB_ITERATIONS);
			relDiffU = computeRelativeDiffAt(refArray,RNDUArray, NB_ITERATIONS);
			relDiffC = computeRelativeDiffAt(refArray,CADNAArray, NB_ITERATIONS);
			tmp1 = [k relDiffN];
			% saving the result in RNDN Diff
			%RNDNDiff = [RNDNDiff;tmp1];
			RNDNDiff(index,:) = [k relDiffN];
			RNDADiff(index,:) = [k relDiffA];
			RNDDDiff(index,:) = [k relDiffD];
			RNDZDiff(index,:) = [k relDiffZ];
			RNDUDiff(index,:) = [k relDiffU];
			CADNADiff(index,:) = [k relDiffC];

			if (relDiffN == 0)
				nbZeros = nbZeros + 1;
			else
				nbZeros = 0;
			end

			isStochFilesLeft = 1;
			l = 1;
			while ( isStochFilesLeft && l < NB_STOCH_FILES_TAKEN)
				itStr = int2str(permutations(l));
				
				fileNameStochastic = strcat(stochasticFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,StochasticStr,fileNameSuffix2,'(',itStr,')',fileNameSuffix3);
				
				fileIDStochastic = fopen(fileNameStochastic, 'r');
				if (fileIDStochastic == -1)
					isStochFilesLeft = 0;
					disp(['End Stochastic : pre=',precisionStr,', nb taken=',int2str(NB_STOCH_FILES_TAKEN),', it max=',itStr]);
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
			disp(strcat('[',precisionStr,'] : Stochastic(',int2str(NB_STOCH_FILES_TAKEN),') = ',num2str(mean(StochasticDiff(index,2,:),3)))); % k*(l-1):((k+1)*l-1),2:3)))));
			disp('-');

			k = k + 1;
		end
	end

	outputFolder = 'data/';
	dlmwrite(strcat(outputFolder,'RNDN_rel_dif_at_it_',int2str(NB_ITERATIONS),'.dat'),RNDNDiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDA_rel_dif_at_it_',int2str(NB_ITERATIONS),'.dat'),RNDADiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDD_rel_dif_at_it_',int2str(NB_ITERATIONS),'.dat'),RNDDDiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDZ_rel_dif_at_it_',int2str(NB_ITERATIONS),'.dat'),RNDZDiff,'\t');
	dlmwrite(strcat(outputFolder,'RNDU_rel_dif_at_it_',int2str(NB_ITERATIONS),'.dat'),RNDUDiff,'\t');
	dlmwrite(strcat(outputFolder,'CADNA_rel_dif_at_it_',int2str(NB_ITERATIONS),'.dat'),CADNADiff,'\t');

	meanValue = mean(					...
		StochasticDiff(  	...
		:, 	... all lines
		2, 	... only the second column (the diff value)
		:) 	... all stochastic runs
		, 3 ); 	% group the third dimension
	dlmwrite(strcat(outputFolder,'STOCHASTIC_rel_dif_at_it_',int2str(NB_ITERATIONS),'(mean).dat'), ...
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

	dlmwrite(strcat(outputFolder,'STOCHASTIC_rel_dif_at_it_',int2str(NB_ITERATIONS),'(deviationUp).dat'), ...
		[ StochasticDiff(:,1), 	... precision
		stdUp	...
		]	...
		);

	dlmwrite(strcat(outputFolder,'STOCHASTIC_rel_dif_at_it_',int2str(NB_ITERATIONS),'(deviationDown).dat'), ...
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
		StochasticStr tmp relDiff meanValue stdValue stdUp stdDown ...
		roundingModeStrings RNDNDiff RNDADiff RNDDDiff RNDZDiff RNDUDiff ...
		RNDAArray RNDDArray RNDZArray RNDUArray relDiffA relDiffZ relDiffD ...
		relDiffN relDiffU;
	% clear RNDNDiff StochasticDiff

	% fileNameFolder = '/home/kito/Dev/Sources/ACSEL/matrice_grad/stochFiles/output';
	% filename = 'output/lorenz_prec=131_mp=200_ni=100000_rm=RNDN_si=10.000000_ro=28.000000_be=2.666700.dat';

end