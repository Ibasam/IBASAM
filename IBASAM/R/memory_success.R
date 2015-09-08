memory_success <-
function () 
{
    sizeM <- unlist(.C("memory_success_sizes", as.integer(0:1), 
        PACKAGE = "Ibasam"))
    if (all(sizeM > 0)) {
        pop <- matrix(unlist(.C("memory_success", as.double(1:(sizeM[1] * 
            sizeM[2])), PACKAGE = "Ibasam")), ncol = sizeM[2], 
            nrow = sizeM[1], byrow = TRUE)
        pop <- as.data.frame(pop)
        v <- numeric(nrow(pop))
        sel <- pop[, 1]
        for (i in 1:nrow(pop)) {
            ids <- pop[pop[, c(8, 9)] == pop[i, 1], 1]
            v[i] <- length(unique(ids))
        }
        colnames(pop) <- c("ID", "Female", "AgeRiver", "AgeSea", 
            "DateRepro", "Neggs", "Nemerging", "IDmother", "IDfather", 
            "Year", "Nrepro")
        pop$NsuccessRepro <- v
    }
    else {
        pop <- NA
    }
    return(pop)
}
