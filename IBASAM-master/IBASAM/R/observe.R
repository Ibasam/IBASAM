observe <-
function () 
{
    n <- Number_individuals()
    if (n > 0) {
        pop <- matrix(unlist(.C("observe", as.double(1:(n * nColObserve)), 
            PACKAGE = "Ibasam")), ncol = nColObserve, nrow = n, 
            byrow = TRUE)
        pop <- as.data.frame(pop)
    }
    else {
        pop <- as.data.frame(t(rep(NA, nColObserve)))
    }
    colnames(pop) <- ColNames
    return(pop)
}
