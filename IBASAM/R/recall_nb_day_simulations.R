recall_nb_day_simulations <-
function () 
{
    return(unlist(.C("recall_nb_day_simulations", as.double(0), 
        PACKAGE = "Ibasam")))
}
