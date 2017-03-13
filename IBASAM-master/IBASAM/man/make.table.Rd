\name{make.table}
\alias{make.table}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
make.table
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
make.table(nr, nc, titles = "")
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{nr}{
%%     ~~Describe \code{nr} here~~
}
  \item{nc}{
%%     ~~Describe \code{nc} here~~
}
  \item{titles}{
%%     ~~Describe \code{titles} here~~
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
function (nr, nc, titles = "") 
{
    plot(c(0, nc * 2 + 1), c(0, -(nr + 1)), type = "n", xlab = "", 
        ylab = "", axes = FALSE)
    text(nc + 0.5, 0, cex = 1.2, titles)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
