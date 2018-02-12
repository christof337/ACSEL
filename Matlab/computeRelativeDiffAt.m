function res = computeRelativeDiffAt(refArray, testedArray, iterationNumber) 
	res = 0;
	nElements = min(size(refArray.data,1),size(testedArray.data,1));
    if iterationNumber > nElements
        res = -1;
    else
        nCol = min(size(refArray.data,2),size(testedArray.data,2));

        for l = 1:nCol
            res = res + (testedArray.data(iterationNumber,l) - refArray.data(iterationNumber,l))^2;
        end
        res = sqrt(res);

        clear nCol;
    end
    clear nElements;
end
