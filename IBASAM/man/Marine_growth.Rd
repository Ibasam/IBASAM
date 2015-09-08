\name{Marine_growth}
\alias{Marine_growth}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Marine_growth
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
Marine_growth(meanP, sdP)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{meanP}{
%%     ~~Describe \code{meanP} here~~
}
  \item{sdP}{
%%     ~~Describe \code{sdP} here~~
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
function (meanP, sdP) 
{
    .C("Marine_growth", as.double(meanP), as.double(sdP), PACKAGE = "libIbasam")
    invisible(NULL)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
