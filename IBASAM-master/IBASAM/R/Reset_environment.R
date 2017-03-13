Reset_environment <-
function () 
{
    .C("Reset_environment", PACKAGE = "Ibasam")
    invisible(NULL)
}
