# Pytorch-Resnet9-CIFAR10
ResNet-9, a lightweight convolutional neural network, was trained on the CIFAR-10 dataset using PyTorch, achieving 90% validation accuracy. CIFAR-10, a dataset of 60,000 32x32 color images across 10 classes, was preprocessed with normalization and data augmentation techniques like random cropping and flipping to enhance generalization.<br>

## About Dataset
CIFAR-10  is an established computer-vision dataset used for object recognition. It is a subset of the 80
 million tiny images dataset and consists of 60,000 32x32 color images containing one of 10 object classes, 
 with 6000 images per class. It was collected by Alex Krizhevsky, Vinod Nair, and Geoffrey Hinton.

 ![image](https://github.com/user-attachments/assets/bfa7ea73-d82f-4d9d-bb6e-6d31fe5a156b)

## Data Transformation (Data Normalisation and Data Augmentation)

```
Dataset ImageFolder
    Number of datapoints: 50000
    Root location: ./input/cifar10/train
    StandardTransform
Transform: Compose(
               RandomCrop(size=(32, 32), padding=4)
               RandomHorizontalFlip(p=0.5)
               ToTensor()
               Normalize(mean=(0.4914, 0.4822, 0.4465), std=(0.2023, 0.1994, 0.201))
           )
```

## Sample images in batch from the training dataloader.

![image](https://github.com/user-attachments/assets/1a5e696d-cf69-42fa-996a-8964461a1792)

## Training the model

**Learning rate scheduling:**
Instead of using a fixed learning rate, we will use a learning rate scheduler, which will change the learning rate after every batch of training. 
There are many strategies for varying the learning rate during training, and the one we'll use is called the "One Cycle Learning Rate Policy", 
which involves starting with a low learning rate, gradually increasing it batch-by-batch to a high learning rate for about 30% of epochs, 
then gradually decreasing it to a very low value for the remaining epochs.

**Weight decay:**
We also use weight decay, which is yet another regularization technique which prevents the weights from becoming too large by adding an additional term 
to the loss function.

**Gradient clipping:**
Apart from the layer weights and outputs, it also helpful to limit the values of gradients to a small range to prevent undesirable changes
in parameters due to large gradient values. This simple yet effective technique is called gradient clipping. 

### References
[CIFAR-10 ResNet9 Pytorch](https://www.kaggle.com/code/datajameson/cifar-10-object-recognition-resnet-acc-94)
