dat1<-read.table('population1data.txt', header=T)
dat2<-read.table('population2data.txt', header=T)
dat<-read.table('featurevalues.txt', header=T)

# Plot the distribution of feature values
png("MigrationRate20.png")
plot(dat1, ylim=c(0,8), xlab="Generation", ylab="Average phenotype value", pch=19+1, col='black')
points(dat2, ylim=c(0,8), pch=19+1, col='grey')
title('Dispersal rate = 0.20')
dev.off()

# Test if the featureValues of the Habitats are different
myTest<-wilcox.test(dat$Habitat1, dat$Habitat2);

# Plot the distribution of feature values
png("FeatureValDistribution20.png")
boxplot(dat[,2:3])
title('Feature value distribution, d=0.20')
dev.off()

# Plot the distribution of feature values using barplots
png("FeatureValDistributionBarplot20.png")
hab1<-factor(dat$Habitat1, levels=c(0:8))
hab2<-factor(dat$Habitat2, levels=c(0:8))
#barplot(rbind(table(hab1), table(hab2)), beside=TRUE, xlab="Phenotype value", ylab="Frequency", , col=c(0,1))
barplot(rbind(table(hab1), table(hab2)), beside=TRUE, xlab="Phenotype value", ylab="Frequency")
title('Dispersal rate = 0.20')
dev.off()
