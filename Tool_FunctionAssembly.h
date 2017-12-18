//
//  FunctionAssembly.h
//  XiaoXiaoLe2
//
//  Created by 欧阳佳乐 on 2017/7/27.
//
//

#ifndef FunctionAssembly_h
#define FunctionAssembly_h

#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "math.h"

using namespace std;

class ToolFunctionAssembly
{
public:
    /*int转换为string*/
    static string changeIntToString(int num);
    
    /*两点的距离*/
    static float getTwoPointDis(float x1, float y1, float x2, float y2);
    
    /*点距离直线是否在距离内
     *参数:
     ** a,b,c:(float) 直线方程式的参数(ax+by+c=0)
     ** poiX,poiY:(float) 点的坐标(x,y)
     ** dis:(float) 距离的最大值
     */
    static bool isPointDisLineLess(float a, float b, float c, float poiX, float poiY, float dis);
    
    /*点距离直线是否在距离内
     *参数:
     ** poiX1,poiY1,poiX2,poiY2:(float) 直线上的两点(poiX1,poiY1),(poiX2,poiY2)
     ** poiX,poiY:(float) 点的坐标(x,y)
     ** dis:(float) 距离的最大值
     */
    static bool isPointDisLineLess(float poiX1, float poiY1, float poiX2, float poiY2, float poiX, float poiY, float dis);
    
    /*点是否在矩形范围内
     *参数:
     ** poiBegX,poiBegY:(float) 矩形的起始点(左下点),(poiBegX,poiBegY)
     ** width,hight:(float) 矩形的长和高,(width,hight)
     ** poiX,poiY:(float) 点的坐标(poiX,poiY)
     */
    static bool isPointInRect(float poiBegX, float poiBegY, float width, float hight, float poiX, float poiY);
    
    /*点是否在圆形范围内
     *参数:
     ** poiCirX,poiCirY:(float) 圆心(x, y)
     ** radius:(float) 圆的半径
     ** poiX,poiY:(float) 点的坐标
     */
    static bool isPointInCircle(float poiCirX, float poiCirY, float radius, float poiX, float poiY);
    
    /*点是否在多边形范围内
     *参数:
     ** polyX,polyY:(vector<float>) 多边形的坐标点,(polyX[n],polyY[n])
     ** poiX,poiY:(float) 点的坐标(poiX,poiY)
     */
    static bool isPointInPolygon(vector<float> polyX, vector<float> polyY, float poiX, float poiY);
    
    //将map<int, T>的按照int大小排列，返回vector<T>, isFromStoL = true:从小到大
    template<typename T>
    static vector<T> sortMapByInt(const map<int, T> map_sort, const bool isFromStoL = false)
    {
        vector<T> vecRet = vector<T>();
        vector<int> vecIndex = vector<int>();
        map<int, T> copyMap = map_sort;
        
        typename map<int, T>::iterator iter = copyMap.begin();
        
        for (; iter != copyMap.end(); iter++)
        {
            vecRet.push_back(iter->second);
            vecIndex.push_back(iter->first);
        }
        
        int index = 1;
        while (index < vecIndex.size())
        {
            int i = index;
            for (int j = i - 1; j >= 0; j--)
            {
                int icomp = vecIndex.at(i);
                int jcomp = vecIndex.at(j);
                if (!isFromStoL)
                {//从大到小
                    if (icomp > jcomp)
                    {
                        vecIndex.insert(vecIndex.begin() + j, icomp);
                        vecIndex.erase(vecIndex.begin() + j + 2);
                        
                        vecRet.insert(vecRet.begin() + j, vecRet.at(icomp));
                        vecRet.erase(vecRet.begin() + j + 2);
                        
                        i--;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {//从小到大
                    if (icomp < jcomp)
                    {
                        vecIndex.insert(vecIndex.begin() + j, icomp);
                        vecIndex.erase(vecIndex.begin() + j + 2);
                        
                        vecRet.insert(vecRet.begin() + j, vecRet.at(icomp));
                        vecRet.erase(vecRet.begin() + j + 2);
                        
                        i--;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            index++;
        }
        
        
        return vecRet;
    }
};

#endif /* FunctionAssembly_h */
