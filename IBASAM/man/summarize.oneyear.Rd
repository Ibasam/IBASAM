\name{summarize.oneyear}
\alias{summarize.oneyear}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
summarize.oneyear
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
summarize.oneyear(summerpop, winterpop, variables = c("Lf", "gPercF", "gSLmid", "galphaS", paste(c("gFmid", "pFmid"), rep(1:4, each = 2), sep = ""), "gNeutral"))
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{summerpop}{
%%     ~~Describe \code{summerpop} here~~
}
  \item{winterpop}{
%%     ~~Describe \code{winterpop} here~~
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
function (summerpop, winterpop, variables = c("Lf", "gPercF", 
    "gSLmid", "galphaS", paste(c("gFmid", "pFmid"), rep(1:4, 
        each = 2), sep = ""), "gNeutral")) 
{
    rr <- summarize.summer.population(summerpop, variables)
    rr <- summarize.winter.population(winterpop, rr, variables)
    rr
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
