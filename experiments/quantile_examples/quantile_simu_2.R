set.seed(1234)

rm(list = ls())

setwd("~/git/split-relabel/experiments/quantile_examples")

library(quantregForest)
library(gradient.forest)

p = 40
n = 2000
JMP = 0.8

ticks = 1001
X.test = matrix(0, ticks, p)
X.test[,1] = seq(-1, 1, length.out = ticks)
X.test.df = data.frame(X=X.test)

X = matrix(2 * runif(n * p) - 1, n, p)
Y = rnorm(n) + JMP * (X[,1] > 0)
D = data.frame(X=X, Y=Y)

qrf.meinshausen = quantregForest(X, Y, mtry=p, nodesize=10, replace=FALSE)
preds.meinshausen = predict(qrf.meinshausen, X.test, quantiles = c(0.1, 0.5, 0.9))

qrf.grad = quantile.forest(X, Y, quantiles = c(0.1, 0.5, 0.9), mtry=p, min.node.size = 10, sample.fraction=0.632, num.trees=500)
preds.grad = predict(qrf.grad, X.test.df, quantiles = c(0.1, 0.5, 0.9))

preds.truth = cbind(-qnorm(0.9) + JMP * (X.test[,1] > 0),
                    JMP * (X.test[,1] > 0),
                    qnorm(0.9) + JMP * (X.test[,1] > 0)) 

pdf("quantile_plot_shift_n2k_p40.pdf")

pardef = par(mar = c(5, 4, 4, 2) + 0.5, cex.lab = 1.5, cex.axis = 1.5, cex.sub = 1.5)
plot(NA, NA, xlim = c(-1, 1), ylim = range(preds.meinshausen, preds.grad, preds.truth), xlab = "X", ylab = "Y")

lines(X.test[,1], preds.meinshausen[,1], col = 4, lwd = 2, lty = 2)
lines(X.test[,1], preds.meinshausen[,2], col = 4, lwd = 2, lty = 1)
lines(X.test[,1], preds.meinshausen[,3], col = 4, lwd = 2, lty = 2)

lines(X.test[,1], preds.grad[,1], col = 2, lwd = 2, lty = 2)
lines(X.test[,1], preds.grad[,2], col = 2, lwd = 2, lty = 1)
lines(X.test[,1], preds.grad[,3], col = 2, lwd = 2, lty = 2)

lines(X.test[,1], preds.truth[,1], col = 1, lwd = 2, lty = 2)
lines(X.test[,1], preds.truth[,2], col = 1, lwd = 2, lty = 1)
lines(X.test[,1], preds.truth[,3], col = 1, lwd = 2, lty = 2)

legend("topleft", c("truth", "quantregForest", "split-relabel"), lwd = 2, col = c(1, 4, 2), cex=1.5)

par=pardef
dev.off()
