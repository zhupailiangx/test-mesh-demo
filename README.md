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


<table border=0 cellpadding=0 cellspacing=0 width=338 style='border-collapse:
 collapse;table-layout:fixed;width:254pt'>
 <col width=210 style='mso-width-source:userset;mso-width-alt:7680;width:158pt'>
 <col width=64 span=2 style='width:48pt'>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 width=210 style='height:15.0pt;width:158pt'>Metrics</td>
  <td class=xl71 width=64 style='border-left:none;width:48pt'>Linux</td>
  <td class=xl71 width=64 style='border-left:none;width:48pt'>Windows</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Elapsed Time</td>
  <td class=xl71 style='border-top:none;border-left:none'>5.383s</td>
  <td class=xl71 style='border-top:none;border-left:none'>3.398s</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Effective CPU
  Utilization</td>
  <td class=xl73 style='border-top:none;border-left:none'>6.10%</td>
  <td class=xl73 style='border-top:none;border-left:none'>23.40%</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Spin and
  Overhead Time</td>
  <td class=xl71 style='border-top:none;border-left:none'>6.35s</td>
  <td class=xl71 style='border-top:none;border-left:none'>2.842s</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Wait Time with
  poor CPU Utilization</td>
  <td class=xl71 style='border-top:none;border-left:none'>96.6s</td>
  <td class=xl71 style='border-top:none;border-left:none'>0.399s</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=210 style='width:158pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
 </tr>
 <![endif]>
</table>

</body>

注：Spin and Overhead Time 指线程在等待CPU调度时的自旋的时间和切换时做需要的额外时间。线程在等待CPU调度时不停的占用CPU执行空操作，以保持线程的运行状态，以便在CPU可用时立即执行。它们如果时间长会浪费CPU时间，导致性能下降，如果时间短会频繁进行线程切换导致性能下降。

### linux 分析

