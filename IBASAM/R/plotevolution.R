plotevolution <-
function (fr, variables = c("Lf", "gPercF", "gSLmid", "galphaS", 
    paste(c("gFmid", "pFmid"), rep(1:4, each = 2), sep = ""), 
    "gNeutral"), window = TRUE, xax = NULL) 
{
    nyr <- dim(fr)[4]
    nvar <- length(variables)
    nsub <- 6
    if (is.null(xax)) 
        xax <- 1:nyr
    for (v in 1:nvar) for (su in 1:nsub) plotonevariable(fr, 
        v, su, xax, window, main = paste(variables[v], groupnames[su]), 
        xlab = "Years", ylab = variables[v])
}
