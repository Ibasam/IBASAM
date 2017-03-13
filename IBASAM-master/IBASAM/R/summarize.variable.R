summarize.variable <-
function (x) 
{
    quantile(x, c(0.025, 0.5, 0.975), na.rm = TRUE)
}
