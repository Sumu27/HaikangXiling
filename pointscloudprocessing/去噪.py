import open3d as o3d

''' 点云批量读取 '''
path = "D:\\Desktop\\pointscloudcatch\\1\\"
filename = 0
end = ".xyz"
# 修改为目标文件夹下点云文件数量
filenum = 11
varname = "cp"
# 用 var 列表存储读取的所有点云
var = []
for i in range(filenum):
    # 文件路径拼接
    cppath = path + str(filename) + end
    var.append(varname + str(filename))
    # 读取
    var[i] = o3d.io.read_point_cloud(cppath)
    filename = filename + 1

''' 点云数据去噪并写入 '''
# 存储路径
save_path = "D:\\Desktop\\pointscloudcatch\\3save\\"
# 统计滤波参数
# std_ratio越小 滤波效果越好
nns = 50
std_ratio = 0.12
for i in range(filenum):
    # 滤波
    # sor_pcd即为滤波后的点云
    # ind 即为滤波中视作噪声的点
    sor_pcd, ind = var[i].remove_statistical_outlier(nns, std_ratio)
    # 存储路径
    w_path = save_path + str(i) + end
    o3d.io.write_point_cloud(w_path, sor_pcd, True)
