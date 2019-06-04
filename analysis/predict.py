# scipy
import scipy
#print('scipy: %s' % scipy.__version__)
# numpy
import numpy
#print('numpy: %s' % numpy.__version__)
# matplotlib
import matplotlib
#print('matplotlib: %s' % matplotlib.__version__)
# pandas
import pandas
#print('pandas: %s' % pandas.__version__)
# scikit-learn
import sklearn
#print('sklearn: %s' % sklearn.__version__)
# statsmodels
import statsmodels
#print('statsmodels: %s' % statsmodels.__version__)

from pandas.plotting import scatter_matrix
import matplotlib.pyplot as plt
	
#from pandas import Series
from sklearn.metrics import mean_squared_error
from math import sqrt

series = pandas.read_csv('water_quality.csv', header=0)
print(series.describe())
# split data, withholding last 10 data points for validation
split_point = len(series) - 10
dataset, validation = series[0:split_point], series[split_point:]
print('Dataset %d, Validation %d' % (len(dataset), len(validation)))
dataset.to_csv('dataset.csv')
validation.to_csv('validation.csv')

# forecasting model

# prepare data, 50% for testing
X = series.values
#X = X.astype('float32')
train_size = int(len(X) * 0.50)
train, test = X[0:train_size], X[train_size:]

# iterate over time steps in the test dataset
# walk-forward validation
history = [x for x in train]
predictions = list()
for i in range(len(test)):
	# predict
	yhat = history[-1]
	predictions.append(yhat)
	# observation
	obs = test[i]
	history.append(obs)
	#print('>Predicted=%.3f, Expected=%3.f' % (yhat, obs))
# report performance
mse = mean_squared_error(test, predictions)
rmse = sqrt(mse)
print('RMSE: %.3f' % rmse)
	
# box and whisker plots
#series.plot(kind='box', subplots=True, layout=(2,2), sharex=False, sharey=False)
#plt.show()

# histograms
#dataset.hist()
#plt.show()

# scatter plot matrix
scatter_matrix(dataset)
plt.show()
