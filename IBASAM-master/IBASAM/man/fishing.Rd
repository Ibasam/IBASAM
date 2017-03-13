\name{fishing}
\alias{fishing}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
fishing
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
fishing(fishParam)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{fishParam}{
%%     ~~Describe \code{fishParam} here~~
}
}
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
function (fishParam) 
{
    npop <- Number_individuals()
    if (npop > 0) {
        .C("fishing", as.double(fishParam), PACKAGE = "libIbasam")
        n <- unlist(.C("N_fished", as.integer(0), PACKAGE = "libIbasam"))
        if (n > 0) {
            pop <- matrix(unlist(.C("observe_fished", as.double(1:(n * 
                nColObserve)), PACKAGE = "libIbasam")), ncol = nColObserve, 
                nrow = n, byrow = TRUE)
            pop <- as.data.frame(pop)
        }
        else {
            pop <- as.data.frame(t(rep(NA, nColObserve)))
        }
    }
    else {
        pop <- as.data.frame(t(rep(NA, nColObserve)))
    }
    colnames(pop) <- ColNames
    return(pop)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
