

#include"Hik.h"
int lPort = 0; //全局的播放库port号
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
	case NET_DVR_SYSHEAD: //系统头


		if (!PlayM4_GetPort(&lPort))  //获取播放库未使用的通道号
		{
			break;
		}
		//m_iPort = lPort; //第一次回调的是系统头，将获取的播放库port号赋值给全局port，下次回调数据时即使用此port号播放
		if (dwBufSize > 0)
		{
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //设置实时流播放模式
			{
				break;
			}

			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 1024 * 1024)) //打开流接口
			{
				break;
			}

			//设置解码回调函数 只解码不显示
			if (!PlayM4_SetDecCallBack(lPort, DecCBFun))
			{
				break;
			}
			struct aa{int unuser;} b;
			b.unuser = 1;
			if (!PlayM4_Play(lPort, NULL)) //播放开始
			{
				break;
			}
		}
		break;
	case NET_DVR_STREAMDATA:   //码流数据
		if (dwBufSize > 0 && lPort != -1)
		{
			// cout << "码流数据" << endl;
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				break;
			}
		}
		break;
	default: //其他数据
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
	case EXCEPTION_RECONNECT:    //预览时重连
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


