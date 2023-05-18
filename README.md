# test-oneapi-Openmp-MLS
## 引言
本示例旨在分析CPU数量和线程数量在Windows和Linux上的性能差异，进而帮助分析Linux和Windows上MLS算法性能差异较大的问题。

## Linux
* mkdir build
* cd build
* cmake ..
* make -j8
* ./voxel_grid.cpp ../cloud_denoised.pcd

## 设置隔离核
### Linux 隔离核
* sudo nano /etc/default/grub
* GRUB_CMDLINE_LINUX_DEFAULT添加isolcpus=18,19
* ctrl+X 保存退出
* sudo update-grub
* reboot
### windows 隔离核
* 系统配置->引导->高级选项->处理器个数

## 测试结果
