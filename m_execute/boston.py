import tensorflow as tf
from tensorflow.keras.datasets import boston_housing
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam

(x_train, y_train), (x_test, y_test) = boston_housing.load_data()

# Normalize the features
mean = x_train.mean(axis=0)
std = x_train.std(axis=0)
x_train = (x_train - mean) / std
x_test = (x_test - mean) / std

#x_test[5] // input for prediction
#y_test[5] // actual value

model = Sequential()
model.add(Dense(128,activation='relu',input_shape = (x_train[0].shape)))
model.add(Dense(64,activation='relu'))
model.add(Dense(32,activation='relu'))
model.add(Dense(1))

model.compile(optimizer=Adam(learning_rate=0.001), loss='mse')

model.fit(x_train, y_train, batch_size=32, epochs=100, verbose=1, validation_data=(x_test,y_test))

loss = model.evaluate(x_test, y_test, verbose=0)
print(f"Mean Squared Error (MSE): {loss:.2f}")

test_input = [[-0.3754937 , -0.48361547, -0.20791668, -0.25683275,  0.23597582,-0.48113631, -0.94641237, -0.67000565, -0.39603557, -0.08965908, 0.32944629,  0.44807713,  0.11720047]]
predicted_value = model.predict(test_input)
print("actual value is :",y_test[4])
print("predicted value is : ",predicted_value)