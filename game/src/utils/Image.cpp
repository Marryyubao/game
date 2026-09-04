#include "../../inc/utils/Image.h"

void LoadResource(IMAGE* pDstImage, const wchar_t* filename)//加载一个图片
{
	loadimage(pDstImage, filename);
}

void LoadResource(IMAGE* pDstImage, const wchar_t* filename, int srcX, int srcY, int srcWidth, int srcHeight)//对图片裁剪
{
	IMAGE tempImage;
	loadimage(&tempImage, filename);
	SetWorkingImage(&tempImage);//让图片在设备上工作
	getimage(pDstImage, srcX, srcY, srcWidth, srcHeight);//相当于在设备上截图
	SetWorkingImage();
}
