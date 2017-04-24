reinitialize_salmon_maturation <-
function () 
{
    .C("reinitialize_salmon_maturation", PACKAGE = "Ibasam")
    invisible(NULL)
}
