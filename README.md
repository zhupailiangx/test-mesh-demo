# test-oneapi-Openmp-MLS
Performance exploration

## Linux
* mkdir build
* cd build
* cmake ..
* make -j8
* ./voxel_grid.cpp ../cloud_denoised.pcd

## 测试不同核数和不同线程数对性能的影响
### Linux 隔离物理核
* sudo nano /etc/default/grub
* sudo update-grub
* reboot
### windows 
* 系统配置->引导->高级选项->处理器个数
### 测试结果
