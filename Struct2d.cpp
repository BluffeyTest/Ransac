#include "Struct2d.h"

using namespace std;

/**
 * @brief Point2i加法
 * 
 * @param pt 
 * @return Point2i 
 */
inline Point2i Point2i::operator+(const Point2i &pt) const
{
    return Point2i(this->x + pt.x, this->y + pt.y);
     
}

/**
 * @brief Point2i减法
 * 
 * @param pt 
 * @return Point2i 
 */
inline Point2i Point2i::operator-(const Point2i &pt) const
{
    return Point2i(this->x - pt.x, this->y - pt.y);
}

/**
 * @brief Point2i判断是否相等
 * 
 * @param pt 
 * @return Point2i 
 */
inline bool Point2i::operator==(const Point2i &pt) const
{
    return (this->x == pt.x && this->y == pt.y);
}

/**
 * @brief Point2f加法
 * 
 * @param pt 
 * @return Point2f 
 */
inline Point2f Point2f::operator+(const Point2f &pt) const
{
    return Point2f(this->x + pt.x, this->y + pt.y);
     
}

/**
 * @brief Point2f减法
 * 
 * @param pt 
 * @return Point2f 
 */
inline Point2f Point2f::operator-(const Point2f &pt) const
{
    return Point2f(this->x - pt.x, this->y - pt.y);
}

/**
 * @brief Point2f比较是否相等</br>
 * 一般不建议使用
 * 
 * @param pt 
 * @return bool 
 */
inline bool Point2f::operator==(const Point2f &pt) const
{
    const double eps = 1e-2;//float的精度只有六位，算上整数位，一般能有三维小数位是保证精度的就不错了
    return (fabs(this->x - pt.x)<eps && fabs(this->y - pt.y)<eps );
}

/**
 * @brief Point2d加法
 * 
 * @param pt 
 * @return Point2d 
 */
inline Point2d Point2d::operator+(const Point2d &pt) const
{
    return Point2d(this->x + pt.x, this->y + pt.y);
     
}

/**
 * @brief Point2d减法
 * 
 * @param pt 
 * @return Point2d 
 */
inline Point2d Point2d::operator-(const Point2d &pt) const
{
    return Point2d(this->x - pt.x, this->y - pt.y);
}

/**
 * @brief Point2d比较是否相等</br>
 * 
 * @param pt 
 * @return bool 
 */
inline bool Point2d::operator==(const Point2d &pt) const
{
    const double eps = 1e-6;//double的精度有15位，算上整数位，所以问题小一些
    return (fabs(this->x - pt.x)<eps && fabs(this->y - pt.y)<eps );
}

stCircle::stCircle(Point &pt1, Point &pt2, Point &pt3)
{
    double x1 = pt1.x, x2 = pt2.x, x3 = pt3.x;
    double y1 = pt1.y, y2 = pt2.y, y3 = pt3.y;
    double a = x1 - x2;
    double b = y1 - y2;
    double c = x1 - x3;
    double d = y1 - y3;
    double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
    double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
    double det = b * c - a * d;

    //三点共线
    if (fabs(det) < 1e-5)
    {
        dR = -1;
        ptCenter = Point(0, 0);
    }

    double x0 = -(d * e - b * f) / det;
    double y0 = -(a * f - c * e) / det;
    dR = hypot(x1 - x0, y1 - y0);
    ptCenter = Point(x0, y0);
}

inline bool stCircle::operator==(const stCircle &stC) const
{
    if (this->ptCenter.x == stC.ptCenter.x && this->ptCenter.y == stC.ptCenter.y && this->dR == stC.dR)
        return true;
    return false;
}

stCircle stCircle::Shift(Point &pt) const
{
    Point pt1 = this->ptCenter + pt;
    return stCircle(pt1, this->dR);
}

inline bool stCircle::Cross(stCircle &stC) const
{
    double dDist = sqrt(pow(this->ptCenter.x - stC.ptCenter.x, 2) + pow(this->ptCenter.y - stC.ptCenter.y, 2));
    if (dDist == (this->dR + stC.dR))
        return true;
    return false;
}

//圆与直线相交
inline bool stCircle::Cross(stGenLine &stG) const
{
    double dDistance = this->FromLine(stG); //stG.FromPoint(this->ptCenter);
    if (this->dR < dDistance)
        return true;
    return false;
}

//待优化
//这儿应该用跨立、快排处理
inline bool stCircle::Cross(stSegLine &stS) const
{
    stGenLine stG = stGenLine(stS);
    double d1 = sqrt(pow(stS.pt1.x - this->ptCenter.x, 2) + pow(stS.pt1.y - this->ptCenter.y, 2)); ///<线段第一个点到圆心的距离
    double d2 = sqrt(pow(stS.pt2.x - this->ptCenter.x, 2) + pow(stS.pt2.y - this->ptCenter.y, 2)); ///<线段第二个点到圆心的距离
    //double d3 = this->FromLine(stG);///<圆心到直线的距离
    double d4 = stS.FromPoint(this->ptCenter);
    if (d1 < this->dR && d2 < this->dR) //都在圆内
        return false;
    if (std::min(d1, d2) < this->dR && max(d1, d2) > this->dR) //一个圆内一个圆外
        return true;
    if (d4 < this->dR && max(d1, d2) > this->dR) //线上最近点在圆内，最远点在圆外
        return true;
    return false;
}

inline double stCircle::FromLine(stGenLine &stG) const
{
    double dDistance = fabs(stG.da * this->ptCenter.x + stG.db * this->ptCenter.y + stG.dc) / sqrt(pow(stG.da, 2) + pow(stG.db, 2));
    return dDistance;
}

