force_smolt_run <-
function () 
{
    .C("force_smolt_run", PACKAGE = "Ibasam")
    invisible(NULL)
}
