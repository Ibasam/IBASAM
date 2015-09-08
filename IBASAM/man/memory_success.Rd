\name{memory_success}
\alias{memory_success}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
memory_success
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
memory_success()
}
%- maybe also 'usage' for other objects documented here.
\details{
%%  ~~ If necessary, more details than the description above ~~
}
\value{
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
%% ...
}
\references{
%% ~put references to the literature/web site here ~
}
\author{
Cyril Piou
}
\note{
%%  ~~further notes~~
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\seealso{
%% ~~objects to See Also as \code{\link{help}}, ~~~
}
\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function () 
{
    sizeM <- unlist(.C("memory_success_sizes", as.integer(0:1), 
        PACKAGE = "libIbasam"))
    if (all(sizeM > 0)) {
        pop <- matrix(unlist(.C("memory_success", as.double(1:(sizeM[1] * 
            sizeM[2])), PACKAGE = "libIbasam")), ncol = sizeM[2], 
            nrow = sizeM[1], byrow = TRUE)
        pop <- as.data.frame(pop)
        v <- numeric(nrow(pop))
        sel <- pop[, 1]
        for (i in 1:nrow(pop)) {
            ids <- pop[pop[, c(8, 9)] == pop[i, 1], 1]
            v[i] <- length(unique(ids))
        }
        colnames(pop) <- c("ID", "Female", "AgeRiver", "AgeSea", 
            "DateRepro", "Neggs", "Nemerging", "IDmother", "IDfather", 
            "Year", "Nrepro")
        pop$NsuccessRepro <- v
    }
    else {
        pop <- NA
    }
    return(pop)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
