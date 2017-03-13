\name{draw.plotmath.cell}
\alias{draw.plotmath.cell}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
draw.plotmath.cell
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
draw.plotmath.cell(expr, i, nr, string = NULL)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{expr}{
%%     ~~Describe \code{expr} here~~
}
  \item{i}{
%%     ~~Describe \code{i} here~~
}
  \item{nr}{
%%     ~~Describe \code{nr} here~~
}
  \item{string}{
%%     ~~Describe \code{string} here~~
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
function (expr, i, nr, string = NULL) 
{
    r <- get.r(i, nr)
    c <- get.c(i, nr)
    if (is.null(string)) {
        string <- deparse(expr)
        string <- substr(string, 12, nchar(string) - 1)
    }
    text((2 * (c - 1) + 1), -r, string, col = "grey")
    text((2 * c), -r, expr, adj = c(0.5, 0.5))
    rect((2 * (c - 1) + 0.5), -(r - 0.5), (2 * c + 0.5), -(r + 
        0.5), border = "grey")
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
