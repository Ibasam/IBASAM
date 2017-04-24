Prepare_environment_vectors <-
function (temperature, logrelflow) 
{
    n <- length(temperature)
    if (length(logrelflow) == n & is.vector(temperature) & is.vector(logrelflow)) {
        .C("Prepare_environment_vectors", as.double(1:n), as.double(temperature), 
            as.double(logrelflow), as.double(n), PACKAGE = "Ibasam")
        invisible(NULL)
    }
    else {
        return("wrong entries in prepare environment vectors")
    }
}
