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

function res = computeDiff(refArray, testedArray) 
	res = 0;
	nElements = min(size(refArray.data,1),size(testedArray.data,1));
	nCol = min(size(refArray.data,2),size(testedArray.data,2));
	for k = 1:nElements
	    for l = 1:nCol
	        res = res + (refArray.data(k,l) - testedArray.data(k,l))^2;
	    end
    end

    % disp(res);
    
    clear nElements nCol
    
end