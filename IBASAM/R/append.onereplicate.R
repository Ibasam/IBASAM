append.onereplicate <-
function (onerepl, allrepl) 
{
    if (length(dim(allrepl)) > length(dim(onerepl)) && all(dim(allrepl)[1:(length(dim(allrepl)) - 
        1)] == dim(onerepl))) {
        fr <- arraybind(allrepl, onerepl)
    }
    else {
        if (length(dim(allrepl)) == length(dim(onerepl)) && all(dim(allrepl) == 
            dim(onerepl))) {
            allrepl <- array(allrepl, dim = c(dim(allrepl), 1))
            fr <- arraybind(allrepl, onerepl)
        }
        else stop("merging problem")
    }
    return(fr)
}
