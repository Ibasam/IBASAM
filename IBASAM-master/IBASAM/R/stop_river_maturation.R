stop_river_maturation <-
function () 
{
    .C("stop_river_maturation", PACKAGE = "Ibasam")
    invisible(NULL)
}
