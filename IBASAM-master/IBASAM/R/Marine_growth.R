Marine_growth <-
function (meanP, sdP) 
{
    .C("Marine_growth", as.double(meanP), as.double(sdP), PACKAGE = "Ibasam")
    invisible(NULL)
}
