% % Generate random data from a uniform distribution and calculate the mean.
% % Plot the data and the mean.
%  
% n = 50;            % 50 data points
% r = rand(n,1);
% plot(r)
%  
% % Draw a line from (0,m) to (n,m)
% m = mean(r);
% hold on
% plot([0,n],[m,m])
% hold off
% title('Mean of Random Uniform Data')
difRNDN = 0;
difStochastic = 0;
refArray = table2array(lorentzRefpre200rmRNDN);
RNDNArray = table2array(lorenzprec13mp200ni100000rmRNDNsi10);
StochasticArray = table2array(lorenzprec13mp200ni100000rmSTOCHASTICsi10);
nElements = size(refArray,1);
nCol = size(refArray,2);
for k = nElements
    for l = 1:nCol
        difStochastic = difStochastic + (refArray(k,l) - StochasticArray(k,l))^2;
        difRNDN = difRNDN + (refArray(k,l) - RNDNArray(k,l))^2;
    end
end

disp(difStochastic);
disp(difRNDN);
