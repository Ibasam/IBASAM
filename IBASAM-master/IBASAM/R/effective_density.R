effective_density <-
function () 
{
    return(unlist(.C("effective_density", as.double(0), PACKAGE = "Ibasam")))
}
