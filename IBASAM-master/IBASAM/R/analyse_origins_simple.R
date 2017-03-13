analyse_origins_simple <-
function (pop) 
{
    motherS <- colSums(matrix(pop$motherStrat == rep(possibleStrategies, 
        each = nrow(pop)), nrow = nrow(pop)))/nrow(pop)
    fatherS <- colSums(matrix(pop$fatherStrat == rep(possibleStrategies, 
        each = nrow(pop)), nrow = nrow(pop)))/nrow(pop)
    return(list(motherS = motherS, fatherS = fatherS))
}
