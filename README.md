# test-oneapi-Openmp-MLS
## 引言
本示例旨在分析CPU数量和线程数量在Windows和Linux上对MLS算法的性能影响。

## Linux
* source /opt/intel/oneapi/setvars.sh
* mkdir build
* cd build
* cmake ..
* make -j8
* ./voxel_grid.cpp ../cloud_denoised.pcd
## Windows
* 打开PowerShell, cmd.exe "/K" '"C:\Program Files (x86)\Intel\oneAPI\setvars.bat" && powers
* ./build_mesh.bat
* ./run_mesh.bat
## Vtune Threading

<table border=0 cellpadding=0 cellspacing=0 width=594 style='border-collapse:
 collapse;table-layout:fixed;width:446pt'>
 <col width=210 style='mso-width-source:userset;mso-width-alt:7680;width:158pt'>
 <col width=64 span=6 style='width:48pt'>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 width=210 style='height:15.0pt;width:158pt'>Metrics</td>
  <td class=xl71 width=64 style='border-left:none;width:48pt'>Linux</td>
  <td class=xl71 width=64 style='border-left:none;width:48pt'>Windows</td>

 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Elapsed Time</td>
  <td class=xl71 style='border-top:none;border-left:none'>5.383s</td>
  <td class=xl71 style='border-top:none;border-left:none'>3.398s</td>
  <td colspan=4 style='mso-ignore:colspan'></td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Effective CPU
  Utilization</td>
  <td class=xl73 style='border-top:none;border-left:none'>6.10%</td>
  <td class=xl73 style='border-top:none;border-left:none'>23.40%</td>
  <td colspan=4 style='mso-ignore:colspan'></td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Spin and
  Overhead Time</td>
  <td class=xl71 style='border-top:none;border-left:none'>6.35s</td>
  <td class=xl71 style='border-top:none;border-left:none'>2.642</td>
  <td colspan=4 style='mso-ignore:colspan'></td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Wait Time with
  poor CPU Utilization</td>
  <td class=xl71 style='border-top:none;border-left:none'>96.6s</td>
  <td class=xl71 style='border-top:none;border-left:none'>0.399s</td>
  <td colspan=4 style='mso-ignore:colspan'></td>
 </tr>
 <tr height=80 style='height:60.0pt;mso-xlrowspan:4'>
  <td height=80 colspan=7 style='height:60.0pt;mso-ignore:colspan'></td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 colspan=6 style='height:15.0pt;mso-ignore:colspan'></td>
  <td class=xl70></td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=210 style='width:158pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
 </tr>
 <![endif]>
</table>

</body>


### linux 分析

![image](https://github.com/zhupailiangx/test-mesh-demo/assets/120553507/802944b1-b30f-4498-b124-b0ce32df7408)
### Windows 分析

![image](https://github.com/zhupailiangx/test-mesh-demo/assets/120553507/3a20f2df-27bd-4818-9bde-c98475553704)
Linux Spin and Overhead 时间长。
由于Linux系统Vtune Treading分析不能给出线程运行在P核还是E核，所以采用了隔离核的方式进行分析。 
## 设置隔离核
### Linux 隔离核
* sudo nano /etc/default/grub
* GRUB_CMDLINE_LINUX_DEFAULT添加isolcpus=18,19
* ctrl+X 保存退出
* sudo update-grub
* reboot
### Windows 隔离核
* 系统配置->引导->高级选项->处理器个数
### Windows指定CPU运行
* 任务管理器->详细信息->devenv.exe->设置相关性

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
  <td class=xl66 align=right style='border-top:none;border-left:none'>1278</td>
  <td class=xl67 align=right style='border-top:none;border-left:none'>526</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>20</td>
  <td class=xl68 align=right style='border-top:none;border-left:none'>526</td>
  <td class=xl66 align=right style='border-top:none;border-left:none'>1278</td>
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
 
 
 

<table border=0 cellpadding=0 cellspacing=0 width=256 style='border-collapse:
 collapse;table-layout:fixed;width:192pt'>
 <col width=64 span=4 style='width:48pt'>
 <tr height=20 style='height:15.0pt'>
  <td colspan=2 height=20 class=xl68 width=128 style='height:15.0pt;width:96pt'>Linux</td>
  <td colspan=2 class=xl68 width=128 style='border-left:none;width:96pt'>Windows</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl68 style='height:15.0pt;border-top:none'>4P</td>
  <td class=xl68 style='border-top:none;border-left:none'>4E</td>
  <td class=xl68 style='border-top:none;border-left:none'>4P</td>
  <td class=xl68 style='border-top:none;border-left:none'>4E</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl68 style='height:15.0pt;border-top:none'>1538</td>
  <td class=xl68 style='border-top:none;border-left:none'>2235</td>
  <td class=xl68 style='border-top:none;border-left:none'>2126</td>
  <td class=xl68 style='border-top:none;border-left:none'>2738</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
 </tr>
 <![endif]>
</table>

</body>

## 总结
* Linux在20个核和20个线程的参数下，性能最佳
* Windows 14个线程或者14个逻辑核的参数下，性能最佳
* 多核下，E核没有P核性能强
* Windows 系统MLS程序因为线程数过多或者逻辑核数量过多导致切换调度时间长而降低性能
