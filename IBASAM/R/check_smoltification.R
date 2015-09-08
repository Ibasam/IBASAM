check_smoltification <-
function () 
{
    .C("check_smoltification", PACKAGE = "Ibasam")
    invisible(NULL)
}
