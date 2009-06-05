dat1<-read.table('population1data.txt', header=T)
dat2<-read.table('population2data.txt', header=T)
dat<-read.table('featurevalues.txt', header=T)

# Plot the distribution of feature values
png("MigrationRate20.png")
plot(dat1, ylim=c(0,8))
points(dat2, ylim=c(0,8), col='blue', xlab="Generation", ylab="Average feature value")
title('Migration rate = 0.20')
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
barplot(rbind(table(hab1), table(hab2)), beside=TRUE, xlab="Feature value", ylab="Frequency")
title('Feature value distribution, d=0.20')
dev.off()
