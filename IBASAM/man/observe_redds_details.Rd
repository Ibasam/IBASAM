\name{observe_redds_details}
\alias{observe_redds_details}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
observe_redds_details
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
observe_redds_details(motherID = 0)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{motherID}{
%%     ~~Describe \code{motherID} here~~
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
function (motherID = 0) 
{
    n <- unlist(.C("n_details_one_redd", as.integer(0), as.integer(motherID), 
        PACKAGE = "libIbasam"))[1]
    if (n > 0) {
        pop <- matrix(unlist(.C("details_one_redd", as.double(1:(n * 
            nColDetailsRedds)), as.integer(motherID), PACKAGE = "libIbasam")[[1]]), 
            ncol = nColDetailsRedds, nrow = n, byrow = TRUE)
        pop <- as.data.frame(pop)
    }
    else {
        pop <- as.data.frame(t(rep(NA, nColDetailsRedds)))
    }
    colnames(pop) <- ColNamesDetailsRedds
    return(pop)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
