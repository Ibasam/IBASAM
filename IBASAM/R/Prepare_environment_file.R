Prepare_environment_file <-
function (filename) 
{
    .C("Prepare_environment_file", as.character(filename), PACKAGE = "Ibasam")
    invisible(NULL)
}
