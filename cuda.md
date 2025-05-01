Running a CUDA program on Ubuntu involves several steps, from installing the necessary tools to compiling and executing the CUDA code. Here's a step-by-step guide:

✅ Step 1: Verify System Requirements

Make sure your system has:

A CUDA-capable NVIDIA GPU

Ubuntu 20.04 or 22.04 (or similar version)

gcc/g++ compilers (some versions are more compatible with specific CUDA versions)

✅ Step 2: Install NVIDIA Driver

Check current GPU:

lspci | grep -i nvidia

Add NVIDIA's PPA and install the latest driver:

sudo add-apt-repository ppa:graphics-drivers/ppa

sudo apt update

sudo ubuntu-drivers autoinstall

sudo reboot

After reboot, verify driver installation:

nvidia-smi

✅ Step 3: Install CUDA Toolkit

You can install from .deb package or use apt. Here's the recommended way using the .deb:

Download the CUDA Toolkit for your version of Ubuntu.

Install CUDA:

sudo dpkg -i cuda-repo-<version>.deb

sudo apt-key add /var/cuda-repo-*/7fa2af80.pub

sudo apt update

sudo apt install cuda

Add CUDA to the path: Add the following lines to your ~/.bashrc or ~/.zshrc:

export PATH=/usr/local/cuda/bin:$PATH

export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH

Then:

source ~/.bashrc

Verify installation:

nvcc --version

✅ Step 4: Compile a CUDA Program

Create a test file, e.g., test.cu:

#include <stdio.h>

__global__ void helloCUDA() {
    printf("Hello from GPU!\n");
}

int main() {
    helloCUDA<<<1, 1>>>();
    cudaDeviceSynchronize();
    return 0;
}

Compile with nvcc:

nvcc -o test test.cu

✅ Step 5: Run the Program

./test

You should see:

Hello from GPU!

✅ Optional: Install cuDNN (for deep learning applications)

Download cuDNN from NVIDIA cuDNN.

Extract and copy the files to CUDA directories:

sudo cp cuda/include/cudnn*.h /usr/local/cuda/include

sudo cp cuda/lib64/libcudnn* /usr/local/cuda/lib64

sudo chmod a+r /usr/local/cuda/include/cudnn*.h /usr/local/cuda/lib64/libcudnn*

Would you like a ready-made Makefile or a sample CUDA project to try out?



To run a CUDA program on Windows, you'll need to install the appropriate tools, configure your environment, and compile using NVIDIA's nvcc compiler. Here are the steps:

✅ Step 1: Check Prerequisites

Make sure you have:

An NVIDIA CUDA-capable GPU

Windows 10/11 (64-bit)

A supported Visual Studio version (e.g., 2019 or 2022)

Administrator privileges

✅ Step 2: Install NVIDIA GPU Driver

Download and install the latest driver from:

👉 https://www.nvidia.com/Download/index.aspx

After installation, verify with:

nvidia-smi

You can run this in Command Prompt (CMD) or Windows PowerShell.

✅ Step 3: Install CUDA Toolkit

Download the CUDA Toolkit from:

👉 https://developer.nvidia.com/cuda-downloads

Install with default settings (this includes:

CUDA compiler nvcc

CUDA libraries

Nsight tools

Visual Studio integration)

After installation:

CUDA usually installs to C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\vXX.X

✅ Step 4: Set Up Environment Variables

These are often set automatically, but you can verify or add them manually:

Go to:

Control Panel → System → Advanced system settings → Environment Variables

Under System variables, make sure:

CUDA_PATH is set to something like:

C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.1

Add to Path:

C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.1\bin

✅ Step 5: Write a CUDA Program

Create a file, e.g., hello.cu:

#include <stdio.h>

__global__ void helloFromGPU() {
    printf("Hello from the GPU!\n");
}

int main() {
    helloFromGPU<<<1, 1>>>();
    cudaDeviceSynchronize();
    return 0;
}

✅ Step 6: Compile Using nvcc

Open "x64 Native Tools Command Prompt for VS 20XX" (from the Start menu).

Navigate to your file's directory and run:

nvcc hello.cu -o hello.exe

✅ Step 7: Run the Program

hello.exe

Expected output:

Hello from the GPU!

✅ Optional: Use Visual Studio for CUDA

If you prefer using Visual Studio:

Launch Visual Studio.

File → New → Project → "CUDA 11.x Runtime" (if CUDA is integrated properly).

Write and build your CUDA code in the provided *.cu files.

Press Ctrl + F5 to build and run.

