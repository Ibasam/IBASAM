reinitialize_parr_maturation <-
function () 
{
    .C("reinitialize_parr_maturation", PACKAGE = "Ibasam")
    invisible(NULL)
}
