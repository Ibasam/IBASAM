summarize.summer.population <-
function (population, variables) 
{
    grilses <- (population$Returns == 1 & population$AgeSea < 
        2)
    MSW <- (population$Returns >= 1 & population$AgeSea >= 2)
    Parrs0 <- (population$AgeSea == 0 & population$AgeRiver < 
        1)
    Parrs1 <- (population$AgeSea == 0 & population$AgeRiver >= 
        1)
    rr <- summarize.sub.population(population[grilses, ], variables)
    rr <- array(rr, dim = c(dim(rr), 1))
    rr <- arraybind(rr, summarize.sub.population(population[MSW, 
        ], variables))
    rr <- arraybind(rr, summarize.sub.population(population[Parrs0, 
        ], variables))
    rr <- arraybind(rr, summarize.sub.population(population[Parrs1, 
        ], variables))
    rr
}
