defaultParameters <-
function () 
{
    def <- .C("defaultParameters", as.double(1:17), as.double(1:13), 
        as.double(1:13), as.double(1:13), as.double(1:13), as.double(1:13), 
        as.double(1:93), PACKAGE = "Ibasam")
    names(def) <- c("envParam", "gParam", "parrParam", "smoltsParam", 
        "grilseParam", "mswParam", "colParam")
    return(def)
}
