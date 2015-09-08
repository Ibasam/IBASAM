check_autumn_maturation_ocean <-
function () 
{
    .C("check_autumn_maturation_ocean", PACKAGE = "Ibasam")
    invisible(NULL)
}
