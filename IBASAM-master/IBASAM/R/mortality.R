mortality <-
function (time_step_length) 
{
    .C("mortality", as.double(time_step_length), PACKAGE = "Ibasam")
    invisible(NULL)
}
