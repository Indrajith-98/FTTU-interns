import torch
import torch.nn as nn


class CustomCNN(nn.Module):
    def __init__(self, num_classes=10):
        super(CustomCNN, self).__init__()
        self.conv_layers = nn.Sequential(
            # First Convolutional layer
            nn.Conv2d(
                1, 32, kernel_size=3, stride=1, padding=1
            ),  # in_channels=1, out_channels=32
            nn.BatchNorm2d(32),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2),  # Reduces size by half
            # Second Convolutional layer
            nn.Conv2d(
                32, 64, kernel_size=3, stride=1, padding=1
            ),  # in_channels=32, out_channels=64
            nn.BatchNorm2d(64),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2),  # Reduces size by half
            # Third Convolutional layer
            nn.Conv2d(
                64, 128, kernel_size=3, stride=1, padding=1
            ),  # in_channels=64, out_channels=128
            nn.BatchNorm2d(128),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2),  # Reduces size by half
        )
        self.fc_layers = nn.Sequential(
            nn.Flatten(),
            nn.Linear(128 * 3 * 3, 256),  # Adjusted input size to FC layer
            nn.GELU(),
            nn.Dropout(0.5),
            nn.Linear(256, num_classes),
        )

    def forward(self, x):
        x = self.conv_layers(x)
        x = self.fc_layers(x)
        return x


# Example usage
model = CustomCNN(num_classes=10)
x = torch.randn(1, 1, 28, 28)  # Batch size 1, grayscale image 28x28
output = model(x)
print(output.shape)  # Should output (1, 10)
