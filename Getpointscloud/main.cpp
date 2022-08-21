
#include "../common/common.hpp"
//#include "../common/RenderImage.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>


int main()
{
    ASSERT_OK(MV3D_RGBD_Initialize());

    unsigned int nDevNum = 0;
    ASSERT_OK(MV3D_RGBD_GetDeviceNumber(DeviceType_USB, &nDevNum));
    LOGD("MV3D_RGBD_GetDeviceNumber success! nDevNum:%d.", nDevNum);
    ASSERT(nDevNum);


    // �����豸
    std::vector<MV3D_RGBD_DEVICE_INFO> devs(nDevNum);
    ASSERT_OK(MV3D_RGBD_GetDeviceList(DeviceType_USB, &devs[0], nDevNum, &nDevNum));
    for (unsigned int i = 0; i < nDevNum; i++)
    {
        LOG("Index[%d]. SerialNum[%s] IP[%s] name[%s].\r\n", i, devs[i].chSerialNumber, devs[i].SpecialInfo.stNetInfo.chCurrentIp, devs[i].chModelName);
    }

    //���豸
    void* handle = NULL;
    unsigned int nIndex = 0;
    ASSERT_OK(MV3D_RGBD_OpenDevice(&handle, &devs[nIndex]));
    LOGD("OpenDevice success.");

    // ��ʼ��������
    ASSERT_OK(MV3D_RGBD_Start(handle));
    LOGD("Start work success.");

    //�򿪴洢�ļ�
    std::ofstream os;
    std::string path = "D:\\points\\";
    int flagnum = 0;
    bool exit_flag = TRUE;

    MV3D_RGBD_FRAME_DATA stFrameData = { 0 };
    while (exit_flag)
    {
        // ��ȡͼ������
        int nRet = MV3D_RGBD_FetchFrame(handle, &stFrameData, 5000);
        //��ȡͼ��֡
        if (MV3D_RGBD_OK == nRet)
        {
            //ͼ��֡�ܶ����ͣ�������Ϊ���ʱ����ת��Ϊ����
            for (int i = 0; i < stFrameData.nImageCount; i++)
            {
                //������ȸ�ʽ��ʼת��
                if (ImageType_Depth == stFrameData.stImageData[i].enImageType)
                {
                    path = "D:\\points\\" + std::to_string(flagnum) + ".xyz";
                    os.open(path, std::ios::app);
                    flagnum++;
                    MV3D_RGBD_IMAGE_DATA stPointCloudImage;
                    //����ǰ֡ת��Ϊ����
                    nRet = MV3D_RGBD_MapDepthToPointCloud(handle, &stFrameData.stImageData[i], &stPointCloudImage);
                    //pPtr ָ�� ���ƴ洢��ʼ��ַ
                    float* pPtr = (float*)stPointCloudImage.pData;
                    int nPointNum = stPointCloudImage.nDataLen / (sizeof(float) * 3);

                    //�ӵ�һ�����ƿ�ʼ���ļ�����д�� xyz ����
                    LOGD("Start write Points of %d framenum!", stPointCloudImage.nFrameNum);
                    for (int nPntIndex = 0; nPntIndex < nPointNum; ++nPntIndex)
                    {
                        if (pPtr[nPntIndex * 3 + 0] != 0 || pPtr[nPntIndex * 3 + 1] != 0 || pPtr[nPntIndex * 3 + 2] != 0)
                            os << pPtr[nPntIndex * 3 + 0] << ' ' << pPtr[nPntIndex * 3 + 1] << ' ' << pPtr[nPntIndex * 3 + 2] << std::endl;

                    }

                    LOGD("_MapDepthToPointCloud() Run Succeed: framenum (%d) height(%d) width(%d)  len (%d)!", stPointCloudImage.nFrameNum,
                        stPointCloudImage.nHeight, stPointCloudImage.nWidth, stPointCloudImage.nDataLen);
                    os.close();
                }


                //����ȡͼ��֡ʧ�����˳�
                if (MV3D_RGBD_OK != nRet)
                {
                    break;
                }

            }

        }
        //�����˳�
        if (_kbhit())
        {
            exit_flag = FALSE;
        }
    }

    ASSERT_OK(MV3D_RGBD_Stop(handle));
    ASSERT_OK(MV3D_RGBD_CloseDevice(&handle));
    ASSERT_OK(MV3D_RGBD_Release());

    LOGD("Main done!");

    return 0;
}