\name{append.oneyear}
\alias{append.oneyear}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
append.oneyear
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
append.oneyear(summerpop, winterpop, rr, variables = c("Lf", "gPercF", "gSLmid", "galphaS", paste(c("gFmid", "pFmid"), rep(1:4, each = 2), sep = ""), "gNeutral"))
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{summerpop}{
%%     ~~Describe \code{summerpop} here~~
}
  \item{winterpop}{
%%     ~~Describe \code{winterpop} here~~
}
  \item{rr}{
%%     ~~Describe \code{rr} here~~
}
  \item{variables}{
%%     ~~Describe \code{variables} here~~
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
function (summerpop, winterpop, rr, variables = c("Lf", "gPercF", 
    "gSLmid", "galphaS", paste(c("gFmid", "pFmid"), rep(1:4, 
        each = 2), sep = ""), "gNeutral")) 
{
    nr <- summarize.oneyear(summerpop, winterpop, variables)
    if (length(dim(rr)) > length(dim(nr)) && all(dim(rr)[1:(length(dim(rr)) - 
        1)] == dim(nr))) {
        fr <- arraybind(rr, nr)
    }
    else {
        if (length(dim(rr)) == length(dim(nr)) && all(dim(rr) == 
            dim(nr))) {
            rr <- array(rr, dim = c(dim(rr), 1))
            fr <- arraybind(rr, nr)
        }
        else stop("merging problem")
    }
    return(fr)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
