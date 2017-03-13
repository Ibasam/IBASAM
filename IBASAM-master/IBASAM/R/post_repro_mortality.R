post_repro_mortality <-
function () 
{
    .C("post_repro_mortality", PACKAGE = "Ibasam")
    invisible(NULL)
}
