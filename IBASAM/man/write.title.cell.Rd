\name{write.title.cell}
\alias{write.title.cell}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
write.title.cell
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
write.title.cell(title, r, c, cex = 1)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{title}{
%%     ~~Describe \code{title} here~~
}
  \item{r}{
%%     ~~Describe \code{r} here~~
}
  \item{c}{
%%     ~~Describe \code{c} here~~
}
  \item{cex}{
%%     ~~Describe \code{cex} here~~
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
function (title, r, c, cex = 1) 
{
    text(2 * c - 0.5, -r, title, cex = cex)
    rect((2 * (c - 1) + 0.5), -(r - 0.5), (2 * c + 0.5), -(r + 
        0.5))
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
