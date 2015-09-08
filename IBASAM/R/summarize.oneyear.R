summarize.oneyear <-
function (summerpop, winterpop, variables = c("Lf", "gPercF", 
    "gSLmid", "galphaS", paste(c("gFmid", "pFmid"), rep(1:4, 
        each = 2), sep = ""), "gNeutral")) 
{
    rr <- summarize.summer.population(summerpop, variables)
    rr <- summarize.winter.population(winterpop, rr, variables)
    rr
}
