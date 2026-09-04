#pragma once

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include<easyx.h>

void LoadResource(IMAGE* pDstImage, const wchar_t* filename);//加载一个图片
void LoadResource(IMAGE* pDstImage, const wchar_t* filename, int srcX, int srcY, int srcWidth, int srcHeight);//对图片裁剪


#endif