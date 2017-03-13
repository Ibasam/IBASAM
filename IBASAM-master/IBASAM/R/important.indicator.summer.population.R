important.indicator.summer.population <-
function (population) 
{
    grilses <- (population$Returns == 1 & population$AgeSea < 
        2)
    MSW <- (population$Returns == 1 & population$AgeSea >= 2)
    Mreturns <- (population$Returns > 1 & population$AgeSea >= 
        2)
    Parrs0imm <- (population$AgeSea == 0 & population$AgeRiver < 
        1 & population$Mature == 0)
    Parrs0mat <- (population$AgeSea == 0 & population$AgeRiver < 
        1 & population$Mature == 1)
    Parrs1pimm <- (population$AgeSea == 0 & population$AgeRiver >= 
        1 & population$Mature == 0)
    Parrs1pmat <- (population$AgeSea == 0 & population$AgeRiver >= 
        1 & population$Mature == 1)
    return(list(grilsesNB = sum(grilses), grilsesLf = mean(population[grilses, 
        "Lf"]), MSWNB = sum(MSW), MSWLf = mean(population[MSW, 
        "Lf"]), MreturnsNB = sum(Mreturns), MreturnsLf = mean(population[Mreturns, 
        "Lf"]), Parrs0immNB = sum(Parrs0imm), Parrs0immLf = mean(population[Parrs0imm, 
        "Lf"]), Parrs0matNB = sum(Parrs0mat), Parrs0matLf = mean(population[Parrs0mat, 
        "Lf"]), Parrs1pimmNB = sum(Parrs1pimm), Parrs1pimmLf = mean(population[Parrs1pimm, 
        "Lf"]), Parrs1pmatNB = sum(Parrs1pmat), Parrs1pmatLf = mean(population[Parrs1pmat, 
        "Lf"]), WiniParr0imm = mean(population[Parrs0imm, "Wini"]), 
        WiniParr0mat = mean(population[Parrs0mat, "Wini"]), spGRgrilses = mean(population[grilses, 
            "SpecificGR"]), spGRMSW = mean(population[MSW, "SpecificGR"])))
}
