fishing <-
function (fishParam) 
{
    npop <- Number_individuals()
    if (npop > 0) {
        .C("fishing", as.double(fishParam), PACKAGE = "Ibasam")
        n <- unlist(.C("N_fished", as.integer(0), PACKAGE = "Ibasam"))
        if (n > 0) {
            pop <- matrix(unlist(.C("observe_fished", as.double(1:(n * 
                nColObserve)), PACKAGE = "Ibasam")), ncol = nColObserve, 
                nrow = n, byrow = TRUE)
            pop <- as.data.frame(pop)
        }
        else {
            pop <- as.data.frame(t(rep(NA, nColObserve)))
        }
    }
    else {
        pop <- as.data.frame(t(rep(NA, nColObserve)))
    }
    colnames(pop) <- ColNames
    return(pop)
}
