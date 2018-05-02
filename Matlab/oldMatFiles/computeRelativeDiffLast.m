function res = computeRelativeDiffLast(refArray, testedArray) 
	res = 0;
	nElements = min(size(refArray.data,1),size(testedArray.data,1));
	nCol = min(size(refArray.data,2),size(testedArray.data,2));
	%for k = 1:nElements
        %for l = 1:nCol
        %    res = res + abs( testedArray.data(k,l) - refArray.data(k,l) ) / abs(refArray.data(k,l));
        %end
	%end
	
  	for l = 1:nCol
            res = res + (testedArray.data(500,l) - refArray.data(500,l))^2;
        end
	
	res = sqrt(res);
	%res = abs( testedArray.data(nElements,nCol) - refArray.data(nElements,nCol) ) / abs(refArray.data(nElements,nCol))

    % isnTmp = isnan([res]);
   % disp('test');
    %if isnan(res)
    %    disp(res);
    %    disp(' is Not a Number');
    %else
       % disp(' is a number');
    %end
    
    clear nElements nCol
    
end
