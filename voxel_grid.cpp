// ./voxel_grid ../cloud.pcd 0

// Keep pcl-oneapi headers ahead of the others
#include <pcl/oneapi/filters_omp/statistical_outlier_removal.h>
#include <pcl/oneapi/surface_omp/mls.h>
#include <pcl/features/normal_3d_omp.h>
#include <iostream>
#include <string>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
// GP3 to be replaced with pcl-oneapi
#include <pcl/oneapi/surface_omp/gp3.h>
#include <pcl/io/vtk_io.h>
#include <pcl/common/time.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/ply_io.h>
//#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common.h>
#include <ctime>
#include <omp.h>
//pcl::visualization::PCLVisualizer *viewer;

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: exec cloud_file_path smooth use_pcl-oneapi" << std::endl;
        return -1;
    }
    const std::string filePath = argv[1];
    //bool smooth = atoi(argv[2]);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile(filePath, *cloud);
    //pcl::StopWatch time_total;
    std::cout << "omp_get_max_threads():" << omp_get_max_threads() << std::endl;
    //test msl 
    std::cout << "PointCloud after filtering: " << cloud->width * cloud->height<< " data points (" << pcl::getFieldsList(*cloud) << ")." << std::endl;

    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);

    pcl::StopWatch time3;
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
    mls.setComputeNormals(true);
    mls.setInputCloud(cloud);
    mls.setPolynomialOrder(2);
    mls.setSearchMethod(tree);
    mls.setSearchRadius(0.05);


    mls.setNumberOfThreads(20);
    //mls.process(*cloud_with_normals);
   /* mls.process(*cloud_with_normals);
    mls.process(*cloud_with_normals);*/
    for (int i = 0; i < 30; i++) 
        mls.process(*cloud_with_normals);
    
    std::cout << "======MLS: " << time3.getTime()/30 << " ms" << std::endl;








    
 //   for (int loop=0; loop<3; loop++) {
 //       printf("\n");
 //       std::cout << "Loop: " << loop << std::endl;
 //       printf("\n");
	//// Down sampling
 //       pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
 //       pcl::StopWatch time1;
 //       pcl::VoxelGrid<pcl::PointXYZ> vg;
 //       vg.setInputCloud(cloud);
 //       vg.setLeafSize(0.01f, 0.01f, 0.01f);
 //       vg.filter(*cloud_filtered);
 //       std::cout << "======Sampling: " << time1.getTime() << " ms" << std::endl;
 //       std::cout << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
 //           << " data points (" << pcl::getFieldsList(*cloud_filtered) << ")." << std::endl;

        // Noise reduction
      /*  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_denoised(new pcl::PointCloud<pcl::PointXYZ>);
        std::cout << "Cloud before filtering: " << std::endl;
        std::cout << *cloud_filtered << std::endl;
        pcl::StopWatch time2;
        pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
        sor.setInputCloud(cloud_filtered);
        sor.setMeanK(50);
        sor.setStddevMulThresh(1.0);
        sor.filter(*cloud_denoised);
        std::cout << "======Noise reduction: " << time2.getTime() << " ms" << std::endl;
        std::cout << "Cloud after filtering: " << std::endl;
        std::cout << *cloud_denoised << std::endl;

        pcl::io::savePCDFile("cloud_denoised.pcd", *cloud_denoised);*/

        //pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
        //if (smooth) {
        //    // Smooth
	       // pcl::StopWatch time3;
        //    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
        //    pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
        //    mls.setComputeNormals(true);
        //    mls.setInputCloud(cloud_denoised);
        //    mls.setPolynomialOrder(2);
        //    mls.setSearchMethod(tree);
        //    mls.setSearchRadius(0.05);
        //    mls.setNumberOfThreads(20);
        //    mls.process(*cloud_with_normals);
        //    std::cout << "======MLS: " << time3.getTime() << " ms" << std::endl;
        //} else {
            // Normal Estimation
    	    //pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
         //   pcl::StopWatch time4;
         //   pcl::NormalEstimationOMP<pcl::PointXYZ, pcl::Normal> n(20); //pcl::oneapi::NormalEstimation ne_device;
         //   pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
         //   tree->setInputCloud(cloud_denoised);
         //   n.setInputCloud(cloud_denoised);
         //   n.setSearchMethod(tree);
         //   n.setKSearch(20);
         //   n.compute(*normals);

         //   // Concatenate the XYZ and normal fields*
         //   pcl::concatenateFields(*cloud_denoised, *normals, *cloud_with_normals);
         //   std::cout << "======Normal estimation: " << time4.getTime() << " ms" << std::endl;
        //}
        //pcl::io::savePCDFile("cloud_with_normals.pcd", *cloud_with_normals);

	// Triangulation
     //   pcl::PolygonMesh triangles;
     //   pcl::StopWatch time5;
	    //pcl::GreedyProjectionTriangulationOMP<pcl::PointNormal> gp3;
     //   pcl::search::KdTree<pcl::PointNormal>::Ptr tree2(new pcl::search::KdTree<pcl::PointNormal>);
     //   tree2->setInputCloud(cloud_with_normals);
     //   gp3.setSearchRadius(0.05);
     //   gp3.setMu(2.5);
     //   gp3.setMaximumNearestNeighbors(100);
     //   gp3.setMaximumSurfaceAngle(M_PI / 4); // 45 degrees
     //   gp3.setMinimumAngle(M_PI / 18); // 10 degrees
     //   gp3.setMaximumAngle(2 * M_PI / 3); // 120 degrees
     //   gp3.setNormalConsistency(false);
     //   gp3.setInputCloud(cloud_with_normals);
     //   gp3.setSearchMethod(tree2);
	    //
     //   gp3.setNumberOfThreads(omp_get_max_threads());
     //   gp3.setBlockOverlapPercentage(0.05);
	    //
     //   gp3.reconstruct(triangles);
     //   std::cout << "======GreedyProjection3: " << time5.getTime() << " ms" << std::endl;
     //   pcl::io::savePLYFile("surface.ply", triangles);

//#if 0 // visualization
//        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_src(new pcl::PointCloud<pcl::PointXYZ>());
//        if (-1 == pcl::io::loadPLYFile("surface.ply", *cloud_src)) {
//            std::cout << "load ply file failed. please check it." << std::endl;
//            return -2;
//        }
//        pcl::PolygonMesh poly_mesh = triangles;
//
//        viewer = new pcl::visualization::PCLVisualizer("viewer");
//        int v1;
//        int v2;
//        viewer->createViewPort(0.0, 0.0, 0.5, 1.0, v1);
//        viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v2);
//        viewer->addText("v1", 10, 10, 20, 1, 0, 0, "viewport_v1", v1);
//        viewer->addText("v2", 10, 10, 20, 0, 1, 0, "viewport_v2", v2);
//        viewer->addCoordinateSystem(0.5);
//        viewer->setBackgroundColor(0.2, 0.2, 0.2);
//        viewer->addPointCloud(cloud_src, "cloud_src", v1);
//        viewer->addPolygonMesh(poly_mesh, "mesh_src", v2);
//        viewer->spinOnce(5);
//	viewer->removePointCloud("cloud_src", v1);
//	viewer->removePolygonMesh("mesh_src", v2);
//#endif
   // } // end for
    //std::cout << "======total times: " << time_total.getTime() << " ms" << std::endl;
  
    return 0;
}
