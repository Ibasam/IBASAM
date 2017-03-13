important.indicator.winter.population <-
function (population) 
{
    smolt1 <- (population$AgeSea == 0 & population$AgeRiver < 
        2 & population$Smolt == 1)
    smolt2 <- (population$AgeSea == 0 & population$AgeRiver >= 
        2 & population$AgeRiver < 3 & population$Smolt == 1)
    smolt3 <- (population$AgeSea == 0 & population$AgeRiver >= 
        3 & population$Smolt == 1)
    return(list(smolt1NB = sum(smolt1), smolt1Lf = mean(population[smolt1, 
        "Lf"]), smolt2NB = sum(smolt2), smolt2Lf = mean(population[smolt2, 
        "Lf"]), smolt3NB = sum(smolt3), smolt3Lf = mean(population[smolt3, 
        "Lf"])))
}
