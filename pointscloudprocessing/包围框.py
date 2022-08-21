import open3d as o3d

pcd = o3d.io.read_point_cloud("5.xyz")
# 点云AABB包围盒
aabb = pcd.get_axis_aligned_bounding_box()
aabb.color = (1, 0, 0)
# 点云OBB包围盒
obb = pcd.get_oriented_bounding_box()
obb.color = (0, 1, 0)
o3d.visualization.draw_geometries([pcd, aabb, obb], window_name="点云包围盒",
                                  width=800, height=600,
                                  left=50, top=50,
                                  point_show_normal=False,
                                  mesh_show_wireframe=False,
                                  mesh_show_back_face=False)# 可视化





