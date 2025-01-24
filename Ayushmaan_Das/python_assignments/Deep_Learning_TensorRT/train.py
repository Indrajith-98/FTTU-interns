import tensorflow as tf
from sklearn.metrics import f1_score
import numpy as np

from resnet34 import build_resnet_34
from utils.plot_metrics import plot_metrics
from utils.predictor import make_prediction

fashion_mnist = tf.keras.datasets.fashion_mnist
(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()

x_train = x_train / 255.0
x_test = x_test / 255.0
x_train = np.expand_dims(x_train, axis=-1)
x_test = np.expand_dims(x_test, axis=-1)


num_classes = 10
input_shape = x_train.shape[1:]

model = build_resnet_34(input_shape, num_classes)

model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
print(model.summary())

early_stopping = tf.keras.callbacks.EarlyStopping(monitor='val_loss', patience=5, restore_best_weights=True)
history = model.fit(x_train, y_train, validation_split=0.1, epochs=50, batch_size=64, callbacks=[early_stopping])

model.save('resnet34_fashion_mnist.h5')

y_pred = np.argmax(model.predict(x_test), axis=1)

f1 = f1_score(y_test, y_pred, average='weighted')
print(f"F1 SCORE: {f1:.4f}")

plot_metrics(history=history)

image, prediction = make_prediction(model, 'test.png')