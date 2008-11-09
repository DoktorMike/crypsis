library(ROCR);

trn<-read.table('generated_data.dat');
glmfit<-glm(V9~., data=trn, family=binomial());
pred<-predict(glmfit, type="response");
trg<-trn[,9];
#tmp<-cbind(trn, predict(glmfit, type="response"));
#res<-sqrt(sum((tmp[,9]-tmp[,10])**2))/dim(tmp)[1];
#cat(paste('NMSE: ', res, '\n'));

preds<-prediction(pred, trg);
perf<-performance(preds, measure='auc');
#perf<-performance(preds, measure='rmse');
val<-unclass(attr(perf, 'y.values'))[[1]];
cat(paste('AUC: ', val, '\n'));

