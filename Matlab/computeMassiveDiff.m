
fileNameFolder = 'output';
fileNamePrefix = 'lorenz_prec=';
fileNameSuffix1 = '_mp=200_ni=100000_rm=';
fileNameSuffix2 = '_si=10.000000_ro=28.000000_be=2.666700.dat';
RNDNStr = 'RNDN';
StochasticStr = 'STOCHASTIC';

delimiterIn = '\t';
headerlinesIn = 1;

i = 2;
shouldContinue = 1;

referenceFileName = 'lorenzRef_pre=200_rm=RNDN.dat';
refArray = importdata(strcat(fileNameFolder,'/',referenceFileName),delimiterIn,headerlinesIn);

RNDNDiff = [];
StochasticDiff = [];

while ( shouldContinue ) 
	precisionStr = int2str(i);
	fileNameRNDN = strcat(fileNameFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,RNDNStr,fileNameSuffix2);
	fileNameStochastic = strcat(fileNameFolder,'/',fileNamePrefix,precisionStr,fileNameSuffix1,StochasticStr,fileNameSuffix2);

	fileIDRNDN = fopen(fileNameRNDN, 'r');
	fileIDStochastic = fopen(fileNameStochastic, 'r');

	if (fileIDRNDN == -1)
		shouldContinue = 0;
        disp('End RNDN');
        disp(precisionStr);
	elseif (fileIDStochastic == -1)
		shouldContinue = 0;
        disp('End Stochastic');
        disp(precisionStr);
	else
		fclose(fileIDRNDN);
		fclose(fileIDStochastic);
		
		RNDNArray = importdata(fileNameRNDN,delimiterIn,headerlinesIn);
		tmp1 = [computeDiff(refArray,RNDNArray)];
		RNDNDiff = [RNDNDiff;tmp1];

		StochasticArray = importdata(fileNameStochastic,delimiterIn,headerlinesIn);
		tmp2 = [computeDiff(refArray,StochasticArray)];
		StochasticDiff = [StochasticDiff;tmp2];
        
		disp(strcat('[',precisionStr,'] : RNDN       = ',num2str(tmp1)));
		disp(strcat('[',precisionStr,'] : Stochastic = ',num2str(tmp2)));
		disp('-');

		i = i + 1;
	end
end

disp('--------------------------');
disp('RNDN Diff :');
disp(RNDNDiff);
disp('Stochastic Diff :');
disp(StochasticDiff);

disp(mean(RNDNDiff,'omitnan'));
disp(mean(StochasticDiff,'omitnan'));

dlmwrite('RNDN_dif_1.dat',RNDNDiff,'\t');
dlmwrite('STOCHASTIC_dif_1.dat',StochasticDiff,'\t');

clear fileNameFolder fileNamePrefix fileNameSuffix1 fileNameSuffix2 delimiterIn headerlinesIn i shouldContinue fileNameStochastic fileNameRNDN
clear precisionStr fileIDRNDN fileIDStochastic A tmp1 tmp2 refArray referenceFileName RNDNArray RNDNStr StochasticArray StochasticStr tmp
clear RNDNDiff StochasticDiff

% filename = 'output/lorenz_prec=131_mp=200_ni=100000_rm=RNDN_si=10.000000_ro=28.000000_be=2.666700.dat';