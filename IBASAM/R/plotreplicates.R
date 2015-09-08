plotreplicates <-
function (fr, variables = c("Lf", "gPercF", "gSLmid", "galphaS", 
    paste(c("gFmid", "pFmid"), rep(1:4, each = 2), sep = ""), 
    "gNeutral"), window = TRUE, xax = NULL) 
{
    frs <- apply(fr, 1:4, mean, na.rm = TRUE)
    plotevolution(frs, variables, window, xax)
}
