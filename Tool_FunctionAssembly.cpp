//
//  FunctionAssembly.cpp
//  XiaoXiaoLe2
//
//  Created by 欧阳佳乐 on 2017/7/27.
//
//

#include "Tool_FunctionAssembly.h"

/*int转换为string*/
string ToolFunctionAssembly::changeIntToString(int num)
{
    stringstream ss;
    ss << num;
    
    return ss.str();
}

/*两点的距离*/
float ToolFunctionAssembly::getTwoPointDis(float x1, float y1, float x2, float y2)
{
    float dis = 0;
    
    dis = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    
    return dis;
}

/*点距离直线是否在距离内
 *参数:
 ** a,b,c:(int) 直线方程式的参数(ax+by+c=0)
 ** poiX,poiY:(float) 点的坐标(x,y)
 ** dis:(float) 距离的最大值
 */
bool ToolFunctionAssembly::isPointDisLineLess(float a, float b, float c, float poiX, float poiY, float dis)
{
    bool isRet = false;
    float poiBeginX = 0.0f, poiBeginY = 0.0f, poiEndX = 0.0f, poiEndY = 0.0f;
    poiBeginX = poiX;
    poiBeginY = (-c - a * poiBeginX) / b;
    poiEndY = poiY;
    poiEndX = (-c - b * poiEndY) / a;
    
    float disX = (poiX > poiEndX) ? (poiX - poiEndX) : (poiEndX - poiX);
    float disY = (poiY > poiBeginY) ? (poiY - poiBeginY) : (poiBeginY - poiY);
    
    float distance = 0.0f;
    double angle = 0;
    angle = atan(disY / disX);
    distance = disX * sin(angle);
    
    if (distance < dis)
    {
        isRet = true;
    }
    
    return isRet;
}

/*点距离直线是否在距离内
 *参数:
 ** poiX1,poiY1,poiX2,poiY2:(float) 直线上的两点(poiX1,poiY1),(poiX2,poiY2)
 ** poiX,poiY:(float) 点的坐标(x,y)
 ** dis:(float) 距离的最大值
 */
bool ToolFunctionAssembly::isPointDisLineLess(float poiX1, float poiY1, float poiX2, float poiY2, float poiX, float poiY, float dis)
{
    bool isRet = false;
    float a = 0.0f, b = 0.0f, c = 0.0f;
    if (poiX1 == poiX2 && poiY1 == poiY2)
    {
        return isRet;
    }
    else if (poiX1 == poiX2)
    {
        b = 1.0f;
        c = poiX1;
    }
    else if (poiY1 == poiY2)
    {
        a = 1.0f;
        c = poiY1;
    }
    else
    {
        a = poiY2 - poiY1;
        b = poiX1 - poiX2;
        c = poiX2 * poiY1 - poiX1 * poiY2;
    }
    
    isRet = isPointDisLineLess(a, b, c, poiX, poiY, dis);
    
    return isRet;
}

/*点是否在矩形范围内
 *参数:
 ** poiBegX,poiBegY:(float) 矩形的起始点(左下点),(poiBegX,poiBegY)
 ** width,hight:(float) 矩形的长和高,(width,hight)
 ** poiX,poiY:(float) 点的坐标(poiX,poiY)
 */
bool ToolFunctionAssembly::isPointInRect(float poiBegX, float poiBegY, float width, float hight, float poiX, float poiY)
{
    bool isRet = false;
    
    if (poiX >= poiBegX && poiX <= poiBegX + width && poiY >= poiBegY && poiY <= poiBegY + hight)
    {
        isRet = true;
    }
    
    return isRet;
}

/*点是否在圆形范围内
 *参数:
 ** poiCirX,poiCirY:(float) 圆心(x, y)
 ** radius:(float) 圆的半径
 ** poiX,poiY:(float) 点的坐标
 */
bool ToolFunctionAssembly::isPointInCircle(float poiCirX, float poiCirY, float radius, float poiX, float poiY)
{
    bool isRet = false;
    
    double disX = poiX - poiCirX;
    double disY = poiY - poiCirY;
    double dis = sqrt(pow(disX, 2) + pow(disY, 2));
    
    if (dis <= radius)
    {
        isRet = true;
    }
    
    return isRet;
}

/*点是否在多边形范围内
 *参数:
 ** polyX,polyY:(vector<float>) 多边形的坐标点,(polyX[n],polyY[n])
 ** poiX,poiY:(float) 点的坐标(poiX,poiY)
 */
bool ToolFunctionAssembly::isPointInPolygon(vector<float> polyX, vector<float> polyY, float poiX, float poiY)
{
    bool isRet = false;
    
    if (polyX.size() > 2 && polyX.size() == polyY.size())
    {
        int index = 0;
        double angle = 0.0;
        double dev = 0.1;
        double pi = 3.14;
        
        while (index < polyX.size())
        {
            float poiX1 = polyX[index];
            float poiY1 = polyY[index];
            float poiX2 = polyX[(index + 1) % polyX.size()];
            float poiY2 = polyY[(index + 1) % polyX.size()];
            
            double angle1 = atan2((double)(poiY1 - poiY), (double)(poiX1 - poiX));
            double angle2 = atan2((double)(poiY2 - poiY), (double)(poiX2 - poiX));
            
            double angleThis = fabs(angle2 - angle1);
            if (angleThis > pi)
            {
                angleThis = 2.0 * pi - angleThis;
            }
            angle += angleThis;
            
            index++;
        }
        
        if (angle < pi * 2.0 + dev && angle > pi * 2.0 - dev)
        {
            isRet = true;
        }
    }
    
    return isRet;
}

////将map<int, T>的按照int大小排列，返回vector<T>
//template<typename T>
//vector<T> ToolFunctionAssembly::sortMapByInt(const map<int, T> map_sort, const bool isFromStoL)
//{
//    vector<T> vecRet = vector<T>();
//    vector<int> vecIndex = vector<int>();
//    
//    typename map<int, T>::iterator iter = map_sort.begin();
//    
//    for (; iter != map_sort.end(); iter++)
//    {
//        vecRet.push_back(iter->second);
//        vecIndex.push_back(iter->first);
//    }
//    
//    int index = 1;
//    while (index < vecIndex.size())
//    {
//        int i = index;
//        for (int j = i - 1; j >= 0; j--)
//        {
//            int icomp = vecIndex.at(i);
//            int jcomp = vecIndex.at(j);
//            if (!isFromStoL)
//            {//从大到小
//                if (icomp > jcomp)
//                {
//                    vecIndex.insert(vecIndex.begin() + j, icomp);
//                    vecIndex.erase(vecIndex.begin() + j + 2);
//                    
//                    vecRet.insert(vecRet.begin() + j, vecRet.at(icomp));
//                    vecRet.erase(vecRet.begin() + j + 2);
//                    
//                    i--;
//                }
//                else
//                {
//                    break;
//                }
//            }
//            else
//            {//从小到大
//                if (icomp < jcomp)
//                {
//                    vecIndex.insert(vecIndex.begin() + j, icomp);
//                    vecIndex.erase(vecIndex.begin() + j + 2);
//                    
//                    vecRet.insert(vecRet.begin() + j, vecRet.at(icomp));
//                    vecRet.erase(vecRet.begin() + j + 2);
//                    
//                    i--;
//                }
//                else
//                {
//                    break;
//                }
//            }
//        }
//        index++;
//    }
//    
//    
//    return vecRet;
//}










