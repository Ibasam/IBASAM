proportions.population <-
function (population, window = TRUE, plotting = TRUE, titles = "") 
{
    grilses <- (population$Returns > 0 & population$AgeSea < 
        2)
    MSW <- (population$Returns > 0 & population$AgeSea >= 2)
    OnevsMSWratio <- sum(grilses)/sum(MSW)
    sexratioGrilses <- sum(grilses & population$Female == 0)/sum(grilses & 
        population$Female == 1)
    sexratioMSW <- sum(MSW & population$Female == 0)/sum(MSW & 
        population$Female == 1)
    return(list(OnevsMSWratio = OnevsMSWratio, sexratioGrilses = sexratioGrilses, 
        sexratioMSW = sexratioMSW, nReturns = sum(grilses) + 
            sum(MSW)))
}
