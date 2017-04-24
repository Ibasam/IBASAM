\name{plotreplicates}
\alias{plotreplicates}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
plotreplicates
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
plotreplicates(fr, variables = c("Lf", "gPercF", "gSLmid", "galphaS", paste(c("gFmid", "pFmid"), rep(1:4, each = 2), sep = ""), "gNeutral"), window = TRUE, xax = NULL)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{fr}{
%%     ~~Describe \code{fr} here~~
}
  \item{variables}{
%%     ~~Describe \code{variables} here~~
}
  \item{window}{
%%     ~~Describe \code{window} here~~
}
  \item{xax}{
%%     ~~Describe \code{xax} here~~
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
function (fr, variables = c("Lf", "gPercF", "gSLmid", "galphaS", 
    paste(c("gFmid", "pFmid"), rep(1:4, each = 2), sep = ""), 
    "gNeutral"), window = TRUE, xax = NULL) 
{
    frs <- apply(fr, 1:4, mean, na.rm = TRUE)
    plotevolution(frs, variables, window, xax)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