/*inline*/ double stCircle::FromPoint(Point &pt) const
{
    return sqrt(pow(this->ptCenter.x - pt.x, 2) + pow(this->ptCenter.y - pt.y, 2));
}

stGenLine::stGenLine(Point &p1, Point &p2)
{
    this->da = (double)(p1.y - p2.y);
    this->db = (double)(p2.x - p1.x);
    this->dc = (double)(p1.x * p2.y - p2.x * p1.y);
}

stGenLine::stGenLine(stSegLine &stS)
{
    Point &p1 = stS.pt1;
    Point &p2 = stS.pt2;
    this->da = (double)(p1.y - p2.y);
    this->db = (double)(p2.x - p1.x);
    this->dc = (double)(p1.x * p2.y - p2.x * p1.y);
}

inline double stGenLine::FromPoint(Point &pt) const
{
    double dDistance = fabs(this->da * pt.x + this->db * pt.y + this->dc) / sqrt(pow(this->da, 2) + pow(this->db, 2));
    return dDistance;
}

/*inline*/ bool stGenLine::operator||(const stGenLine &stG) const
{

    double dScale = this->da / stG.da;
    const double eps = 1e-6;
    if (fabs(this->da - stG.da * dScale) < eps && fabs(this->db - stG.db * dScale) < eps)
        return true;
    return false;
}

inline bool stGenLine::operator==(const stGenLine &stG) const
{
    double dScale = this->da / stG.da;
    const double eps = 1e-6;
    if (fabs(this->da - stG.da * dScale) < eps && fabs(this->db - stG.db * dScale) < eps && fabs(this->dc - stG.dc * dScale) < eps)
        return true;
    return false;
}

inline bool stSegLine::operator==(stSegLine &stS) const
{
    if (this->pt1 == stS.pt1 && this->pt2 == stS.pt2)
        return true;
    return false;
}

//快排跨立实验
inline bool stSegLine::Cross(stSegLine &stS) const
{
    if (!(min(this->pt1.x, this->pt2.x) <= max(stS.pt1.x, stS.pt2.x) 
        && min(stS.pt1.y, stS.pt2.y) <= max(this->pt1.y, this->pt2.y) 
        && min(stS.pt1.x, stS.pt2.x) <= max(this->pt1.x, this->pt2.x) 
        && min(this->pt1.y, this->pt2.y) <= max(stS.pt1.y, stS.pt2.y))
        )
            return false;

    double u, v, w, z;
    u = (stS.pt1.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt1.y - this->pt1.y);
    v = (stS.pt2.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt2.y - this->pt1.y);
    w = (this->pt1.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt1.y - stS.pt1.y);
    z = (this->pt2.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt2.y - stS.pt1.y);

    return (u * v <= 0.00000001 && w * z <= 0.00000001);
}

inline void stSegLine::GetGenLine(stGenLine &stG) const
{
    stG.da = (double)(this->pt1.y - this->pt2.y);
    stG.db = (double)(this->pt2.x - this->pt1.x);
    stG.dc = (double)(this->pt1.x * this->pt2.y - this->pt2.x * this->pt1.y);
}

inline double stSegLine::Length() const
{
    return sqrt(pow(this->pt1.x - this->pt2.x, 2) + pow(this->pt1.y - this->pt2.y, 2));
    ;
}

/*inline*/ double stSegLine::FromPoint(Point pt) const
{
    double r = ((pt.x - this->pt1.x) * (this->pt2.x - this->pt1.x) 
        + (pt.y - this->pt1.y) * (this->pt2.y - this->pt1.y)) / this->Length();
    double dAP2 = pow(this->pt1.x - pt.x, 2) + pow(this->pt1.y - pt.y, 2);
    double dBP2 = pow(pt.x - this->pt2.x, 2) + pow(pt.y - this->pt2.y, 2);
    if (r <= 0)
        return sqrt(dAP2); //第一种情况, 返回AP的长
    else if (r >= 1)
        return sqrt(dBP2); //第二种情况, 返回BP的长度
    else                   //第三种情况, 返回PC的长度
    {
        double AC = r * this->Length(); //先求AC的长度,(AC=r*|AB|)
        return sqrt(dAP2 - AC * AC);    //再勾股定理返回PC的长度
    }
    return 0.0;
}

/*inline*/ double Distance(Point &pt1, Point &pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

ostream &operator<<(ostream &os, stCircle &stC)
{
    os << "Circle: "
       << "Center = (" << stC.ptCenter.x << ", " << stC.ptCenter.y << "), R = " << stC.dR;
    return os;
}

ostream &operator<<(ostream &os, stArc &stArc)
{
    os << "Arc: " << stArc.Circle << ", startangle = " << stArc.dStartAngle << ", EndAngle = " << stArc.dEndAngle;
    return os;
}

ostream &operator<<(ostream &os, stSegLine &stS)
{
    os << "SegLine: "
       << "(" << stS.pt1.x << ", " << stS.pt1.y << ")----( " << stS.pt2.x << ", " << stS.pt2.y << ")";
    return os;
}

ostream &operator<<(ostream &os, stGenLine &stG)
{
    os << "GenLine: " << stG.da << " * x ";
    stG.db < 0 ? os << stG.db : os << "+ " << stG.db;
    os << " * y ";
    stG.dc < 0 ? os << stG.dc : os << "+ " << stG.dc;
    os << " = 0.0";
    return os;
}
