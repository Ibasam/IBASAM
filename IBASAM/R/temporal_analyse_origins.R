temporal_analyse_origins <-
function (pop, Years, plotting = FALSE, titles = "") 
{
    results <- array(NA, c(2, length(possibleStrategies), length(Years)))
    for (y in Years) {
        popt <- pop[pop$year == y, ]
        rest <- analyse_origins(popt, plotting = FALSE, complete = FALSE)
        results[, , (1 + y - min(Years))] <- rest
    }
    dimnames(results) <- list(rownames(rest), colnames(rest), 
        as.character(Years))
    if (plotting) {
        plot(Years, results[1, 1, ], type = "l", bty = "l", ylim = c(0, 
            1), ylab = "Strategy %", main = titles)
        lines(Years, results[1, 1, ], lty = 2)
        for (j in 2:length(possibleStrategies)) {
            lines(Years, results[1, j, ], col = j)
            lines(Years, results[2, j, ], col = j, lty = 2)
        }
        legend("topright", legend = c("mother", "father"), lty = c(1, 
            2))
        legend("topleft", legend = as.character(possibleStrategies), 
            lty = 1, col = 1:length(possibleStrategies))
    }
    return(results)
}
