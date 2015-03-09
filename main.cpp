#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <tchar.h>
#include "utility.h"

#include "BUF_USBCCDCamera_SDK.h"

using namespace std;


#define CCD_FRAME_RAW 0
#define FRAME_TYPE	CCD_FRAME_RAW
#define CAMERA_WIDTH    1280
#define CAMERA_HEIGHT   960

unsigned char* Image;

void FrameCallBack(TProcessedDataProperty* Attributes, unsigned char* BytePtr){
for(int i;i<10;i++){
cout << "works" << endl;
		char buffer[512];
		string time = get_date();
		int d = 5;
		sprintf(buffer,"yayta_%d.raw",i);

		FILE* file = fopen(buffer, "wb");
		if ( file == NULL )
		{
			printf( "Error: Could not open file.\n" );
		}
		else
		{

		fwrite( BytePtr,Attributes->Column * Attributes->Row, 1, file );

			fclose(file);
		}
cin >> d;
}

}



void CameraFaultCallBack(int ImageType)
{
	printf("Error: Camera fault.\n");
	BUFCCDUSB_StopFrameGrab();
	BUFCCDUSB_StopCameraEngine();
	BUFCCDUSB_UnInitDevice();
	//fault = true;
}
void stopCamera(){
	BUFCCDUSB_StopFrameGrab();
	BUFCCDUSB_StopCameraEngine();
	BUFCCDUSB_UnInitDevice();
}


int _tmain(int argc, _TCHAR* argv[])
{
	MSG msg;


	int ret;
	int ent;
//init - addevice - startcameraengine - workmode - framehooker - USBHooker - framegrab


	ret = BUFCCDUSB_InitDevice();
	if (ret == 0){ cout << "no cameras" << endl;
	}else{
	cout << "success InitDevice: " << ret << endl;
	 }	

	ret = BUFCCDUSB_AddDeviceToWorkingSet( 1 );
	if(ret == 1){cout << "success addCameratoSet: " << ret << endl;
	}else{
	cout << "failed, press a button to exit" << endl;
	cin >> ent;
	return 0;
	}
	ret = BUFCCDUSB_InstallUSBDeviceHooker(CameraFaultCallBack);
	if(ret == 1){cout << "success installUSBDeviceHooker: " << ret << endl;
	}else{
	cout << "failed, press a button to exit" << endl;
	cin >> ent;
	return 0;
	}
cin >> ret;

	ret = BUFCCDUSB_SetCustomizedResolution( 1,1280, 960,0,1);

	ret = BUFCCDUSB_StartCameraEngine(NULL, 8);
	if(ret == 1){cout << "success startCameraEngine:  " << ret << endl;
	}else{
	cout << "failed, press a button to exit" << endl;
	cin >> ent;
	return 0;
	}
	ret = BUFCCDUSB_StartFrameGrab(GRAB_FRAME_FOREVER);
//cin >> ret;
	ret = BUFCCDUSB_InstallFrameHooker(0, FrameCallBack);
cin >> ret;






/*
	if(ret == 1){cout << "success installFrameHooker: " << ret << endl;
	}else{
	cout << "failed, press a button to exit" << endl;
	cin >> ent;
	return 0;
	}
*/



	//ret = BUFCCDUSB_SetCameraWorkMode( 1, 0 );
//ret = BUFCCDUSB_SetCameraWorkMode(1,1);






	if(GetMessage(&msg,NULL,NULL,NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}

	stopCamera();
	cout << "success stopCamera: " << ret << endl;
	return 0;
}

