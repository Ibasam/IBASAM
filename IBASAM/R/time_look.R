time_look <-
function () 
{
    return(unlist(.C("time_look", as.double(1:2), PACKAGE = "Ibasam")))
}
