analyse_origins <-
function (pop, sex = NULL, plotting = TRUE, titles = "", complete = TRUE) 
{
    if (!is.null(sex)) {
        if (sex == 0 | sex == 1) {
            pop <- pop[pop$Female == sex, ]
        }
        else {
            complete <- TRUE
        }
    }
    results <- matrix(unlist(analyse_origins_simple(pop)), nrow = 2, 
        byrow = TRUE)
    if (complete) {
        popt <- pop[pop$Female == 0, ]
        results <- rbind(results, matrix(unlist(analyse_origins_simple(popt)), 
            nrow = 2, byrow = TRUE))
        popt <- pop[pop$Female == 1, ]
        results <- rbind(results, matrix(unlist(analyse_origins_simple(popt)), 
            nrow = 2, byrow = TRUE))
        rownames(results) <- paste(rep(c("all", "males", "females"), 
            each = 2), rep(c("mother", "father"), 3))
        colnames(results) <- as.character(possibleStrategies)
        if (plotting) {
            dotchart(t(results), main = paste(titles, "N=", nrow(pop)))
        }
    }
    else {
        if (plotting) {
            rownames(results) <- c("mother", "father")
            colnames(results) <- as.character(possibleStrategies)
            dotchart(t(results), main = paste(titles, "N=", nrow(pop)))
        }
    }
    return(results)
}
