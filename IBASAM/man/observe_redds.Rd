\name{observe_redds}
\alias{observe_redds}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
observe_redds
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
observe_redds()
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
    n <- unlist(.C("length_observe_redds", as.integer(0), PACKAGE = "libIbasam"))
    if (n > 0) {
        pop <- matrix(unlist(.C("observe_redds", as.double(1:(n * 
            nColObserveRedds)), PACKAGE = "libIbasam")), ncol = nColObserveRedds, 
            nrow = n, byrow = TRUE)
        pop <- as.data.frame(pop)
    }
    else {
        pop <- as.data.frame(t(rep(NA, nColObserveRedds)))
    }
    colnames(pop) <- ColNamesRedds
    return(pop)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
