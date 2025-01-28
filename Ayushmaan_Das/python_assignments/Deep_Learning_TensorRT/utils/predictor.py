import cv2
import numpy as np

def make_prediction(model, image_path):
    class_labels = [
    'T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
    'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot'
    ]

    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    image_org = image
    image = cv2.resize(image, (28, 28))

    image = image / 255.0

    image = np.expand_dims(image, axis=-1)
    image = np.expand_dims(image, axis=0)

    y_pred = np.argmax(model.predict(image), axis=1)
    return image_org, class_labels[y_pred[0]]