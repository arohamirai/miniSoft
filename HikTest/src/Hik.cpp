

#include"Hik.h"
int lPort = 0; //ȫ�ֵĲ��ſ�port��
//void *hWnd = NULL;





void CALLBACK DecCBFun(int nPort, char * pBuf, int nSize, FRAME_INFO * pFrameInfo, void *nReserved1, int nReserved2)
{
	cv::Mat picYV12,picBGR;
	picYV12 = cv::Mat(pFrameInfo->nHeight * 3 / 2, pFrameInfo->nWidth, CV_8UC1, pBuf);
	cvtColor(picYV12, picBGR, CV_YUV2BGR_YV12);

	cv::imshow("img",picBGR);

	cv::waitKey(1);
	return;
}


void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void* dwUser)
{
	//hWnd = GetConsoleWindow();

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD: //ϵͳͷ


		if (!PlayM4_GetPort(&lPort))  //��ȡ���ſ�δʹ�õ�ͨ����
		{
			break;
		}
		//m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
			{
				break;
			}

			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 1024 * 1024)) //�����ӿ�
			{
				break;
			}

			//���ý���ص����� ֻ���벻��ʾ
			if (!PlayM4_SetDecCallBack(lPort, DecCBFun))
			{
				break;
			}
			struct aa{int unuser;} b;
			b.unuser = 1;
			if (!PlayM4_Play(lPort, NULL)) //���ſ�ʼ
			{
				break;
			}
		}
		break;
	case NET_DVR_STREAMDATA:   //��������
		if (dwBufSize > 0 && lPort != -1)
		{
			// cout << "��������" << endl;
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			}
		}
		break;
	default: //��������
		if (dwBufSize > 0 && lPort != -1)
		{
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			}
		}
		break;
	}

}

void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
	char tempbuf[256] = { 0 };
	switch (dwType)
	{
	case EXCEPTION_RECONNECT:    //Ԥ��ʱ����
		printf("----------reconnect--------%d\n", time(NULL));
		break;
	default:
		break;
	}
}

unsigned int __stdcall readCam(void *param)
{
	
	return 0;
}


