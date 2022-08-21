
import open3d as o3d

print("加载点云，显示并渲染")
pcd = o3d.io.read_point_cloud('1.xyz',format='xyz')
pcd.paint_uniform_color([0.5, 0.5, 0.5])
o3d.visualization.draw_geometries([pcd], "Open3D origin points",
                                  width=800, height=600, left=50, top=50,
                                  point_show_normal=False,
                                  mesh_show_wireframe=False,
                                  mesh_show_back_face=False)

print("下采样")
downpcd = pcd.voxel_down_sample(voxel_size=0.05)  # 下采样
o3d.visualization.draw_geometries([downpcd], "Open3D downsample points",
                                  width=800, height=600,
                                  left=50, top=50,
                                  point_show_normal=False,
                                  mesh_show_wireframe=False,
                                  mesh_show_back_face=False)

print("计算下采样点云的法线")
downpcd.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHybrid(radius=0.1, max_nn=30))  # 设置搜索半径0.1m，邻域内30个点
o3d.visualization.draw_geometries([downpcd], "Open3D normal estimation",
                                  width=800, height=600, left=50, top=50,
                                  point_show_normal=True,
                                  mesh_show_wireframe=False,
                                  mesh_show_back_face=False)

