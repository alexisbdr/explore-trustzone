# Exploring TrustZone on low-end hardware
You can find my project proposal link with a more detailed explanation of the project and a rough timeline [here](https://docs.google.com/document/d/1rf5Crq-3dXzLbgTLsfG50kNxVh7cxbN0p3KY8BKXzn4/edit)

## [ARM Trustzone](https://developer.arm.com/ip-products/security-ip/trustzone)
Trustzone is ARM's secure execution environment, it provides "hardware enforced" isolation to embedded computers. Trustzone has been adopted as the security option for embedded applications that deal with sensitive information. 

## Hardware 
* Boards
    * [Raspberry PI 3B+](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/)
    * [HiKey Development Board](https://www.96boards.org/product/hikey/)
* Cameras
    * [IMX219 MIPI CSI-2 Camera](https://www.raspberrypi.org/products/camera-module-v2/)
    * [USB Cameras]

The availability, cost and widespread adoption has made the RaspberryPI the go-to platform for rapid development or prototyping on low-end hardware. We will first try using the RPI 3B+ but other board options are available.  

## [OP-TEE](https://www.op-tee.org/)
OP-TEE is a trusted execution environment (TEE) and is built on top of Trustzone. A port of OP-TEE to Raspberry PI 3B+ was first done by Sequitur Labs and instructions are [here](https://optee.readthedocs.io/en/latest/building/devices/rpi3.html).

## External Resources
* Performance Evaluation of OP-TEE on Raspberry PI3 [paper](https://arxiv.org/pdf/1906.09799.pdf)
* Building an application for OP-TEE - [here](https://optee.readthedocs.io/en/latest/building/trusted_applications.html)


