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
针对ADL 12700 12核（8P，4E）,
MLS算法采用30次循环实验，取平均时间作为对比指标
<table border=0 cellpadding=0 cellspacing=0 width=532 style='border-collapse:
 collapse;table-layout:fixed;width:399pt'>
 <col width=64 style='width:48pt'>
 <col width=88 span=2 style='mso-width-source:userset;mso-width-alt:3218;
 width:66pt'>
 <col width=116 style='mso-width-source:userset;mso-width-alt:4242;width:87pt'>
 <col width=88 span=2 style='mso-width-source:userset;mso-width-alt:3218;
 width:66pt'>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl65 width=64 style='height:30.0pt;width:48pt'>Threads</td>
  <td class=xl66 width=88 style='border-left:none;width:66pt'>Windows</td>
  <td class=xl66 width=88 style='border-left:none;width:66pt'>Linux</td>
  <td rowspan=2 class=xl65 width=116 style='width:87pt'>Logical CPU count</td>
  <td class=xl66 width=88 style='border-left:none;width:66pt'>Linux</td>
  <td class=xl66 width=88 style='border-left:none;width:66pt'>Windows</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 style='height:15.0pt;border-top:none;border-left:
  none'>Average time</td>
  <td class=xl66 style='border-top:none;border-left:none'>Average time</td>
  <td class=xl66 style='border-top:none;border-left:none'>Average time</td>
  <td class=xl66 style='border-top:none;border-left:none'>Average time</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>20</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>1226</td>
  <td class=xl67 align=right style='border-top:none;border-left:none'>526</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>20</td>
  <td class=xl68 align=right style='border-top:none;border-left:none'>526</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>1226</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>18</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>1117</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>561</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>18</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>539</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>1044</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>16</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>981</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>571</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>16</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>554</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>931</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>14</td>
  <td class=xl67 align=right style='border-top:none;border-left:none'>917</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>620</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>14</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>579</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>919</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>12</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>966</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>638</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>12</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>640</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>1046</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl66 align=right style='height:15.0pt;border-top:none'>10</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>980</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>675</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>10</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>732</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>1172</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=88 style='width:66pt'></td>
  <td width=88 style='width:66pt'></td>
  <td width=116 style='width:87pt'></td>
  <td width=88 style='width:66pt'></td>
  <td width=88 style='width:66pt'></td>
 </tr>
 
 
 

 <table border=0 cellpadding=0 cellspacing=0 width=192 style='border-collapse:
 collapse;table-layout:fixed;width:144pt'>
 <col width=64 span=3 style='width:48pt'>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl69 width=64 style='height:30.0pt;width:48pt'>Linux time</td>
  <td class=xl70 width=64 style='border-left:none;width:48pt'>12P+4E</td>
  <td class=xl70 width=64 style='border-left:none;width:48pt'>16P</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl70 style='height:15.0pt;border-top:none;border-left:
  none'>603</td>
  <td class=xl70 style='border-top:none;border-left:none'>547</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
 </tr>
 <![endif]>
</table>
 <![endif]>
</table>

## 总结
* Linux在20个核和20个线程的参数下，性能最佳
* Windows 14个线程或者14个逻辑核的参数下，性能最佳
* E核没有P核性能强
* Linux 线程调度和内核支持优于Windows
