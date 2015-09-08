stats.population <-
function (population, window = TRUE, plotting = TRUE, titles = "") 
{
    if (nrow(population) > 1) {
        population$AgeRiver <- as.factor(round(population$AgeRiver))
        population$AgeSea <- as.factor(round(population$AgeSea))
        population$Female <- as.factor(population$Female)
        population$Mature <- as.factor(population$Mature)
        population$Smolt <- as.factor(population$Smolt)
        population$Parr <- as.factor(population$Parr)
        population$Returns <- as.factor(population$Returns)
        Ls <- by(population$Lf, population[, c("Parr", "AgeRiver", 
            "AgeSea", "Female", "Mature", "Smolt", "Returns")], 
            mySummary)
        Ws <- by(population$W, population[, c("Parr", "AgeRiver", 
            "AgeSea", "Female", "Mature", "Smolt", "Returns")], 
            mySummary)
        Fs <- by(population$Fat, population[, c("Parr", "AgeRiver", 
            "AgeSea", "Female", "Mature", "Smolt", "Returns")], 
            mySummary)
        dimnams <- dimnames(Ls)
        i <- 1
        ResL <- ResW <- ResF <- matrix(NA, length(dimnams$Returns) * 
            length(dimnams$Parr) * length(dimnams$Smolt) * length(dimnams$Mature) * 
            length(dimnams$Female) * length(dimnams$AgeSea) * 
            length(dimnams$AgeRiver), 6)
        rnames <- c()
        rtake <- c()
        for (RE in 1:length(dimnams$Returns)) {
            for (SM in 1:length(dimnams$Smolt)) {
                for (MA in 1:length(dimnams$Mature)) {
                  for (FE in 1:length(dimnams$Female)) {
                    for (AS in 1:length(dimnams$AgeSea)) {
                      for (AR in 1:length(dimnams$AgeRiver)) {
                        for (PAR in 1:length(dimnams$Parr)) {
                          if (!is.null(Ls[[i]])) {
                            ResL[i, ] <- round(unlist(Ls[[i]]), 
                              3)
                            ResW[i, ] <- round(unlist(Ws[[i]]), 
                              3)
                            ResF[i, ] <- round(unlist(Fs[[i]]), 
                              3)
                            rnames <- c(rnames, paste(ifelse(dimnams$Parr[PAR] == 
                              "1", "P-", ""), dimnams$AgeRiver[AR], 
                              "-", dimnams$AgeSea[AS], ifelse(dimnams$Female[FE] == 
                                "1", "-F", "-M"), ifelse(dimnams$Smolt[SM] == 
                                "1", "-S", ""), ifelse(dimnams$Mature[MA] == 
                                "1", "-Mat", ""), ifelse(dimnams$Returns[RE] == 
                                "0", "", dimnams$Returns[RE]), 
                              sep = ""))
                            rtake <- c(rtake, i)
                          }
                          i <- i + 1
                        }
                      }
                    }
                  }
                }
            }
        }
        Lnames <- paste(mySummarynames, "Ls")
        Wnames <- paste(mySummarynames, "Ws")
        Fnames <- paste(mySummarynames, "Fs")
        ResL <- as.data.frame(ResL[rtake, ])
        ResW <- as.data.frame(ResW[rtake, ])
        ResF <- as.data.frame(ResF[rtake, ])
        colnames(ResL) <- Lnames
        colnames(ResW) <- Wnames
        colnames(ResF) <- Fnames
        rownames(ResL) <- rownames(ResW) <- rownames(ResF) <- rnames
        Res <- as.data.frame(cbind(ResL, ResW, ResF))
        if (plotting) {
            newwindow(window)
            usr <- par("usr")
            on.exit(par(usr))
            if (nrow(ResL) < 20) 
                par(mfrow = c(3, 1))
            write.data.frame(ResL, titles = paste("Lengths -", 
                titles), nmaxrow = 40)
            write.data.frame(ResW, titles = paste("Weights -", 
                titles), nmaxrow = 40)
            write.data.frame(ResF, titles = paste("Fats -", titles), 
                nmaxrow = 40)
        }
    }
    else {
        Res <- NULL
    }
    return(Res)
}