![image](https://github.com/zhupailiangx/test-mesh-demo/assets/120553507/802944b1-b30f-4498-b124-b0ce32df7408)
### Windows 分析

![image](https://github.com/zhupailiangx/test-mesh-demo/assets/120553507/3a20f2df-27bd-4818-9bde-c98475553704)

&nbsp;
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
### Threads 和 Cores 数量对MLS性能影响
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
 <![endif]>
</table>


 <table border=0 cellpadding=0 cellspacing=0 width=376 style='border-collapse:
 collapse;table-layout:fixed;width:282pt'>
 <col width=184 style='mso-width-source:userset;mso-width-alt:6729;width:138pt'>
 <col width=64 span=3 style='width:48pt'>
 <tr height=20 style='height:15.0pt'>
  <td colspan=4 height=20 class=xl72 width=376 align='center' style='height:15.0pt;width:282pt'>cpu
  &#25968;&#37327;&#23545;mesh demo &#30340;&#24433;&#21709;</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>&nbsp;</td>
  <td class=xl65 style='border-top:none;border-left:none'>14cpus</td>
  <td class=xl65 style='border-top:none;border-left:none'>16cpus</td>
  <td class=xl65 style='border-top:none;border-left:none'>20cpus</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>1.
  VoxelGrid&nbsp;</td>
  <td class=xl65 align=right style='border-top:none;border-left:none'>54</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>
  <div ccp_infra_version=3 ccp_infra_timestamp=1684893356149 ccp_infra_user_hash=1035841675
  ccp_infra_copy_id=24dcaf08-182e-4941-9fc8-fbd13d8c1055 data-ccp-timestamp=1684893356149>54</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>
  <div ccp_infra_version=3 ccp_infra_timestamp=1684893398075 ccp_infra_user_hash=1035841675
  ccp_infra_copy_id=a76f62c3-581c-4ff6-b022-3853863b17f6 data-ccp-timestamp=1684893398075>54</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>2.
  StatisticalOutlierRemoval&nbsp;&#8203;</td>
  <td class=xl65 align=right style='border-top:none;border-left:none'>260</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>288</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>314</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>3.
  MovingLeastSquares&nbsp;</td>
  <td class=xl65 align=right style='border-top:none;border-left:none'>850</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>800</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>1106</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>4.
  NormalEstimation&nbsp;</td>
  <td class=xl65 align=right style='border-top:none;border-left:none'>251</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>184</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>215</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>5.
  GreedyProjection3</td>
  <td class=xl65 align=right style='border-top:none;border-left:none'>2000</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>1940</td>
  <td class=xl78 align=right style='border-top:none;border-left:none'>2037</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>3D Mesh (MLS):
  1,2,3,5&#8203;</td>
  <td class=xl65 align=right style='border-top:none;border-left:none'>3164</td>
  <td class=xl79 align=right width=64 style='border-top:none;border-left:none;
  width:48pt'>3082</td>
  <td class=xl79 align=right width=64 style='border-top:none;border-left:none;
  width:48pt'>3511</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>3D Mesh
  (Normal): 1,2,4,5&#8203;</td>
  <td class=xl65 align=right style='border-top:none;border-left:none'>2565</td>
  <td class=xl79 align=right width=64 style='border-top:none;border-left:none;
  width:48pt'>2466</div>
  </td>
  <td class=xl79 align=right width=64 style='border-top:none;border-left:none;
  width:48pt'>2620</div>
  </td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=184 style='width:138pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
 </tr>
 <![endif]>
</table>

</body>
 


### Windows14个cpu和20个cpu对比
 
 <table border=0 cellpadding=0 cellspacing=0 width=338 style='border-collapse:
 collapse;table-layout:fixed;width:254pt'>
 <col width=210 style='mso-width-source:userset;mso-width-alt:7680;width:158pt'>
 <col width=64 span=2 style='width:48pt'>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl67 width=210 style='height:15.0pt;width:158pt'>Metrics</td>
  <td class=xl71 width=64 style='border-left:none;width:48pt'>14 cpus</td>
  <td class=xl71 width=64 style='border-left:none;width:48pt'>20 cpus</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Elapsed Time</td>
  <td class=xl71 style='border-top:none;border-left:none'>3.54s</td>
  <td class=xl71 style='border-top:none;border-left:none'>3.398s</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Effective CPU
  Utilization</td>
  <td class=xl73 style='border-top:none;border-left:none'>17.60%</td>
  <td class=xl73 style='border-top:none;border-left:none'>23.40%</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Spin and
  Overhead Time</td>
  <td class=xl71 style='border-top:none;border-left:none'>2.124s</td>
  <td class=xl71 style='border-top:none;border-left:none'>2.842s</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl72 style='height:15.0pt;border-top:none'>Wait Time with
  poor CPU Utilization</td>
  <td class=xl71 style='border-top:none;border-left:none'>2.159s</td>
  <td class=xl71 style='border-top:none;border-left:none'>0.399s</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=210 style='width:158pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
 </tr>
 <![endif]>
</table>
 
 
 

### P 核和E核对性能的影响



<table border=0 cellpadding=0 cellspacing=0 width=704 style='border-collapse:
 collapse;table-layout:fixed;width:528pt'>
 <col width=64 span=11 style='width:48pt'>
 <tr height=20 style='height:15.0pt'>
  <td colspan=11 height=20 class=xl77 width=704 align='center' style='height:15.0pt;
  width:528pt'>P core VS E core</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl65 style='height:15.0pt;border-top:none'>&nbsp;</td>
  <td colspan=5 class=xl71 align='center' style='border-left:none'>Linux</td>
  <td colspan=5 class=xl78 align='center' style='border-right:.5pt solid black;border-left:
  none'>Windows</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl71 style='height:30.0pt;border-top:none'>&#36923;&#36753;&#26680;</td>
  <td class=xl71 style='border-top:none;border-left:none'>P-4cpus</td>
  <td class=xl71 style='border-top:none;border-left:none'>E-4cpus</td>
  <td class=xl71 style='border-top:none;border-left:none'>P-1cpu</td>
  <td class=xl71 style='border-top:none;border-left:none'>E-1cpu</td>
  <td class=xl71 style='border-top:none;border-left:none'>P-12cpus</td>
  <td class=xl71 style='border-top:none;border-left:none'>P-4cpus</td>
  <td class=xl71 style='border-top:none;border-left:none'>E-4cpus</td>
  <td class=xl71 style='border-top:none;border-left:none'>P-1cpu</td>
  <td class=xl71 style='border-top:none;border-left:none'>E-1cpu</td>
  <td class=xl71 style='border-top:none;border-left:none'>P-12cpus</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl71 style='height:15.0pt;border-top:none;border-left:
  none'>1538</td>
  <td class=xl71 style='border-top:none;border-left:none'>2235</td>
  <td class=xl71 style='border-top:none;border-left:none'>4319</td>
  <td class=xl71 style='border-top:none;border-left:none'>7884</td>
  <td class=xl71 style='border-top:none;border-left:none'>640</td>
  <td class=xl71 style='border-top:none;border-left:none'>2126</td>
  <td class=xl71 style='border-top:none;border-left:none'>2738</td>
  <td class=xl71 style='border-top:none;border-left:none'>5568</td>
  <td class=xl71 style='border-top:none;border-left:none'>9313</td>
  <td class=xl71 style='border-top:none;border-left:none'>1046</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td rowspan=2 height=40 class=xl81 style='border-bottom:.5pt solid black;
  height:30.0pt;border-top:none'>&#29289;&#29702;&#26680;</td>
  <td class=xl71 style='border-top:none;border-left:none'>4P<span
  style='mso-spacerun:yes'> </span></td>
  <td class=xl71 style='border-top:none;border-left:none'>4E<span
  style='mso-spacerun:yes'> </span></td>
  <td class=xl71 style='border-top:none;border-left:none'>1P</td>
  <td class=xl71 style='border-top:none;border-left:none'>1E</td>
  <td class=xl71 style='border-top:none;border-left:none'>12-P+E</td>
  <td class=xl71 style='border-top:none;border-left:none'>4P<span
  style='mso-spacerun:yes'> </span></td>
  <td class=xl71 style='border-top:none;border-left:none'>4E<span
  style='mso-spacerun:yes'> </span></td>
  <td class=xl71 style='border-top:none;border-left:none'>1P</td>
  <td class=xl71 style='border-top:none;border-left:none'>1E</td>
  <td class=xl71 style='border-top:none;border-left:none'>12-P+E</td>
 </tr>
 <tr height=20 style='height:15.0pt'>
  <td height=20 class=xl71 style='height:15.0pt;border-top:none;border-left:
  none'>1188</td>
  <td class=xl71 style='border-top:none;border-left:none'>2192</td>
  <td class=xl71 style='border-top:none;border-left:none'>4301</td>
  <td class=xl71 style='border-top:none;border-left:none'>7698</td>
  <td class=xl71 style='border-top:none;border-left:none'>600</td>
  <td class=xl71 style='border-top:none;border-left:none'>1725</td>
  <td class=xl71 style='border-top:none;border-left:none'>2819</td>
  <td class=xl71 style='border-top:none;border-left:none'>5569</td>
  <td class=xl71 style='border-top:none;border-left:none'>9304</td>
  <td class=xl71 style='border-top:none;border-left:none'>988</td>
 </tr>
 <![if supportMisalignedColumns]>
 <tr height=0 style='display:none'>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
  <td width=64 style='width:48pt'></td>
 </tr>
 <![endif]>
</table>

## 总结
* Linux在20个核和20个线程的参数下，性能最佳
* Windows 14个线程或者14个逻辑核的参数下，性能最佳
* 多核下，E核没有P核性能强
* Windows 系统MLS程序因为线程数过多或者逻辑核数量过多导致线程之间竞争而降低性能
