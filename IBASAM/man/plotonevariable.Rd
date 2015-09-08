\name{plotonevariable}
\alias{plotonevariable}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
plotonevariable
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
plotonevariable(fr, vari, group, xax, window = TRUE, ...)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{fr}{
%%     ~~Describe \code{fr} here~~
}
  \item{vari}{
%%     ~~Describe \code{vari} here~~
}
  \item{group}{
%%     ~~Describe \code{group} here~~
}
  \item{xax}{
%%     ~~Describe \code{xax} here~~
}
  \item{window}{
%%     ~~Describe \code{window} here~~
}
  \item{\dots}{
%%     ~~Describe \code{\dots} here~~
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
function (fr, vari, group, xax, window = TRUE, ...) 
{
    newwindow(window)
    plot(xax, fr[2, vari, group, ], type = "l", bty = "n", ylim = range(fr[, 
        vari, group, ], na.rm = TRUE), ...)
    lines(xax, fr[3, vari, group, ], lty = 2)
    lines(xax, fr[1, vari, group, ], lty = 2)
    try(lines(xax, lowess(fr[2, vari, group, ])$y, , lty = 2, 
        col = 2, cex = 2))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
