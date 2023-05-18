set SYCL_ENABLE_DEFAULT_CONTEXTS=1
set SYCL_DEVICE_FILTER=ext_oneapi_level_zero:gpu
set PATH=%PATH%;C:\Program Files (x86)\flann\bin\
set PATH=%PATH%;C:\Program Files (x86)\PCL\bin;C:\Program Files (x86)\PCL-ONEAPI\bin;C:\Program Files\PCL 1.12.1\3rdParty\VTK\bin;C:\Program Files\OpenNI2\Redist;C:\Program Files\PCL 1.12.1\3rdParty\Qhull\bin;
cd build
.\Release\voxel_grid.exe  ../cloud_denoised.pcd
