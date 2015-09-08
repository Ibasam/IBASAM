random_Scorff_river <-
function (nYears) 
{
    mT <- 12.674299
    aT <- 5.909091
    csT <- 114.780948
    alpT <- 0.95184170929478
    betT <- 0.449967327959108
    mF <- -0.02
    aF <- 1.010139
    csF <- 327.836285
    alpF <- 0.964034622660953
    betF <- 0.118343974744226
    temperatures <- sinus_model_resid_ar(mT, aT, csT, alpT, betT, 
        1:(365 * nYears), 365)
    logrelflow <- sinus_model_resid_ar(mF, aF, csF, alpF, betF, 
        1:(365 * nYears), 365) - 0.2
    temperatures[temperatures < 0] <- 0.01
    logrelflow[logrelflow > 3] <- 3
    logrelflow[logrelflow < -3] <- -3
    return(list(temperatures = temperatures, logrelflow = logrelflow))
}
