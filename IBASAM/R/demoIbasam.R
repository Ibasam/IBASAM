demoIbasam <-
function (nYears, CC_Temp, CC_Amp, plotting = TRUE, window = FALSE, returning = FALSE, 
    success = TRUE, empty = TRUE) 
{
    empty()
    def <- defaultParameters()
    mm <- river_climate_model(nYears + 1, CC_Temp, CC_Amp)
    Reset_environment()
    Prepare_environment_vectors(mm$temperatures, mm$logrelflow)
    setup_environment_parameters(def$envParam)
    setup_collection_parameters(def$colParam)
    time_tick(90)
    add_individuals(def$gParam)
    add_individuals(def$parrParam)
    add_individuals(def$smoltsParam)
    go_summer()
    popo <- observe()
    add_individuals(def$grilseParam)
    add_individuals(def$mswParam)
    go_winter()
    popa <- observe()
    if (returning || success) {
        results <- observe()
    }
    ratios <- matrix(NA, nrow = nYears, ncol = 4)
    winterM <- matrix(NA, nrow = nYears, ncol = 6)
    summerM <- matrix(NA, nrow = nYears, ncol = 18)
    ally <- summarize.oneyear(popo, popa)
    sptm <- NULL
    for (y in 1:nYears) {
        ptm <- proc.time()
        spring()
        summer()
        popo <- observe()
        if (returning || success) {
            results <- rbind(results, popo)
        }
        ratios[y, ] <- unlist(proportions.population(popo))
        summerM[y, ] <- unlist(important.indicator.summer.population(popo))
        autumn()
        winter()
        popa <- observe()
        if (returning || success) {
            results <- rbind(results, popa)
        }
        winterM[y, ] <- unlist(important.indicator.winter.population(popa))
        ally <- append.oneyear(popo, popa, ally)
        sptm <- rbind(sptm, proc.time() - ptm)
    }
    if (plotting) {
        op <- par(mfrow = c(2, 2))
        plot_proportions_population(ratios, window = window)
        plot_winterM(winterM, window = window)
        plot_summerM(summerM, window = window)
        plotevolution(ally, window = window)
        par(mfrow = c(2, 1))
        if (success) {
            newwindow(window)
            suc <- temporal_analyse_origins(results, 1:nYears, 
                plotting = plotting, titles = "Strategy success through time")
        }
        newwindow(window)
        plot(ts(sptm[, 1]), main = "CPU time needed per year", 
            ylab = "seconds", xlab = "years", bty = "l", sub = paste("Total:", 
                round(sum(sptm[, 1]), 3)))
        lines(lowess(sptm[, 1]), col = 2, lty = 2)
        par(op)
    }
    if (returning) {
        return(list(results,mm))
    }
    else {
        invisible(NULL)
    }
}
