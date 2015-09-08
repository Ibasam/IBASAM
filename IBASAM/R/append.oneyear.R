append.oneyear <-
function (summerpop, winterpop, rr, variables = c("Lf", "gPercF", 
    "gSLmid", "galphaS", paste(c("gFmid", "pFmid"), rep(1:4, 
        each = 2), sep = ""), "gNeutral")) 
{
    nr <- summarize.oneyear(summerpop, winterpop, variables)
    if (length(dim(rr)) > length(dim(nr)) && all(dim(rr)[1:(length(dim(rr)) - 
        1)] == dim(nr))) {
        fr <- arraybind(rr, nr)
    }
    else {
        if (length(dim(rr)) == length(dim(nr)) && all(dim(rr) == 
            dim(nr))) {
            rr <- array(rr, dim = c(dim(rr), 1))
            fr <- arraybind(rr, nr)
        }
        else stop("merging problem")
    }
    return(fr)
}
