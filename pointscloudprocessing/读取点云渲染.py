import open3d as o3d

pcd = o3d.io.read_point_cloud('D:\\Desktop\\pointscloudcatch\\2\\2.xyz',format='xyz')
o3d.visualization.draw_geometries([pcd],"Open3D pointscloud", width=800, height=600, left=50, top=50,
                                  point_show_normal=False, mesh_show_wireframe=False,
                                  mesh_show_back_face=False)
