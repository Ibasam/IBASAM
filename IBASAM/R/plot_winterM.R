plot_winterM <-
function (winterM, window = TRUE, titles = "", startyear = 0) 
{
    years <- startyear + (1:nrow(winterM))
    newwindow(window)
    plot(years, winterM[, 1], ylab = "smolt NBs", bty = "n", 
        type = "l", ylim = c(0, max(winterM[, 1], na.rm = TRUE)), 
        main = paste("Numbers of smolts through time", titles))
    lines(years, winterM[, 3], lty = 2, col = 2)
    lines(years, winterM[, 5], lty = 3, col = 3)
    legend("topright", legend = c("1+", "2+", "3+"), col = 1:3, 
        lty = 1:3)
    newwindow(window)
    plot(years, winterM[, 2], ylab = "smolt Lf", bty = "n", type = "l", 
        ylim = c(90, 250), main = paste("Sizes of smolts through time", 
            titles))
    lines(years, winterM[, 4], lty = 2, col = 2)
    lines(years, winterM[, 6], lty = 3, col = 3)
    legend("topright", legend = c("1+", "2+", "3+"), col = 1:3, 
        lty = 1:3)
}
