function res = KullbackNonStruct(refArray, testedArray, iterationNumber)
    %disp('Kullback');
	res = 0;
	nElements = min(size(refArray.data,1),size(testedArray,1));
    if iterationNumber > nElements
        disp('pouet1');
        res = -1;
    else
        nCol = min(size(refArray.data,2),size(testedArray,2));

        for l = 1:nCol
% 			disp([num2str(res) '=' num2str(res) '+ abs(' num2str(testedArray.data(iterationNumber,l)) '-' num2str(refArray.data(iterationNumber,l)) '/' num2str(refArray.data(iterationNumber,1)) ')^2']);
% 			disp(['res = ' num2str(abs((testedArray.data(iterationNumber,l) - refArray.data(iterationNumber,l))/refArray.data(iterationNumber,1))^2)]);
            %res = res + abs((testedArray.data(iterationNumber,l) - refArray.data(iterationNumber,l))/refArray.data(iterationNumber,l))^2;
			res = res + abs(testedArray(iterationNumber,l) * log2(abs(testedArray(iterationNumber,l)/refArray.data(iterationNumber,l))));
		end
        %res = sqrt(res);

        clear nCol;
    end
    clear nElements;
end
