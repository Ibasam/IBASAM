\name{arraybind}
\alias{arraybind}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
arraybind
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
arraybind(x, y = NULL)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{
%%     ~~Describe \code{x} here~~
}
  \item{y}{
%%     ~~Describe \code{y} here~~
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
function (x, y = NULL) 
{
    if (!is.null(y)) {
        y <- as.vector(unlist(y))
        tm <- c(as.vector(x), y)
        dix <- dim(x)
        dit <- dix
        w <- length(dix)
        dit[w] <- dix[w] + 1
        if (length(y) < prod(dit[-w])) 
            warning("Recycling x at the end of arraybind(x,y)")
        if (length(y) > prod(dit[-w])) 
            warning("Cutting y at the end of arraybind(x,y)")
        tm <- array(tm, dim = dit)
        return(tm)
    }
    else {
        return(x)
    }
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
