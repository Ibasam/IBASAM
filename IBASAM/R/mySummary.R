mySummary <-
function (x) 
{
    mx <- mean(x)
    nx <- length(x)
    sdx <- sd(x)
    qsx <- quantile(x, c(0.025, 0.5, 0.975))
    return(c(mx, nx, sdx, qsx))
}
