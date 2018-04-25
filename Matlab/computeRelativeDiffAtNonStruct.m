function res = computeRelativeDiffAtNonStruct(refArray, testedArray, iterationNumber)
    %%% refArray is a struct with a field data, and tested array is just an array
	res = 0;
	nElements = min(size(refArray.data,1),size(testedArray,1));
    if iterationNumber > nElements
        disp('pouet');
        res = -1;
    else
        nCol = min(size(refArray.data,2),size(testedArray,2));

        for l = 1:nCol
            res = res + abs((testedArray(iterationNumber,l) - refArray.data(iterationNumber,l))/refArray.data(iterationNumber,l))^2;
        end
        res = sqrt(res);

        clear nCol;
    end
    clear nElements;
end
