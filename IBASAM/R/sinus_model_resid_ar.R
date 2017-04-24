sinus_model_resid_ar <-
function (m, a, cs, alp, bet, d, nbd) 
{
    error <- numeric(length(d))
    tm <- m + a * sin(2 * pi * (d - cs)/nbd)
    error[1] <- 0
    for (dd in d[-1]) {
        error[dd] <- alp * error[dd - 1] + bet * rnorm(1)
        tm[dd] <- tm[dd] + error[dd]
    }
    return(tm)
}
