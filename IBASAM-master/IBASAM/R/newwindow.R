newwindow <-
function (window) 
{
    winsys <- Sys.info()[1] == "Windows"
    linsys <- Sys.info()[1] == "Linux"
    if (window & winsys) 
        windows()
    if (window & linsys) 
        x11()
}
