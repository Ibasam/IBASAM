\name{analyse_origins_simple}
\alias{analyse_origins_simple}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
analyse_origins_simple
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
analyse_origins_simple(pop)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{pop}{
%%     ~~Describe \code{pop} here~~
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
function (pop) 
{
    motherS <- colSums(matrix(pop$motherStrat == rep(possibleStrategies, 
        each = nrow(pop)), nrow = nrow(pop)))/nrow(pop)
    fatherS <- colSums(matrix(pop$fatherStrat == rep(possibleStrategies, 
        each = nrow(pop)), nrow = nrow(pop)))/nrow(pop)
    return(list(motherS = motherS, fatherS = fatherS))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
