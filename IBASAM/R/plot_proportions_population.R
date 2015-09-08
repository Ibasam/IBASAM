plot_proportions_population <-
function (ratios, window = TRUE, titles = "", startyear = 0) 
{
    years <- startyear + (1:nrow(ratios))
    newwindow(window)
    plot(years, ratios[, 1], type = "l", ylab = "ratio", bty = "l", 
        main = paste("1 vs MSW through time", titles))
    newwindow(window)
    plot(years, ratios[, 2], type = "l", ylab = "ratio", bty = "l", 
        main = paste("sexratio Grilses through time", titles))
    newwindow(window)
    plot(years, ratios[, 3], type = "l", ylab = "ratio", bty = "l", 
        main = paste("sexratio MSW through time", titles))
    newwindow(window)
    plot(years, ratios[, 4], type = "l", ylab = "Number", bty = "l", 
        main = paste("number of returns through time", titles))
}
