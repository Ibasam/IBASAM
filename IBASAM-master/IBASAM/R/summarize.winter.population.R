summarize.winter.population <-
function (population, rr, variables) 
{
    smolt1 <- (population$AgeSea == 0 & population$AgeRiver < 
        2 & population$Smolt == 1)
    smolt2 <- (population$AgeSea == 0 & population$AgeRiver >= 
        2 & population$Smolt == 1)
    rr <- arraybind(rr, summarize.sub.population(population[smolt1, 
        ], variables))
    rr <- arraybind(rr, summarize.sub.population(population[smolt2, 
        ], variables))
    rr
}
