summarize.sub.population <-
function (subpop, variables) 
{
    array(apply(subpop[, variables], 2, summarize.variable), 
        dim = c(3, length(variables)))
}
