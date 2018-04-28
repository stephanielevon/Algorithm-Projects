#! /usr/bin/Rscript

library(ggplot2)

data <- read.table(file="stats.txt",header=TRUE,sep="\t")
pdf(file="stat.pdf",width=14,height=6)
ggplot(data,aes(y=time,x=as.character(factor(size)),fill=parameter)) + geom_boxplot()
dev.off()
