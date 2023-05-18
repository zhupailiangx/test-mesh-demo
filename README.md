# test-oneapi-Openmp-MLS
## 引言
本示例旨在分析CPU数量和线程数量在Windows和Linux上对MLS算法的性能影响。

## Linux
* mkdir build
* cd build
* cmake ..
* make -j8
* ./voxel_grid.cpp ../cloud_denoised.pcd
## Windows
* 运行bat文件

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
