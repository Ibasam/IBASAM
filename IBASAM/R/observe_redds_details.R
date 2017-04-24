observe_redds_details <-
function (motherID = 0) 
{
    n <- unlist(.C("n_details_one_redd", as.integer(0), as.integer(motherID), 
        PACKAGE = "Ibasam"))[1]
    if (n > 0) {
        pop <- matrix(unlist(.C("details_one_redd", as.double(1:(n * 
            nColDetailsRedds)), as.integer(motherID), PACKAGE = "Ibasam")[[1]]), 
            ncol = nColDetailsRedds, nrow = n, byrow = TRUE)
        pop <- as.data.frame(pop)
    }
    else {
        pop <- as.data.frame(t(rep(NA, nColDetailsRedds)))
    }
    colnames(pop) <- ColNamesDetailsRedds
    return(pop)
}
