function res = getIndexOfLastNonInfValue(array)
    lastIndex = -1;
    
    NB_INF_CONSIDERED = 10;
    
    nbI = 0;
    k = 1;
    isInfArray = isinf(array);
    while( (nbI < NB_INF_CONSIDERED) && (k < size(isInfArray,1)))
        if ( isInfArray(k) == 1 )
            nbI = nbI + 1;
        else
            nbI = 0;
        end
        k = k + 1;
    end
    
    if (nbI ~= 0) 
        lastIndex = k - NB_INF_CONSIDERED;
    end
    
    res = lastIndex;
end