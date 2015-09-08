setup <-
function (filename, envParam, colParam, internal = FALSE) 
{
    empty()
    Reset_environment()
    if (internal) {
        Prepare_environment_file(filename)
    }
    else {
        dat <- read.table(filename)
        Prepare_environment_vectors(dat$V2, dat$V3)
    }
    setup_environment_parameters(envParam)
    setup_collection_parameters(colParam)
    time_tick(90)
}
