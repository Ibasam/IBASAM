look_environment_data <-
function () 
{
    nb_day <- recall_nb_day_simulations()
    env <- .C("look_environment_data", as.integer(nb_day), as.double(1:nb_day), 
        as.double(1:nb_day), as.double(1:nb_day), PACKAGE = "Ibasam")
    res <- data.frame(days = env[[2]], Temperature = env[[3]], 
        logFlow = env[[4]])
    return(res)
}
