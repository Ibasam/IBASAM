add_eggs <-
function (N, Nredds) 
{
    .C("add_eggs", as.integer(N), as.integer(Nredds), PACKAGE = "Ibasam")
    invisible(NULL)
}
