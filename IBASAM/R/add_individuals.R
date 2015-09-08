add_individuals <-
function (gParam) 
{
    .C("add_individuals", as.double(gParam), PACKAGE = "Ibasam")
    invisible(NULL)
}
