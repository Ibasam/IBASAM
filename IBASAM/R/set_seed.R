set_seed <-
function (seed = NULL) 
{
    if (is.null(seed)) 
        seed = round(runif(1, 1, 1000))
    .C("set_seed", as.integer(seed), PACKAGE = "Ibasam")
    invisible(NULL)
}
