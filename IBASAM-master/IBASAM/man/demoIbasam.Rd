\name{demoIbasam}
\alias{demoIbasam}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
demoIbasam
}
\description{
%%  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
demoIbasam(nYears, plotting = TRUE, window = FALSE, returning = FALSE, success = TRUE, empty = TRUE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{nYears}{
%%     ~~Describe \code{nYears} here~~
}
  \item{plotting}{
%%     ~~Describe \code{plotting} here~~
}
  \item{window}{
%%     ~~Describe \code{window} here~~
}
  \item{returning}{
%%     ~~Describe \code{returning} here~~
}
  \item{success}{
%%     ~~Describe \code{success} here~~
}
  \item{empty}{
%%     ~~Describe \code{empty} here~~
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
function (nYears, plotting = TRUE, window = FALSE, returning = FALSE, 
    success = TRUE, empty = TRUE) 
{
    empty()
    def <- defaultParameters()
    mm <- random_Scorff_river(nYears + 1)
    Reset_environment()
    Prepare_environment_vectors(mm$temperatures, mm$logrelflow)
    setup_environment_parameters(def$envParam)
    setup_collection_parameters(def$colParam)
    time_tick(90)
    add_individuals(def$gParam)
    add_individuals(def$parrParam)
    add_individuals(def$smoltsParam)
    go_summer()
    popo <- observe()
    add_individuals(def$grilseParam)
    add_individuals(def$mswParam)
    go_winter()
    popa <- observe()
    if (returning || success) {
        results <- observe()
    }
    ratios <- matrix(NA, nrow = nYears, ncol = 4)
    winterM <- matrix(NA, nrow = nYears, ncol = 6)
    summerM <- matrix(NA, nrow = nYears, ncol = 18)
    ally <- summarize.oneyear(popo, popa)
    sptm <- NULL
    for (y in 1:nYears) {
        ptm <- proc.time()
        spring()
        summer()
        popo <- observe()
        if (returning || success) {
            results <- rbind(results, popo)
        }
        ratios[y, ] <- unlist(proportions.population(popo))
        summerM[y, ] <- unlist(important.indicator.summer.population(popo))
        autumn()
        winter()
        popa <- observe()
        if (returning || success) {
            results <- rbind(results, popa)
        }
        winterM[y, ] <- unlist(important.indicator.winter.population(popa))
        ally <- append.oneyear(popo, popa, ally)
        sptm <- rbind(sptm, proc.time() - ptm)
    }
    if (plotting) {
        op <- par(mfrow = c(2, 2))
        plot_proportions_population(ratios, window = window)
        plot_winterM(winterM, window = window)
        plot_summerM(summerM, window = window)
        plotevolution(ally, window = window)
        par(mfrow = c(2, 1))
        if (success) {
            newwindow(window)
            suc <- temporal_analyse_origins(results, 1:nYears, 
                plotting = plotting, titles = "Strategy success through time")
        }
        newwindow(window)
        plot(ts(sptm[, 1]), main = "CPU time needed per year", 
            ylab = "seconds", xlab = "years", bty = "l", sub = paste("Total:", 
                round(sum(sptm[, 1]), 3)))
        lines(lowess(sptm[, 1]), col = 2, lty = 2)
        par(op)
    }
    if (returning) {
        return(results)
    }
    else {
        invisible(NULL)
    }
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ misc }
\keyword{ utilities }
\keyword{ programming }
