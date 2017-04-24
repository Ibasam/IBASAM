empty_memory_success <-
function () 
{
    .C("empty_memory_success", PACKAGE = "Ibasam")
    invisible(NULL)
}
