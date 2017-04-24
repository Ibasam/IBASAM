check_return <-
function () 
{
    .C("check_return", PACKAGE = "Ibasam")
    invisible(NULL)
}
