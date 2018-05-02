function res = getIndexOfLastNonZeroValue(array)
    lastIndex = -1;
    
    NB_ZERO_CONSIDERED = 10;
    
    nbZ = 0;
    k = 1;
    while( (nbZ < NB_ZERO_CONSIDERED) && (k < size(array,1)))
        if ( array(k) == 0 )
            nbZ = nbZ + 1;
        else
            nbZ = 0;
        end
        k = k + 1;
    end
    
    if (nbZ ~= 0) 
        lastIndex = k - NB_ZERO_CONSIDERED;
    end
    
    res = lastIndex;
end