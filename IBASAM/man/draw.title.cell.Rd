\name{draw.title.cell}
\alias{draw.title.cell}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
draw.title.cell
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
draw.title.cell(title, i, nr)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{title}{
%%     ~~Describe \code{title} here~~
}
  \item{i}{
%%     ~~Describe \code{i} here~~
}
  \item{nr}{
%%     ~~Describe \code{nr} here~~
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
function (title, i, nr) 
{
    r <- get.r(i, nr)
    c <- get.c(i, nr)
    text(2 * c - 0.5, -r, title)
    rect((2 * (c - 1) + 0.5), -(r - 0.5), (2 * c + 0.5), -(r + 
        0.5))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
