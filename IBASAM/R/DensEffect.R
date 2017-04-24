DensEffect <-
function (time_step_length, effDens) 
{
    return(unlist(.C("DensEffect", as.double(time_step_length), 
        as.double(effDens), as.double(0), PACKAGE = "Ibasam")[[3]]))
}
