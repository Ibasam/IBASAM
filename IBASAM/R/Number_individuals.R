Number_individuals <-
function () 
{
    return(unlist(.C("Number_individuals", as.integer(0), PACKAGE = "Ibasam")))
}
