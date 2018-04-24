function res = computeRelativeDiffAt(refArray, testedArray, iterationNumber) 
	res = 0;
	nElements = min(size(refArray.data,1),size(testedArray.data,1));
    if iterationNumber > nElements
        disp('pouet1');
        res = -1;
    else
        nCol = min(size(refArray.data,2),size(testedArray.data,2));

        for l = 1:nCol
            res = res + abs((testedArray.data(iterationNumber,l) - refArray.data(iterationNumber,l))/refArray.data(iterationNumber,1))^2;
        end
        res = sqrt(res);

        clear nCol;
    end
    clear nElements;
end
