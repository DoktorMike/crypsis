trn<-read.table('apa.dat');
glmfit<-glm(V9~., data=trn, family=binomial());
tmp<-cbind(trn, predict(glmfit, type="response"));
res<-sqrt(sum((tmp[,9]-tmp[,10])**2))/dim(tmp)[1];
cat(paste('NMSE: ', res, '\n'));

