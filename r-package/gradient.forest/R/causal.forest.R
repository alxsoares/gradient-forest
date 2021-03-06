causal.forest <- function(X, Y, W, sample.fraction = 0.5, mtry = ceiling(ncol(X)/3), 
    num.trees = 500, num.threads = NULL, min.node.size = NULL, keep.inbag = FALSE, 
    honesty = TRUE, ci.group.size = 4, precompute.nuisance = TRUE, seed = NULL) {
    
    sparse.data <- as.matrix(0)
    
    if (is.null(mtry)) {
        mtry <- 0
    } else if (!is.numeric(mtry) | mtry < 0) {
        stop("Error: Invalid value for mtry")
    }
    
    verbose <- FALSE
    
    if (is.null(num.threads)) {
        num.threads <- 0
    } else if (!is.numeric(num.threads) | num.threads < 0) {
        stop("Error: Invalid value for num.threads")
    }
    
    if (is.null(min.node.size)) {
        min.node.size <- 0
    } else if (!is.numeric(min.node.size) | min.node.size < 0) {
        stop("Error: Invalid value for min.node.size")
    }
    
    sample.with.replacement <- FALSE
    
    if (!is.logical(keep.inbag)) {
        stop("Error: Invalid value for keep.inbag")
    }
    
    if (!is.numeric(sample.fraction) | sample.fraction <= 0 | sample.fraction > 1) {
        stop("Error: Invalid value for sample.fraction. Please give a value in (0,1].")
    }
    
    if (is.null(seed)) {
        seed <- runif(1, 0, .Machine$integer.max)
    }
    
    split.regularization <- 0
    
    if (!precompute.nuisance) {
        
        input.data <- as.matrix(cbind(X, Y, W))
        
    } else {
        
        forest.Y <- regression.forest(X, Y, sample.fraction = sample.fraction, mtry = mtry, 
            num.trees = min(500, num.trees), num.threads = num.threads, min.node.size = NULL, 
            keep.inbag = FALSE, honesty = TRUE, seed = seed)
        Y.hat = predict(forest.Y)
        
        forest.W <- regression.forest(X, W, sample.fraction = sample.fraction, mtry = mtry, 
            num.trees = min(500, num.trees), num.threads = num.threads, min.node.size = NULL, 
            keep.inbag = FALSE, honesty = TRUE, seed = seed)
        W.hat = predict(forest.W)
        
        input.data <- as.matrix(cbind(X, Y - Y.hat, W - W.hat))
        
    }
    
    
    variable.names <- c(colnames(X), "outcome", "treatment")
    outcome.index.zeroindexed <- ncol(X)
    treatment.index.zeroindexed <- ncol(X) + 1
    instrument.index.zeroindexed <- treatment.index.zeroindexed
    
    no.split.variables <- numeric(0)
    
    forest <- instrumental_train(input.data, outcome.index.zeroindexed, treatment.index.zeroindexed, 
        instrument.index.zeroindexed, sparse.data, variable.names, mtry, num.trees, 
        verbose, num.threads, min.node.size, sample.with.replacement, keep.inbag, 
        sample.fraction, no.split.variables, seed, honesty, ci.group.size, split.regularization)
    
    forest[["ci.group.size"]] <- ci.group.size
    forest[["original.data"]] <- input.data
    class(forest) <- "causal.forest"
    forest
}

predict.causal.forest <- function(forest, newdata = NULL, num.threads = NULL, estimate.variance = FALSE) {
    predict.instrumental.forest(forest, newdata, num.threads, estimate.variance)
}
