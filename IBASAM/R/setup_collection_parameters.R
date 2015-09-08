setup_collection_parameters <-
function (colParam) 
{
    .C("setup_collection_parameters", as.double(colParam), PACKAGE = "Ibasam")
    invisible(NULL)
}
