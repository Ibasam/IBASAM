time_tick <-
function (time_step_length) 
{
    return(unlist(.C("time_tick", as.double(time_step_length), 
        as.double(0), PACKAGE = "Ibasam")[[2]]))
}
